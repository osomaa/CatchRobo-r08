#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>
#include <vector>
#include <thread>
#include <atomic>

// POSIX serial
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace atcan {

static inline std::string hex_dump(const std::vector<uint8_t>& b) {
  static const char* hexd = "0123456789ABCDEF";
  std::string s; s.reserve(b.size()*3);
  for (size_t i=0;i<b.size();++i){
    uint8_t x=b[i];
    s.push_back(hexd[x>>4]); s.push_back(hexd[x&0xF]);
    if(i+1<b.size()) s.push_back(' ');
  }
  return s;
}

static inline uint32_t build_addr(uint8_t id8, uint16_t data16, uint8_t mode5, uint8_t res3) {
  uint32_t base = (uint32_t(id8) << 24) | (uint32_t(data16) << 8) | ((uint32_t(mode5)&0x1F) << 3) | (uint32_t(res3)&0x07);
  return ((base << 3) | 0x04u);
}

static inline void split_addr(uint32_t raw_addr, uint8_t& id8, uint16_t& data16, uint8_t& mode5, uint8_t& res3) {
  uint32_t addr = (raw_addr & ~0x00000004u) >> 3;
  res3  = uint8_t(addr & 0x07u);
  mode5 = uint8_t((addr >> 3) & 0x1Fu);
  data16= uint16_t((addr >> 8) & 0xFFFFu);
  id8   = uint8_t((addr >> 24) & 0xFFu);
}

static inline bool parse_candump_frame(const std::string& s, uint8_t& id8, uint16_t& data16, uint8_t& mode5, uint8_t& res3, std::vector<uint8_t>& payload) {
  auto pos = s.find('#');
  if (pos == std::string::npos) return false;
  std::string id_hex = s.substr(0, pos);
  std::string data_hex = s.substr(pos+1);
  if (id_hex.empty()) return false;
  uint32_t canid = 0;
  try { canid = std::stoul(id_hex, nullptr, 16); }
  catch (...) { return false; }

  // parse payload
  payload.clear();
  std::string dh;
  dh.reserve(data_hex.size());
  for(char c: data_hex){ if(isxdigit((unsigned char)c)) dh.push_back(c); }
  if (dh.size() % 2 != 0) return false;
  for(size_t i=0;i<dh.size(); i+=2){
    uint8_t v = uint8_t(std::stoul(dh.substr(i,2), nullptr, 16));
    payload.push_back(v);
  }
  if (payload.size() > 8) return false;

  id8    = uint8_t((canid >> 24) & 0xFFu);
  data16 = uint16_t((canid >> 8) & 0xFFFFu);
  mode5  = uint8_t((canid >> 3) & 0x1Fu);
  res3   = uint8_t(canid & 0x07u);
  return true;
}

static inline std::string format_candump_line(uint8_t id8, uint16_t data16, uint8_t mode5, uint8_t res3, const std::vector<uint8_t>& payload) {
  uint32_t canid = (uint32_t(id8)<<24) | (uint32_t(data16)<<8) | ((uint32_t(mode5)&0x1F)<<3) | (uint32_t(res3)&0x07);
  static const char* hexd = "0123456789ABCDEF";
  char idbuf[9]; idbuf[8]=0;
  for(int i=7;i>=0;--i){ idbuf[i]=hexd[canid & 0xF]; canid >>= 4; }
  std::string s(idbuf);
  s.push_back('#');
  for(uint8_t b: payload){ s.push_back(hexd[b>>4]); s.push_back(hexd[b&0xF]); }
  return s;
}

class AtCanBridgeNode : public rclcpp::Node {
public:
  AtCanBridgeNode(): Node("atcan_bridge_cpp") {
    port_ = this->declare_parameter<std::string>("port", "/dev/ttyUSB0");
    baud_ = this->declare_parameter<int>("baud", 921600);
    dtr_  = this->declare_parameter<bool>("dtr", true);
    rts_  = this->declare_parameter<bool>("rts", false);
    qsz_  = this->declare_parameter<int>("queue_size", 100);

    pub_rx_     = this->create_publisher<std_msgs::msg::String>("/atcan/rx", qsz_);
    pub_rx_raw_ = this->create_publisher<std_msgs::msg::String>("/atcan/rx_raw", qsz_);
    sub_tx_     = this->create_subscription<std_msgs::msg::String>("/atcan/tx", qsz_,
                      std::bind(&AtCanBridgeNode::on_tx, this, std::placeholders::_1));

    open_serial();
    reader_running_.store(true);
    reader_thread_ = std::thread([this]{ this->reader_loop(); });
  }

  ~AtCanBridgeNode() override {
    reader_running_.store(false);
    if (reader_thread_.joinable()) reader_thread_.join();
    if (fd_ >= 0) ::close(fd_);
  }

private:
  // ===== Serial =====
  void open_serial() {
    fd_ = ::open(port_.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd_ < 0) {
      RCLCPP_FATAL(this->get_logger(), "Serial open failed: %s", port_.c_str());
      throw std::runtime_error("serial open failed");
    }
    // termios setup
    termios tio{}; ::tcgetattr(fd_, &tio);
    cfmakeraw(&tio);
    tio.c_cflag |= (CLOCAL | CREAD);
    tio.c_cflag &= ~CRTSCTS; // no hw flow
    // 8N1
    tio.c_cflag &= ~PARENB;
    tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;
    tio.c_cflag |= CS8;
    // speed
    speed_t spd = B921600;
#ifndef B921600
# error "Your termios headers lack B921600; map to closest or switch to boost::asio."
#endif
    // If you need other rates, add mapping from baud_ to speed_t here.
    (void)spd;
    // Try to map common baud rates:
    speed_t bs = B921600;
    switch (baud_) {
      case 115200: bs = B115200; break;
      case 230400: bs = B230400; break;
      case 460800: bs = B460800; break;
      case 500000: bs = B500000; break;
      case 921600: bs = B921600; break;
      default:     bs = B921600; break;
    }
    cfsetispeed(&tio, bs);
    cfsetospeed(&tio, bs);

    tio.c_cc[VMIN]  = 0; // non-blocking
    tio.c_cc[VTIME] = 0;

    if (tcsetattr(fd_, TCSANOW, &tio) != 0) {
      RCLCPP_ERROR(this->get_logger(), "tcsetattr failed");
    }

    // DTR/RTS
#ifdef TIOCM_DTR
    int flags = 0;
    ioctl(fd_, TIOCMGET, &flags);
    if (dtr_) flags |= TIOCM_DTR; else flags &= ~TIOCM_DTR;
#ifdef TIOCM_RTS
    if (rts_) flags |= TIOCM_RTS; else flags &= ~TIOCM_RTS;
#endif
    ioctl(fd_, TIOCMSET, &flags);
#endif

    // flush
    tcflush(fd_, TCIOFLUSH);
    RCLCPP_INFO(this->get_logger(), "Serial open OK: %s @ %d bps (DTR=%s, RTS=%s)",
                port_.c_str(), baud_, dtr_?"on":"off", rts_?"on":"off");
  }

  // ===== TX path =====
  void on_tx(const std_msgs::msg::String::SharedPtr msg) {
    uint8_t id8, mode5, res3; uint16_t data16; std::vector<uint8_t> payload;
    if (!parse_candump_frame(msg->data, id8, data16, mode5, res3, payload)) {
      RCLCPP_WARN(this->get_logger(), "TX parse error: '%s'", msg->data.c_str());
      return;
    }
    // Build AT frame
    uint32_t raw = build_addr(id8, data16, mode5, res3);
    std::vector<uint8_t> frame;
    frame.reserve(2+4+1+payload.size()+2);
    frame.push_back('A'); frame.push_back('T');
    // addr BE
    frame.push_back(uint8_t((raw >> 24) & 0xFF));
    frame.push_back(uint8_t((raw >> 16) & 0xFF));
    frame.push_back(uint8_t((raw >> 8)  & 0xFF));
    frame.push_back(uint8_t( raw        & 0xFF));
    frame.push_back(uint8_t(payload.size() & 0xFF));
    frame.insert(frame.end(), payload.begin(), payload.end());
    frame.push_back('\r'); frame.push_back('\n');

    // write
    if (fd_ >= 0) {
      ssize_t n = ::write(fd_, frame.data(), frame.size());
      if (n < 0) RCLCPP_ERROR(this->get_logger(), "Serial write failed");
    }
  }

  // ===== RX path =====
  void reader_loop() {
    std::vector<uint8_t> buf; buf.reserve(4096);
    auto pub_raw = [this](const std::vector<uint8_t>& fr){
      std_msgs::msg::String m; m.data = hex_dump(fr); pub_rx_raw_->publish(m);
    };
    auto pub_rx  = [this](const std::string& line){
      std_msgs::msg::String m; m.data = line; pub_rx_->publish(m);
    };

    while (rclcpp::ok() && reader_running_.load()) {
      uint8_t tmp[1024];
      ssize_t n = (fd_>=0) ? ::read(fd_, tmp, sizeof(tmp)) : -1;
      if (n > 0) {
        buf.insert(buf.end(), tmp, tmp+n);
        // extract by CRLF
        for(;;){
          auto it = std::search(buf.begin(), buf.end(), CRLF_.begin(), CRLF_.end());
          if (it == buf.end()) break;
          std::vector<uint8_t> one(buf.begin(), it+2);
          buf.erase(buf.begin(), it+2);

          pub_raw(one);
          // parse AT -> candump
          if (one.size() >= 2+4+1+2 && one[0]=='A' && one[1]=='T' && one[one.size()-2]=='\r' && one.back()=='\n') {
            uint32_t raw_addr = (uint32_t(one[2])<<24) | (uint32_t(one[3])<<16) | (uint32_t(one[4])<<8) | uint32_t(one[5]);
            uint8_t  len      = one[6];
            if (one.size() == size_t(2+4+1+len+2)) {
              std::vector<uint8_t> payload(one.begin()+7, one.begin()+7+len);
              uint8_t id8, mode5, res3; uint16_t data16;
              split_addr(raw_addr, id8, data16, mode5, res3);
              pub_rx(format_candump_line(id8, data16, mode5, res3, payload));
            } else {
              RCLCPP_WARN(this->get_logger(), "RX length mismatch (len=%u, frame=%zu)", len, one.size());
            }
          } else {
            RCLCPP_WARN(this->get_logger(), "Invalid AT frame");
          }
        }
      } else {
        // idle
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
      }
    }
  }

private:
  std::string port_;
  int baud_;
  bool dtr_, rts_;
  int qsz_;

  int fd_{-1};
  std::thread reader_thread_;
  std::atomic<bool> reader_running_{false};
  const std::array<uint8_t,2> CRLF_{{'\r','\n'}};

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_rx_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_rx_raw_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_tx_;
};

} // namespace atcan
