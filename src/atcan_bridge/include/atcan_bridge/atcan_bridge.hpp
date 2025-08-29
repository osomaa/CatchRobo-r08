#pragma once
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <array>
#include <algorithm>
#include <cctype>
#include <charconv>

// POSIX serial
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace atcan {

// ========== utils ==========
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

// 29bit CAN-ID -> AT生アドレス(32bit)
static inline uint32_t build_addr(uint32_t can29) {
  return ((can29 & 0x1FFFFFFFu) << 3) | 0x04u; // 下位3bitのbit2を拡張IDフラグとして立てる
}

// AT生アドレス(32bit) -> 29bit CAN-ID
static inline uint32_t split_addr(uint32_t raw_addr) {
  return ((raw_addr & ~0x00000004u) >> 3) & 0x1FFFFFFFu;
}

// "EEEEEEEE#DD..." を数値ID+payloadに
static inline bool parse_candump_frame(const std::string& s,
                                       uint32_t& canid,
                                       std::vector<uint8_t>& payload,
                                       bool allow_fd=false) {
  // trim
  const auto l = s.find_first_not_of(" \t\r\n");
  if (l == std::string::npos) return false;
  const auto r = s.find_last_not_of(" \t\r\n");
  const std::string view = s.substr(l, r - l + 1);

  const auto pos = view.find('#');
  if (pos == std::string::npos) return false;

  // ID部（0x/0X 接頭辞許容）
  size_t id_start = 0;
  if (pos >= 2 && view[0]=='0' && (view[1]=='x' || view[1]=='X')) id_start = 2;

  canid = 0;
  {
    const char* first = view.data() + id_start;
    const char* last  = view.data() + pos;
    auto rc = std::from_chars(first, last, canid, 16);
    if (rc.ec != std::errc() || rc.ptr != last) return false;
    if (canid > 0x1FFFFFFF) return false;
    canid &= 0x1FFFFFFF;
  }

  // データ部（16進以外は無視、偶数桁必須）
  payload.clear();
  size_t p = pos + 1;
  while (p < view.size() && std::isspace(static_cast<unsigned char>(view[p]))) ++p;

  std::string compact;
  compact.reserve(view.size() - p);
  for (; p < view.size(); ++p) {
    unsigned char c = static_cast<unsigned char>(view[p]);
    if (std::isxdigit(c)) compact.push_back(static_cast<char>(std::toupper(c)));
  }
  if (compact.size() % 2) return false;

  const size_t max_len = allow_fd ? 64 : 8;
  const size_t nbytes = compact.size()/2;
  if (nbytes > max_len) return false;

  payload.resize(nbytes);
  for (size_t i=0;i<nbytes;++i) {
    unsigned v=0;
    auto rc = std::from_chars(compact.data()+2*i, compact.data()+2*i+2, v, 16);
    if (rc.ec != std::errc()) return false;
    payload[i] = static_cast<uint8_t>(v);
  }
  return true;
}

// 数値ID+payload -> "EEEEEEEE#DD..."
static inline std::string format_candump_line(uint32_t can_id,
                                              const std::vector<uint8_t>& payload) {
  static const char* H = "0123456789ABCDEF";
  char idbuf[9]; idbuf[8] = '\0';           // ← 必ずNUL終端！
  uint32_t v = (can_id & 0x1FFFFFFF);
  for (int i=7; i>=0; --i) { idbuf[i] = H[v & 0xF]; v >>= 4; }
  std::string s(idbuf);
  s.push_back('#');
  for (uint8_t b : payload) { s.push_back(H[b>>4]); s.push_back(H[b&0xF]); }
  return s;
}

// ATフレーム組み立て（'AT' + addrBE + len + payload + CRLF）
static inline std::vector<uint8_t> build_at_frame(uint32_t raw_addr,
                                                  const std::vector<uint8_t>& payload) {
  std::vector<uint8_t> frame;
  frame.reserve(2+4+1+payload.size()+2);
  frame.push_back('A'); frame.push_back('T');
  frame.push_back(uint8_t((raw_addr >> 24) & 0xFF));
  frame.push_back(uint8_t((raw_addr >> 16) & 0xFF));
  frame.push_back(uint8_t((raw_addr >>  8) & 0xFF));
  frame.push_back(uint8_t( raw_addr        & 0xFF));
  frame.push_back(uint8_t(payload.size() & 0xFF));
  frame.insert(frame.end(), payload.begin(), payload.end());
  frame.push_back('\r'); frame.push_back('\n');
  return frame;
}

// ========== node ==========
class AtCanBridgeNode : public rclcpp::Node {
public:
  AtCanBridgeNode(): Node("atcan_bridge") {
    port_ = this->declare_parameter<std::string>("port", "/dev/ttyUSB0");
    baud_ = this->declare_parameter<int>("baud", 921600);
    dtr_  = this->declare_parameter<bool>("dtr", true);
    rts_  = this->declare_parameter<bool>("rts", false);
    qsz_  = this->declare_parameter<int>("queue_size", 100);

    pub_rx_     = this->create_publisher<std_msgs::msg::String>("/atcan/rx", qsz_);
    pub_rx_raw_ = this->create_publisher<std_msgs::msg::String>("/atcan/rx_raw", qsz_);
    sub_tx_     = this->create_subscription<std_msgs::msg::String>(
                    "/atcan/tx", qsz_,
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
    termios tio{}; ::tcgetattr(fd_, &tio);
    cfmakeraw(&tio);
    tio.c_cflag |= (CLOCAL | CREAD);
    tio.c_cflag &= ~CRTSCTS; // no hw flow
    // 8N1
    tio.c_cflag &= ~PARENB;
    tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;
    tio.c_cflag |= CS8;

    // speed map
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

    tio.c_cc[VMIN]  = 0; // non-blocking
    tio.c_cc[VTIME] = 0;

    if (tcsetattr(fd_, TCSANOW, &tio) != 0) {
      RCLCPP_ERROR(this->get_logger(), "tcsetattr failed");
    }

#ifdef TIOCM_DTR
    int flags = 0;
    ioctl(fd_, TIOCMGET, &flags);
    if (dtr_) flags |= TIOCM_DTR; else flags &= ~TIOCM_DTR;
#ifdef TIOCM_RTS
    if (rts_) flags |= TIOCM_RTS; else flags &= ~TIOCM_RTS;
#endif
    ioctl(fd_, TIOCMSET, &flags);
#endif

    tcflush(fd_, TCIOFLUSH);
    RCLCPP_INFO(this->get_logger(), "Serial open OK: %s @ %d bps (DTR=%s, RTS=%s)",
                port_.c_str(), baud_, dtr_?"on":"off", rts_?"on":"off");
  }

  // ===== TX path =====
  void on_tx(const std_msgs::msg::String::SharedPtr msg) {
    uint32_t can_id; std::vector<uint8_t> payload;
    if (!parse_candump_frame(msg->data, can_id, payload)) {
      RCLCPP_WARN(this->get_logger(), "TX parse error: '%s'", msg->data.c_str());
      return;
    }
    auto frame = build_at_frame(build_addr(can_id), payload);
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
        for(;;){
          auto it = std::search(buf.begin(), buf.end(), CRLF_.begin(), CRLF_.end());
          if (it == buf.end()) break;
          std::vector<uint8_t> one(buf.begin(), it+2);
          buf.erase(buf.begin(), it+2);

          pub_raw(one);
          if (one.size() >= 2+4+1+2 && one[0]=='A' && one[1]=='T' && one[one.size()-2]=='\r' && one.back()=='\n') {
            uint32_t raw_addr = (uint32_t(one[2])<<24) | (uint32_t(one[3])<<16) | (uint32_t(one[4])<<8) | uint32_t(one[5]);
            uint8_t  len      = one[6];
            if (one.size() == size_t(2+4+1+len+2)) {
              std::vector<uint8_t> payload(one.begin()+7, one.begin()+7+len);
              uint32_t can_id = split_addr(raw_addr);
              pub_rx(format_candump_line(can_id, payload));
            } else {
              RCLCPP_WARN(this->get_logger(), "RX length mismatch (len=%u, frame=%zu)", len, one.size());
            }
          } else {
            RCLCPP_WARN(this->get_logger(), "Invalid AT frame");
          }
        }
      } else {
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
