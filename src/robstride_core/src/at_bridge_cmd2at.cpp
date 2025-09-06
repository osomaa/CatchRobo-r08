#include <rclcpp/rclcpp.hpp>
#include "robstride_core/msg/mit_cmd.hpp"
#include "robstride_core/at_wire.hpp"

#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <std_msgs/msg/string.hpp>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <thread>
#include <atomic>
#include <array>

class AtBridgeNode : public rclcpp::Node {
public:
  AtBridgeNode() : Node("at_bridge_cmd2at") {
    // --- serial params ---
    port_ = declare_parameter<std::string>("port", "/dev/ttyUSB0");
    baud_ = declare_parameter<int>("baud", 921600);
    dtr_  = declare_parameter<bool>("dtr", true);
    rts_  = declare_parameter<bool>("rts", false);

    // --- scaling (float -> integer for TX, and inverse for RX) ---
    pos_scale_    = declare_parameter<double>("pos_scale",    1000.0);
    vel_scale_    = declare_parameter<double>("vel_scale",    1000.0);
    torque_scale_ = declare_parameter<double>("torque_scale", 100.0);
    kp_scale_     = declare_parameter<double>("kp_scale",     100.0);
    kd_scale_     = declare_parameter<double>("kd_scale",     100.0);

    // addr
    base_can_id_  = declare_parameter<int>("base_can_id", 0x00000000);

    // pubs/subs
    pub_obs_   = create_publisher<std_msgs::msg::UInt16MultiArray>("/robstride/obs", 50);
    pub_raw_   = create_publisher<std_msgs::msg::String>("/atcan/rx_raw", 10);  // debug
    sub_mit_   = create_subscription<robstride_core::msg::MitCmd>(
                  "/robstride/cmd/mit", rclcpp::QoS(100).best_effort(),
                  std::bind(&AtBridgeNode::on_mit, this, std::placeholders::_1));

    open_serial();

    // RX thread
    running_.store(true);
    rx_thread_ = std::thread([this]{ this->reader_loop(); });

    RCLCPP_INFO(get_logger(), "at_bridge_cmd2at ready: %s @ %d",
                port_.c_str(), baud_);
  }

  ~AtBridgeNode() override {
    running_.store(false);
    if (rx_thread_.joinable()) rx_thread_.join();
    if (fd_ >= 0) ::close(fd_);
  }

private:
  // ---- serial ----
  void open_serial() {
    fd_ = ::open(port_.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_ < 0) {
      RCLCPP_FATAL(get_logger(), "Serial open failed: %s", port_.c_str());
      throw std::runtime_error("serial open failed");
    }
    termios tio{}; ::tcgetattr(fd_, &tio);
    cfmakeraw(&tio);
    tio.c_cflag |= (CLOCAL | CREAD);
    tio.c_cflag &= ~CRTSCTS;
    tio.c_cflag &= ~PARENB; tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;  tio.c_cflag |= CS8;

    speed_t bs = B921600;
    switch (baud_) {
      case 115200: bs = B115200; break;
      case 230400: bs = B230400; break;
      case 460800: bs = B460800; break;
#ifdef B500000
      case 500000: bs = B500000; break;
#endif
#ifdef B921600
      case 921600: bs = B921600; break;
#endif
      default:     bs = B921600; break;
    }
    cfsetispeed(&tio, bs);
    cfsetospeed(&tio, bs);
    tio.c_cc[VMIN] = 0; tio.c_cc[VTIME] = 0;
    if (tcsetattr(fd_, TCSANOW, &tio) != 0) RCLCPP_ERROR(get_logger(), "tcsetattr failed");

#ifdef TIOCM_DTR
    int flags = 0; ioctl(fd_, TIOCMGET, &flags);
    if (dtr_) flags |= TIOCM_DTR; else flags &= ~TIOCM_DTR;
#ifdef TIOCM_RTS
    if (rts_) flags |= TIOCM_RTS; else flags &= ~TIOCM_RTS;
#endif
    ioctl(fd_, TIOCMSET, &flags);
#endif
    tcflush(fd_, TCIOFLUSH);
  }

  // ---- TX: MitCmd -> AT frame -> write ----
  void on_mit(const robstride_core::msg::MitCmd &m) {
    auto u16 = [](double v)->uint16_t {
      if (v < 0) v = 0; if (v > 65535) v = 65535; return static_cast<uint16_t>(std::lround(v));
    };
    const uint8_t  id    = m.id;
    const uint8_t  tor_u = static_cast<uint8_t>(std::clamp(std::lround(m.torque * torque_scale_), 0l, 255l));
    const uint16_t pos_u = u16(m.position * pos_scale_);
    const uint16_t vel_u = u16(m.velocity * vel_scale_);
    const uint16_t kp_u  = u16(m.kp * kp_scale_);
    const uint16_t kd_u  = u16(m.kd * kd_scale_);

    std::vector<uint8_t> payload;
    payload.reserve(2 + 2 + 8);
    payload.push_back(0x01);
    payload.push_back(tor_u);
    payload.push_back(0xFD);
    payload.push_back(id);
    auto be16 = [&](uint16_t w){ payload.push_back(uint8_t(w>>8)); payload.push_back(uint8_t(w&0xFF)); };
    be16(pos_u); be16(vel_u); be16(kp_u); be16(kd_u);

    const uint32_t can29 = static_cast<uint32_t>(base_can_id_) + static_cast<uint32_t>(id);
    const uint32_t addr  = atwire::build_addr(can29);
    auto frame = atwire::build_at_frame(addr, payload);
    if (fd_ >= 0) {
      ssize_t n = ::write(fd_, frame.data(), frame.size());
      if (n < 0) RCLCPP_ERROR(get_logger(), "Serial write failed");
    }
  }

  // ---- RX: AT frame -> payload decode -> /robstride/obs publish ----
  void reader_loop() {
    std::vector<uint8_t> buf; buf.reserve(4096);
    const std::array<uint8_t,2> CRLF{{'\r','\n'}};

    auto publish_raw = [&](const std::vector<uint8_t>& fr){
      std_msgs::msg::String s; s.data = atwire::hex_dump(fr); pub_raw_->publish(s);
    };
    auto publish_obs = [&](uint8_t id, uint8_t tor_u, uint16_t pos_u, uint16_t vel_u,
                           uint16_t kp_u, uint16_t kd_u){
      // 逆スケールで float へ戻す
      const double pos = static_cast<double>(pos_u) / std::max(1.0, pos_scale_);
      const double vel = static_cast<double>(vel_u) / std::max(1.0, vel_scale_);
      const double tor = static_cast<double>(tor_u) / std::max(1.0, torque_scale_);
      const double kp  = static_cast<double>(kp_u)  / std::max(1.0, kp_scale_);
      const double kd  = static_cast<double>(kd_u)  / std::max(1.0, kd_scale_);

      // control が取りやすい並びで publish（id, position, velocity, torque, kp, kd）
      std_msgs::msg::UInt16MultiArray m;
      m.data.resize(6);
      m.data[0] = id;
      // 必要に応じてスケールをUInt16化した値を流す or 別msgに変える
      m.data[1] = pos_u;
      m.data[2] = vel_u;
      m.data[3] = static_cast<uint16_t>(tor_u);
      m.data[4] = kp_u;
      m.data[5] = kd_u;
      pub_obs_->publish(m);
    };

    while (rclcpp::ok() && running_.load()) {
      uint8_t tmp[512];
      ssize_t n = (fd_>=0) ? ::read(fd_, tmp, sizeof(tmp)) : -1;
      if (n > 0) {
        buf.insert(buf.end(), tmp, tmp+n);
        for(;;){
          auto it = std::search(buf.begin(), buf.end(), CRLF.begin(), CRLF.end());
          if (it == buf.end()) break; // CRLFまで溜まってない

          std::vector<uint8_t> one(buf.begin(), it+2);
          buf.erase(buf.begin(), it+2);

          publish_raw(one); // debug

          // フォーマット: "AT" + addr(4) + len(1) + payload + CRLF
          if (one.size() >= 2+4+1+2 && one[0]=='A' && one[1]=='T' &&
              one[one.size()-2]=='\r' && one.back()=='\n') {
            uint8_t  len = one[6];
            if (one.size() == size_t(2+4+1+len+2)) {
              std::vector<uint8_t> pl(one.begin()+7, one.begin()+7+len);

              // 期待するレイアウトに合うかチェック
              if (pl.size() >= 2+2+8 && pl[0]==0x01 && pl[2]==0xFD) {
                uint8_t  tor_u = pl[1];
                uint8_t  id    = pl[3];
                auto rd16 = [&](size_t off)->uint16_t {
                  return (uint16_t(pl[off])<<8) | uint16_t(pl[off+1]);
                };
                uint16_t pos_u = rd16(4);
                uint16_t vel_u = rd16(6);
                uint16_t kp_u  = rd16(8);
                uint16_t kd_u  = rd16(10);

                publish_obs(id, tor_u, pos_u, vel_u, kp_u, kd_u);
              } else {
                // 未対応のペイロードは無視（必要なら別トピックへ生出し）
              }
            } else {
              RCLCPP_WARN(get_logger(), "RX len mismatch: len=%u frame=%zu", len, one.size());
            }
          } else {
            RCLCPP_WARN(get_logger(), "Invalid AT frame");
          }
        }
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
      }
    }
  }

private:
  // params
  std::string port_; int baud_; bool dtr_, rts_; int base_can_id_;
  double pos_scale_, vel_scale_, torque_scale_, kp_scale_, kd_scale_;
  // serial & threads
  int fd_{-1};
  std::atomic<bool> running_{false};
  std::thread rx_thread_;

  // ROS I/F
  rclcpp::Subscription<robstride_core::msg::MitCmd>::SharedPtr sub_mit_;
  rclcpp::Publisher<std_msgs::msg::UInt16MultiArray>::SharedPtr pub_obs_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_raw_;
};

int main(int argc, char** argv){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AtBridgeNode>());
  rclcpp::shutdown();
  return 0;
}
