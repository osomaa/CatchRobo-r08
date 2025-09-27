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
    timer_ = create_wall_timer(
      std::chrono::milliseconds(20),
      std::bind(&CommunicationNode::tick, this));
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
    uint8_t set = 0x12u;
    uint8_t on = 0x03u;
    uint16_t ad_ppos = 0x7005;
    uint16_t ad_vel = 0x7024;
    uint16_t ad_acc = 0x7025;
    float vel = 3.0f;
    float acc = 4.0f;
    uint32_t vel_b;
    uint32_t acc_b;
    std::memcpy(&vel_b, &vel, sizeof(float));
    std::memcpy(&acc_b, &acc, sizeof(float));
    for (uint8_t id = 1; id <= 6; ++id) {
      std::vector<uint8_t> frame = cmd2at(set, 0x0000, id, ad_ppos, 0x0000, 0x00000001);
      send_frame(fd_, frame);
      rclcpp::sleep_for(std::chrono::milliseconds(20));
      frame = cmd2at(on, 0x0000, id, 0x0000, 0x0000, 0x00000000);
      send_frame(fd_, frame);
      rclcpp::sleep_for(std::chrono::milliseconds(20));
      frame = cmd2at(set, 0x0000, id, ad_vel, 0x0000, vel_b);
      send_frame(fd_, frame);
      rclcpp::sleep_for(std::chrono::milliseconds(20));
      frame = cmd2at(set, 0x0000, id, ad_acc, 0x0000, acc_b);
      send_frame(fd_, frame);
      rclcpp::sleep_for(std::chrono::milliseconds(20));
    }
  }
  void on_cmd(const motor_control::msg::SendAt::SharedPtr msg) {
    uint8_t mode = 0x12u;
    uint16_t data16 = 0x0000;
    uint8_t id = msg->id;
    uint16_t address = 0x7016;
    uint16_t voided = 0x0000;
    uint32_t pos_b;
    std::memcpy(&pos_b, &msg->position, sizeof(float));
    std::vector<uint8_t> frame = cmd2at(mode, data16, id, address, voided, pos_b);
    send_frame(fd_, frame);
    rclcpp::sleep_for(std::chrono::milliseconds(20));
    //RCLCPP_INFO(get_logger(),
    //        "send cmd id=%u pos=%.3f", msg->id, msg->position);
  }
  void tick() {
    uint8_t mode = 0x11u;
    uint16_t data16 = 0x00FDu;
    uint16_t address = 0x7019;
    uint16_t voided = 0x0000;
    for (uint8_t id = 1; id <= 6; ++id) {
      std::vector<uint8_t> frame = cmd2at(mode, data16, id, address, voided, 0x00000000);
      send_frame(fd_, frame);
      rclcpp::sleep_for(std::chrono::milliseconds(20));
    }
  }
  void reader_loop() {
    std::vector<uint8_t> recv(1024);
    std::vector<uint8_t> rx;  // ★残りを保持する蓄積バッファ

    while (rclcpp::ok() && reader_running_.load()) {
      struct pollfd pfd{fd_, POLLIN, 0};
      int ret = ::poll(&pfd, 1, 50);
      if (ret > 0 && (pfd.revents & POLLIN)) {
        ssize_t n = ::read(fd_, recv.data(), recv.size());
        if (n <= 0) continue;

        // ★継ぎ足し（上書きしない）
        rx.insert(rx.end(), recv.begin(), recv.begin() + n);

        // ★長さベースでフレーム切り出し
        for (;;) {
          // "AT" を探す
          static const std::array<uint8_t,2> AT_HEADER{{'A','T'}};
          auto it = std::search(rx.begin(), rx.end(), AT_HEADER.begin(), AT_HEADER.end());
          if (it == rx.end()) { rx.clear(); break; }  // AT以前のゴミを捨てる
          if (rx.end() - it < 2 + 4 + 1) {            // ヘッダ不足
            // 次回の受信で続きが来るまで待つ
            rx.erase(rx.begin(), it);                 // AT手前は捨てる
            break;
          }

          // ヘッダ位置
          size_t off = it - rx.begin();
          const uint8_t *p = rx.data() + off;
          // "AT" [0..1], ID[2..5], DLC[6]
          uint8_t dlc = p[6];
          size_t need = 2 + 4 + 1 + dlc + 2;         // AT+ID+DLC+DATA+CRLF
          if (rx.end() - it < static_cast<ptrdiff_t>(need)) {
            // まだ全部来てない
            rx.erase(rx.begin(), it);                 // AT手前は捨てる
            break;
          }
          // 末尾のCRLF確認（なくても多くは通るが念のため）
          if (p[7 + dlc] != '\r' || p[7 + dlc + 1] != '\n') {
            // 形が変ならATの次から再探索
            rx.erase(rx.begin(), it + 2);
            continue;
          }
          // 完全な1フレームを抽出
          std::vector<uint8_t> frame(it, it + need);
          rx.erase(rx.begin(), it + need);           // 消費

          // ===== ここから既存処理 =====

          uint8_t mode5; uint8_t master; uint8_t id8; float val;
          at2cmd(frame, mode5, master, id8, val);
        
          auto msg = motor_control::msg::ReturnAt();
          msg.id = id8;
          msg.position = val;
          //RCLCPP_INFO(get_logger(), "res state id=%u pos=%.3f (mode=0x%02X)", msg.id, msg.position, mode5);
          pub_state_->publish(msg);
          // ===== 既存処理ここまで =====
        }
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
    }
  }

  int fd_;
  std::thread reader_thread_;
  std::atomic<bool> reader_running_{false};
  rclcpp::TimerBase::SharedPtr timer_;
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