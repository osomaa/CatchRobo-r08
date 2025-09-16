#include "rclcpp/rclcpp.hpp"
#include <vector>
#include <cmath>
#include <functional>

#include "motor_control/msg/SendAt.hpp"
#include "motor_control/msg/ReturnAt.hpp"
#include "transform.hpp"
#include "serial_utils.hpp" 

class CommunicationNode : public rclcpp::Node {
public:
  CommunicationNode() : rclcpp::Node("communication_node"), fd_(-1) {
    open_serial(fd_);

    auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
    sub_cmd_ = create_subscription<motor_control::msg::SendAt>(
      "motor/cmd", qos,
      std::bind(&CommunicationNode::on_cmd, this, std::placeholders::_1));
    pub_state_ = create_publisher<motor_control::msg::ReturnAt>("motor/state", qos);
  }
  ~CommunicationNode() override {
    close_serial(fd_);
  }

private:
  void on_cmd(const motor_control::msg::SendAt::SharedPtr msg) {
    uint8_t mode = 0x12;
    uint16_t data16 = 0x0000;
    uint8_t id = msg->id;
    uint16_t address = 0x7016;
    uint16_t voided = 0x0000;
    uint32_t pos_b = memcpy(&msg->position, sizeof(float));
    std::vector<uint8_t> frame = cmd2at(mode, data16, id, address, voided, pos_b);
    send_frame(fd_, frame);
  }

  void reader_loop() {
    while (rclcpp::ok() && reader_runnning_.load()) {
      // ここに受信処理を実装する場合は、非同期I/Oや別スレッドでの処理を検討する
      std::vector<uint8_t> buf;
      buf.reserve(1024);
      struct pollfd pfd{fd_, POLLIN, 0};

      int ret = ::poll(&pfd, 1, 100); // タイムアウト100ms
      if (ret > 0 && (pfd.revents & POLLIN)) {
        uint8_t buf[256];
        ssize_t n = ::read(fd_, buf, sizeof(buf));
        for(;;){
          auto it = std::search(buf.begin(), buf.end(), CRLF_.begin(), CRLF_.end());
          if (it == buf.end()) break;
          std::vector<uint8_t> frame(buf.begin(), it+2);
          buf.erase(buf.begin(), it+2);

          uint32_t addr;
          uint64_t payload;
          uint8_t len = split_frame(frame, addr, payload);

          uint8_t mode5, id8;
          uint16_t data16;
          split_addr(addr, mode5, data16, id8);

          uint16_t raw_pos, raw_vel, raw_torque, raw_temp;
          split_payload(payload, raw_pos, raw_vel, raw_torque, raw_temp);

          SendAt msg;
          msg.id = id8;
          msg.position = uint2float(raw_pos, -12.5f, 12.5f, 16);
          msg.velocity = uint2float(raw_vel, -12.5f, 12.5f, 16);
          msg.torque = uint2float(raw_torque, -12.5f, 12.5f, 16);
          msg.temp = uint2float(raw_temp, -12.5f, 12.5f, 16);
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