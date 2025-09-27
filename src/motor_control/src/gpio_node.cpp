// src/gpio_node.cpp
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <motor_control/msg/gpio_cmd.hpp>
#include <gpiod.h>

#include <thread>
#include <vector>
#include <string>
#include <atomic>
#include <algorithm>
#include <cstdint>

class GpioNode : public rclcpp::Node {
public:
  GpioNode() : Node("gpio_node") {
    // --- parameters (int配列はint64で来るので一度受けてintへ詰め替え) ---
    chip_name_ = this->declare_parameter<std::string>("chip_name", "gpiochip0");

    const auto out_pins_i64 = this->declare_parameter<std::vector<int64_t>>(
        "out_pins", std::vector<int64_t>{12, 13, 16, 19, 20, 21});
    const auto in_pins_i64 = this->declare_parameter<std::vector<int64_t>>(
        "in_pins", std::vector<int64_t>{24, 25});
    out_pins.assign(out_pins_i64.begin(), out_pins_i64.end());
    in_pins.assign(in_pins_i64.begin(), in_pins_i64.end());

    // --- open chip ---
    chip_ = gpiod_chip_open_by_name(chip_name_.c_str());
    if (!chip_) {
      RCLCPP_FATAL(get_logger(), "Failed to open GPIO chip: %s", chip_name_.c_str());
      throw std::runtime_error("gpiod_chip_open_by_name failed");
    }

    // --- request outputs ---
    line_outs.reserve(out_pins.size());
    for (int pin : out_pins) {
      gpiod_line *line_out = gpiod_chip_get_line(chip_, pin);
      if (!line_out) throw std::runtime_error("gpiod_chip_get_line (out) failed");
      if (gpiod_line_request_output(line_out, "ros2", 0) < 0)
        throw std::runtime_error("gpiod_line_request_output failed");
      line_outs.push_back(line_out);
    }

    // --- request inputs (両エッジ) ---
    line_ins.reserve(in_pins.size());
    for (int pin : in_pins) {
      gpiod_line *line_in = gpiod_chip_get_line(chip_, pin);
      if (!line_in) throw std::runtime_error("gpiod_chip_get_line (in) failed");
      if (gpiod_line_request_both_edges_events(line_in, "ros2") < 0)
        throw std::runtime_error("gpiod_line_request_both_edges_events failed");
      line_ins.push_back(line_in);
    }

    // --- subscriptions ---
    sub_cmd_ = this->create_subscription<motor_control::msg::GpioCmd>(
        "gpio_cmd", 10,
        std::bind(&GpioNode::on_cmd, this, std::placeholders::_1));

    sub_full_toggle_ = this->create_subscription<std_msgs::msg::Bool>(
        "gpio_full_toggle", 10,
        std::bind(&GpioNode::full_toggle, this, std::placeholders::_1));

    // （必要なら）入力監視スレッド
    running_.store(true);
    worker_ = std::thread(&GpioNode::reader_loop, this);
  }

  ~GpioNode() override {
    running_.store(false);
    if (worker_.joinable()) worker_.join();

    for (auto *l : line_outs) if (l) gpiod_line_release(l);
    for (auto *l : line_ins)  if (l) gpiod_line_release(l);
    if (chip_) gpiod_chip_close(chip_);
  }

private:
  // 1本だけ切り替えるコマンド
  void on_cmd(const motor_control::msg::GpioCmd::SharedPtr msg) {
    if (!msg) return;
    if (msg->pin_index < 1 || msg->pin_index > static_cast<int>(line_outs.size())) {
      RCLCPP_WARN(get_logger(), "pin_index out of range: %d", msg->pin_index);
      return;
    }
    const int idx = msg->pin_index - 1;
    int value = msg->toggle ? 1 : 0;

    // 例: 8番(=idx7)だけ論理反転したい場合
    if (idx == 7) value = 1 - value;

    if (gpiod_line_set_value(line_outs[idx], value) < 0) {
      RCLCPP_ERROR(get_logger(), "gpiod_line_set_value failed (pin=%d)", out_pins[idx]);
      return;
    }
    RCLCPP_INFO(get_logger(), "Set GPIO %d to %d", out_pins[idx], value);
  }

  // 全出力を一括トグル
  void full_toggle(const std_msgs::msg::Bool::SharedPtr msg) {
    if (!msg) return;
    const int value = msg->data ? 1 : 0;
    for (size_t i = 0; i < line_outs.size(); ++i) {
      int v = static_cast<int>(value);
      if (static_cast<int>(i) == 7) v = 1 - v; // 同じ例の反転
      gpiod_line_set_value(line_outs[i], v);
    }
  }

  // 入力のエッジ監視（必要なければ丸ごと消してOK）
  void reader_loop() {
    while (running_.load()) {
      // 必要ならgpiod_line_event_wait + gpiod_line_event_readで実装
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }

private:
  // parameters
  std::string chip_name_;
  std::vector<int> out_pins;
  std::vector<int> in_pins;

  // gpiod resources
  gpiod_chip *chip_{nullptr};
  std::vector<gpiod_line*> line_outs;
  std::vector<gpiod_line*> line_ins;

  // ROS
  rclcpp::Subscription<motor_control::msg::GpioCmd>::SharedPtr sub_cmd_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_full_toggle_;

  // worker
  std::thread worker_;
  std::atomic<bool> running_{false};
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GpioNode>());
  rclcpp::shutdown();
  return 0;
}
