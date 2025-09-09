#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

namespace csvseq {

enum class MsgKind { STRING, TWIST };
enum class FbKind  { FB_STRING, FB_BOOL };

struct Step {
  // publish
  std::string topic;
  MsgKind msg_kind;
  std::string msg_text; // for STRING
  geometry_msgs::msg::Twist twist; // for TWIST

  // feedback
  std::string fb_topic;
  FbKind fb_kind;
  std::string fb_expect; // for FB_STRING
  std::optional<bool> fb_expect_bool; // for FB_BOOL

  // timeout
  double timeout_sec{10.0};
};

// ───────── CSV 1行の安全な分割（ダブルクォート対応の簡易実装） ─────────
static std::vector<std::string> split_csv_line(const std::string &line) {
  std::vector<std::string> out;
  std::string cur;
  bool in_quote = false;
  for (size_t i = 0; i < line.size(); ++i) {
    char c = line[i];
    if (c == '"') {
      if (in_quote && i + 1 < line.size() && line[i + 1] == '"') {
        cur.push_back('"'); // エスケープされた二重引用符
        ++i;
      } else {
        in_quote = !in_quote;
      }
    } else if (c == ',' && !in_quote) {
      out.push_back(cur);
      cur.clear();
    } else {
      cur.push_back(c);
    }
  }
  out.push_back(cur);
  return out;
}

static inline std::string trim(const std::string &s) {
  size_t b = s.find_first_not_of(" \t\r\n");
  if (b == std::string::npos) return "";
  size_t e = s.find_last_not_of(" \t\r\n");
  return s.substr(b, e - b + 1);
}

static inline bool iequals(const std::string &a, const std::string &b) {
  if (a.size() != b.size()) return false;
  for (size_t i=0;i<a.size();++i) {
    if (std::tolower(static_cast<unsigned char>(a[i])) !=
    std::tolower(static_cast<unsigned char>(b[i]))) return false;
  }
  return true;
}

static std::optional<bool> parse_bool_optional(const std::string &s) {
  if (s.empty()) return std::nullopt;
  std::string t = trim(s);
  for (auto &ch : t) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
  if (t == "true" || t == "1" || t == "t" || t == "yes" || t == "y") return true;
  if (t == "false" || t == "0" || t == "f" || t == "no" || t == "n") return false;
  return std::nullopt;
}

class CsvSequencerNode : public rclcpp::Node {
public:
  CsvSequencerNode() : Node("csv_sequencer_cpp") {
    declare_parameter<std::string>("csv_path", "");
    declare_parameter<double>("default_timeout", 10.0);

    auto path = get_parameter("csv_path").as_string();
    default_timeout_ = get_parameter("default_timeout").as_double();
    if (path.empty()) {
      RCLCPP_ERROR(get_logger(), "csv_path parameter is empty.");
      throw std::runtime_error("csv_path empty");
    }
    if (!load_csv(path)) {
      RCLCPP_ERROR(get_logger(), "Failed to load CSV: %s", path.c_str());
      throw std::runtime_error("CSV load failed");
    }

    // タイマで逐次実行
    timer_ = this->create_wall_timer(20ms, std::bind(&CsvSequencerNode::tick, this));
  }

private:
  bool load_csv(const std::string &path) {
    std::ifstream ifs(path);
    if (!ifs) return false;

    std::string header;
    if (!std::getline(ifs, header)) return false;
    auto cols = split_csv_line(header);
    // 期待ヘッダ
    const std::vector<std::string> expected = {
      "topic", "type", "feedback_topic", "feedback_type", "timeout",
      "msg_text","linear_x","linear_y","linear_z","angular_x","angular_y","angular_z",
      "feedback_expect","feedback_expect_bool"
    };
    // 簡易ヘッダ検証（順序一致前提）
    if (cols.size() < expected.size()) {
      RCLCPP_ERROR(get_logger(), "CSV header too few columns.");
      return false;
    }
    for (size_t i=0;i<expected.size();++i) {
      if (!iequals(trim(cols[i]), expected[i])) {
        RCLCPP_ERROR(get_logger(), "CSV header mismatch at col %zu: got '%s', expect '%s'",
                     i+1, cols[i].c_str(), expected[i].c_str());
        return false;
      }
    }

    steps_.clear();
    size_t line_no = 1;
    std::string line;
    while (std::getline(ifs, line)) {
      ++line_no;
      if (trim(line).empty()) continue;
      auto f = split_csv_line(line);
      if (f.size() < expected.size()) {
        RCLCPP_ERROR(get_logger(), "Line %zu: too few columns", line_no);
        return false;
      }
      Step s;

      s.topic = trim(f[0]);
      auto type = trim(f[1]);
      s.fb_topic = trim(f[2]);
      auto fb_type = trim(f[3]);

      // timeout
      try {
        s.timeout_sec = trim(f[4]).empty() ? default_timeout_ : std::stod(trim(f[4]));
      } catch (...) {
        s.timeout_sec = default_timeout_;
      }

      // message parse
      if (iequals(type, "std_msgs/msg/String")) {
        s.msg_kind = MsgKind::STRING;
        s.msg_text = f[5]; // raw（ダブルクォートでCSVから来る場合はそのまま格納）
      } else if (iequals(type, "geometry_msgs/msg/Twist")) {
        s.msg_kind = MsgKind::TWIST;
        auto getd = [&](size_t idx)->double{
          auto t = trim(f[idx]);
          if (t.empty()) return 0.0;
          try { return std::stod(t); } catch (...) { return 0.0; }
        };
        s.twist.linear.x  = getd(6);
        s.twist.linear.y  = getd(7);
        s.twist.linear.z  = getd(8);
        s.twist.angular.x = getd(9);
        s.twist.angular.y = getd(10);
        s.twist.angular.z = getd(11);
      } else {
        RCLCPP_ERROR(get_logger(), "Line %zu: unsupported message type '%s'", line_no, type.c_str());
        return false;
      }

      // feedback parse
      if (iequals(fb_type, "std_msgs/msg/String")) {
        s.fb_kind = FbKind::FB_STRING;
        s.fb_expect = f[12];
      } else if (iequals(fb_type, "std_msgs/msg/Bool")) {
        s.fb_kind = FbKind::FB_BOOL;
        s.fb_expect_bool = parse_bool_optional(f[13]);
        if (!s.fb_expect_bool.has_value()) {
          RCLCPP_ERROR(get_logger(), "Line %zu: feedback_expect_bool is invalid/empty for Bool", line_no);
          return false;
        }
      } else {
        RCLCPP_ERROR(get_logger(), "Line %zu: unsupported feedback type '%s'", line_no, fb_type.c_str());
        return false;
      }

      steps_.push_back(std::move(s));
    }

    RCLCPP_INFO(get_logger(), "Loaded %zu steps from %s", steps_.size(), path.c_str());
    return true;
  }

  template<class T>
  typename rclcpp::Publisher<T>::SharedPtr get_or_create_pub(const std::string &topic) {
    auto it = pubs_.find(topic);
    if (it != pubs_.end()) {
      // dynamic_cast OK because we only store correct type per topic
      auto ptr = std::dynamic_pointer_cast<rclcpp::Publisher<T>>(it->second);
      if (ptr) return ptr;
      // topic reused with different type → recreate
    }
    auto p = this->create_publisher<T>(topic, rclcpp::QoS(10));
    pubs_[topic] = p;
    return p;
  }

  // 1ステップ実行：publish → フィードバック待ち
  void run_step(const Step &s) {
    RCLCPP_INFO(get_logger(), "Step %zu/%zu → publish to %s, wait on %s (%.2fs)",
                cur_idx_+1, steps_.size(), s.topic.c_str(), s.fb_topic.c_str(), s.timeout_sec);

    bool satisfied = false;
    // removed unused 'wd'

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_str;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_bool;

    auto t0 = now();
    auto deadline = t0 + rclcpp::Duration::from_seconds(s.timeout_sec);

    // Subscribe first to avoid race (feedback arriving too fast)
    if (s.fb_kind == FbKind::FB_STRING) {
      sub_str = this->create_subscription<std_msgs::msg::String>(
        s.fb_topic, rclcpp::QoS(10),
        [&](const std_msgs::msg::String &m){
          if (m.data == s.fb_expect) {
            satisfied = true;
          }
        });
    } else { // FB_BOOL
      sub_bool = this->create_subscription<std_msgs::msg::Bool>(
        s.fb_topic, rclcpp::QoS(10),
        [&](const std_msgs::msg::Bool &m){
          if (m.data == s.fb_expect_bool.value()) {
            satisfied = true;
          }
        });
    }

    // Publish
    if (s.msg_kind == MsgKind::STRING) {
      auto pub = get_or_create_pub<std_msgs::msg::String>(s.topic);
      std_msgs::msg::String msg;
      msg.data = s.msg_text;
      pub->publish(msg);
      RCLCPP_INFO(get_logger(), "PUBLISH String: '%s'", msg.data.c_str());
    } else { // TWIST
      auto pub = get_or_create_pub<geometry_msgs::msg::Twist>(s.topic);
      pub->publish(s.twist);
      RCLCPP_INFO(get_logger(), "PUBLISH Twist: lin(%.3f,%.3f,%.3f) ang(%.3f,%.3f,%.3f)",
                  s.twist.linear.x, s.twist.linear.y, s.twist.linear.z,
                  s.twist.angular.x, s.twist.angular.y, s.twist.angular.z);
    }

    // Wait loop
    while (rclcpp::ok() && !satisfied) {
      rclcpp::spin_some(this->get_node_base_interface());
      if (now() >= deadline) break;
      std::this_thread::sleep_for(10ms);
    }

    if (!satisfied) {
      throw std::runtime_error("feedback timeout");
    }
    RCLCPP_INFO(get_logger(), "Feedback satisfied → next");
  }

  void tick() {
    if (busy_) return;
    if (cur_idx_ >= steps_.size()) {
      RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 5000, "All steps done. Idle.");
      return;
    }
    busy_ = true;
    try {
      run_step(steps_[cur_idx_]);
      ++cur_idx_;
    } catch (const std::exception &e) {
      RCLCPP_ERROR(get_logger(), "Step %zu failed: %s", cur_idx_+1, e.what());
      // 停止（必要ならリトライやon_error動作を拡張）
      timer_->cancel();
    }
    busy_ = false;
  }

private:
  std::vector<Step> steps_;
  size_t cur_idx_{0};
  bool busy_{false};
  double default_timeout_{10.0};
  rclcpp::TimerBase::SharedPtr timer_;
  std::unordered_map<std::string, std::shared_ptr<rclcpp::PublisherBase>> pubs_;
};

} // namespace csvseq

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<csvseq::CsvSequencerNode>();
    rclcpp::spin(node);
  } catch (const std::exception &e) {
    std::cerr << "Fatal: " << e.what() << std::endl;
  }
  rclcpp::shutdown();
  return 0;
}
