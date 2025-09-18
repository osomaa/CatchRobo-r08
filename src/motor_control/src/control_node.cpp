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

    pub_cmd_batch_ = this->create_publisher<motor_control::msg::SendArray>("motor/cmd_batch", rclcpp::QoS(10));
    sub_done_ = this->create_subscription<std_msgs::msg::Bool>(
      "motor/observe/done", rclcpp::QoS(10),
      std::bind(&ControlNode::on_done, this, std::placeholders::_1));

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

  // 1行分を読み取り、batchに積む。終端ならfalse
  bool make_batch(motor_control::msg::SendArray& batch) {
    batch.cmds.clear();

    std::string line;
    std::getline(ifs_, line);
    std::istringstream ss(line);
    std::string cell;

    std::getline(ss, cell, ',');
    bool pomp = to_int(trim_copy(cell)).value_or(0) != 0;
    // 期待: id, position (, ... 拡張余地)
    while (true) {
      motor_control::msg::SendAt cmd;
      // id
      if (!std::getline(ss, cell, ',')) break;
        auto id_opt = to_int(trim_copy(cell));
      if (!id_opt) {
        RCLCPP_WARN(get_logger(), "Invalid id in line: %s", line.c_str());
        continue;
      }
      cmd.id = static_cast<uint8_t>(*id_opt);

      if (!std::getline(ss, cell, ',')) {
        RCLCPP_WARN(get_logger(), "Missing position in line: %s", line.c_str());
        continue;
      }
      auto pos_opt = to_float(trim_copy(cell));
      if (!pos_opt) {
        RCLCPP_WARN(get_logger(), "Invalid position in line: %s", line.c_str());
        continue;
      }
      cmd.position = *pos_opt;
      batch.cmds.push_back(cmd);
    }

    if (batch.cmds.empty()) {
      return false;
    }
    return true;
  }

  void on_done(const std_msgs::msg::Bool::SharedPtr msg) {
    // true=次バッチ要求、false=再送要求（と勝手に解釈）
    if (msg->data) {
      if (!make_batch(cmd_batch_)) {
        RCLCPP_INFO(get_logger(), "CSV reached EOF. No more commands.");
        // 必要ならここで完了通知を出す or ノード終了
        // rclcpp::shutdown();
        return;
      }
      pub_cmd_batch_->publish(cmd_batch_);
      RCLCPP_INFO(get_logger(), "Published new batch: %zu cmds", cmd_batch_.cmds.size());
    } else {
      // 直前のバッチを再送（セミコロン忘れ修正）
      pub_cmd_batch_->publish(cmd_batch_);
      RCLCPP_DEBUG(get_logger(), "Republished last batch: %zu cmds", cmd_batch_.cmds.size());
    }
  }

  std::string input_csv_path_;
  std::ifstream ifs_;
  motor_control::msg::SendArray cmd_batch_;
  rclcpp::Publisher<motor_control::msg::SendArray>::SharedPtr pub_cmd_batch_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_done_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ControlNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
