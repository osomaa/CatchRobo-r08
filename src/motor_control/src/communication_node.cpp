#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <cmath>
#include <functional>

#include "motor_control/msg/send_at.hpp"
#include "motor_control/msg/return_at.hpp"
#include "motor_control/transform.hpp"
#include "motor_control/serial_utils.hpp" 
#include <thread>
#include <atomic>
#include <poll.h>
#include <algorithm>
#include <cstring>
#include <cstdint>

class CommunicationNode : public rclcpp::Node {
public:
  CommunicationNode() : rclcpp::Node("communication_node"), fd_(-1) {
    open_serial(fd_);

    auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
    sub_cmd_ = create_subscription<motor_control::msg::SendAt>(
      "motor/cmd", qos,
      std::bind(&CommunicationNode::on_cmd, this, std::placeholders::_1));
    pub_state_ = create_publisher<motor_control::msg::ReturnAt>("motor/state", qos);
    reader_running_.store(true);
    reader_thread_ = std::thread(&CommunicationNode::reader_loop, this);
    init_motor();
  }
  ~CommunicationNode() override {
    close_serial(fd_);
    reader_running_.store(false);
    if (reader_thread_.joinable()) {
      reader_thread_.join(); 
    }
  }

private:
  void init_motor() {
    uint8_t set = 0x12;
    uint8_t on = 0x03;
    uint16_t ad_ppos = 0x7005;
    uint16_t ad_vel = 0x7024;
    uint16_t ad_acc = 0x7016;
    float vel = 1.0f;
    float acc = 2.0f;
    uint32_t vel_b;
    uint32_t acc_b;
    std::memcpy(&vel_b, &vel, sizeof(float));
    std::memcpy(&acc_b, &acc, sizeof(float));
    for (uint8_t id = 1; id <= 6; ++id) {
      std::vector<uint8_t> frame = cmd2at(set, 0x0000, id, ad_ppos, 0x0000, 0x01000000);
      send_frame(fd_, frame);
      frame = cmd2at(set, 0x0000, id, ad_vel, 0x0000, vel_b);
      send_frame(fd_, frame);
      frame = cmd2at(set, 0x0000, id, ad_acc, 0x0000, acc_b);
      send_frame(fd_, frame);
      frame = cmd2at(on, 0x0000, id, 0x0000, 0x0000, 0x00000000);
      send_frame(fd_, frame);
      rclcpp::sleep_for(std::chrono::milliseconds(100));
    }
  }
  void on_cmd(const motor_control::msg::SendAt::SharedPtr msg) {
    uint8_t mode = 0x12;
    uint16_t data16 = 0x0000;
    uint8_t id = msg->id;
    uint16_t address = 0x7016;
    uint16_t voided = 0x0000;
    uint32_t pos_b=0;
    std::memcpy(&pos_b, &msg->position, sizeof(float));
    std::vector<uint8_t> frame = cmd2at(mode, data16, id, address, voided, pos_b);
    send_frame(fd_, frame);
  }

  void reader_loop() {
    reader_running_.store(true);
    std::vector<uint8_t> buf(1024);
    while (rclcpp::ok() && reader_running_.load()) {
      struct pollfd pfd{fd_, POLLIN, 0};
      int ret = ::poll(&pfd, 1, 100); // タイムアウト100ms

      if (ret > 0 && (pfd.revents & POLLIN)) {
        ssize_t n = ::read(fd_, buf.data(), buf.size());
        if (n <= 0) continue;

        auto it_begin = buf.begin();
        auto it_end = buf.begin() + n;
        
        for(;;){
          auto it = std::search(buf.begin(), buf.end(), CRLF_.begin(), CRLF_.end());
          if (it == buf.end()) break;
          std::vector<uint8_t> frame(buf.begin(), it+2);
          buf.erase(buf.begin(), it+2);
          uint8_t mode5;
          uint16_t data16;
          uint8_t id8;
          float val;

          at2cmd(frame, mode5, data16, id8, val);
          auto msg = motor_control::msg::ReturnAt();
          msg.id = id8;
          msg.position = val;
          pub_state_->publish(msg);
        }
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
  }

  int fd_;
  std::thread reader_thread_;
  std::atomic<bool> reader_running_;

  rclcpp::Subscription<motor_control::msg::SendAt>::SharedPtr sub_cmd_;
  rclcpp::Publisher<motor_control::msg::ReturnAt>::SharedPtr pub_state_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CommunicationNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}