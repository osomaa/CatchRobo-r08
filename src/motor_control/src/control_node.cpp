#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <motor_control/msg/send_at.hpp>
#include <motor_control/msg/send_array.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <optional>

class ControlNode : public rclcpp::Node {
public:
  ControlNode() : rclcpp::Node("control_csv_node") {
    // パラメータ: 入力CSVパス
    const std::string pkg = ament_index_cpp::get_package_share_directory("motor_control");
    const std::string default_csv = pkg + "/config/program.csv";
    input_csv_path_ = this->declare_parameter<std::string>("input_path", default_csv);
    if (input_csv_path_.empty()) {
      RCLCPP_FATAL(get_logger(), "Parameter 'input_csv' is empty.");
      throw std::runtime_error("input_csv not set");
    }
    ifs_.open(input_csv_path_);
    if (!ifs_) {
      RCLCPP_FATAL(get_logger(), "Failed to open CSV: %s", input_csv_path_.c_str());
      throw std::runtime_error("failed to open csv");
    }

    auto q_event = rclcpp::QoS(rclcpp::KeepLast(1)).reliable();
    pub_cmd_batch_ = this->create_publisher<motor_control::msg::SendArray>("motor/cmd_batch", rclcpp::QoS(10));
    sub_done_ = this->create_subscription<std_msgs::msg::Bool>(
      "motor/observe/done", q_event,
      std::bind(&ControlNode::on_done, this, std::placeholders::_1));
    pub_gpio = this->create_publisher<std_msgs::msg::Bool>("gpio_full_toggle", 10);
    RCLCPP_INFO(get_logger(), "control_node ready. CSV=%s", input_csv_path_.c_str());
  }

private:
  static inline std::string trim_copy(std::string s) {
    auto issp = [](unsigned char c){ return std::isspace(c); };
    while (!s.empty() && issp(s.front())) s.erase(s.begin());
    while (!s.empty() && issp(s.back()))  s.pop_back();
    return s;
  }

  static std::optional<int> to_int(const std::string& s) {
    try { return std::stoi(s); } catch (...) { return std::nullopt; }
  }
  static std::optional<float> to_float(const std::string& s) {
    try { return std::stof(s); } catch (...) { return std::nullopt; }
  }
  bool finished_ = false;

// make_batch を堅牢化
bool make_batch(motor_control::msg::SendArray& batch) {
  batch.cmds.clear();
  if (!ifs_.good()) return false;

  std::string line;
  // 空行/コメントをスキップ
  while (std::getline(ifs_, line)) {
    auto t = trim_copy(line);
    if (t.empty() || t[0] == '#' || t[0] == ';') continue;

    std::istringstream ss(line);
    std::string cell;

    // 先頭セル（あなたのCSVは ',' 区切りでOK）
    std::getline(ss, cell, ','); // 例: フラグを読み捨て
    std_msgs::msg::Bool pomp;
    pomp.data = (trim_copy(cell) == "1");
    pub_gpio->publish(pomp);
    size_t added = 0;

    while (true) {
      motor_control::msg::SendAt cmd;

      if (!std::getline(ss, cell, ',')) break;
      auto id_opt = to_int(trim_copy(cell));
      if (!id_opt) { std::string dummy; std::getline(ss, dummy, ','); continue; }
      cmd.id = static_cast<uint8_t>(*id_opt);

      if (!std::getline(ss, cell, ',')) break;
      auto pos_opt = to_float(trim_copy(cell));
      if (!pos_opt) continue;
      cmd.position = *pos_opt;

      batch.cmds.push_back(cmd);
      ++added;
    }
    return added > 0;
  }
  return false; // 本当のEOF
}

void on_done(const std_msgs::msg::Bool::SharedPtr msg) {
  //RCLCPP_INFO(get_logger(), "[on_done] data=%d", (int)msg->data);
  if (finished_) return;

  if (msg->data) {
    if (!make_batch(cmd_batch_)) {
      RCLCPP_INFO(get_logger(), "CSV reached EOF. No more commands.");
      finished_ = true;                       // ← 以後は無視
      return;
    }
    pub_cmd_batch_->publish(cmd_batch_);
    RCLCPP_INFO(get_logger(), "Published new batch: %zu cmds", cmd_batch_.cmds.size());
  } else {
    if (!cmd_batch_.cmds.empty())
      pub_cmd_batch_->publish(cmd_batch_);
  }
}

  std::string input_csv_path_;
  std::ifstream ifs_;
  motor_control::msg::SendArray cmd_batch_;
  rclcpp::Publisher<motor_control::msg::SendArray>::SharedPtr pub_cmd_batch_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_done_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_gpio;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ControlNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
