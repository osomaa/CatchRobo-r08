#pragma once
#include <vector>
#include <string>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace {

inline void set_err(std::string* err, const std::string& msg) {
  if (err) *err = msg;
}

inline speed_t map_baud(int baud) {
  switch (baud) {
    case 9600:   return B9600;
    case 19200:  return B19200;
    case 38400:  return B38400;
    case 57600:  return B57600;
    case 115200: return B115200;
#ifdef B230400
    case 230400: return B230400;
#endif
#ifdef B460800
    case 460800: return B460800;
#endif
#ifdef B500000
    case 500000: return B500000;
#endif
#ifdef B921600
    case 921600: return B921600;
#endif
    default:     return B115200; // フォールバック
  }
}

} // namespace

inline bool open_serial(int& fd_out,
                 const std::string& port = "/dev/ttyUSB0",
                 int baud = 921600,
                 bool dtr_on = false,
                 bool rts_on = false,
                 std::string* err = nullptr)
{
  fd_out = -1;

  // 1) open (non-blocking, no controlling TTY)
  int fd = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (fd < 0) {
    set_err(err, std::string("open(") + port + ") failed: " + std::strerror(errno));
    return false;
  }

  // 2) termios 現在値を取得
  struct termios tio{};
  if (::tcgetattr(fd, &tio) != 0) {
    std::string msg = std::string("tcgetattr failed: ") + std::strerror(errno);
    ::close(fd);
    set_err(err, msg);
    return false;
  }

  // 3) RAW + 8N1
  ::cfmakeraw(&tio);
  tio.c_cflag |= (CLOCAL | CREAD);
  tio.c_cflag &= ~CRTSCTS;      // HWフロー OFF（必要ならONに）
  tio.c_cflag &= ~PARENB;       // N
  tio.c_cflag &= ~CSTOPB;       // 1
  tio.c_cflag &= ~CSIZE;        // 8
  tio.c_cflag |= CS8;
  tio.c_iflag &= ~(IXON | IXOFF | IXANY); // SWフロー OFF

  // 4) 速度設定
  const speed_t bs = map_baud(baud);
  if (cfsetispeed(&tio, bs) != 0 || cfsetospeed(&tio, bs) != 0) {
    std::string msg = std::string("cfset*speed failed: ") + std::strerror(errno);
    ::close(fd);
    set_err(err, msg);
    return false;
  }

  // 5) 非カノニカルの即時返し（readはデータ無ければEAGAIN相当）
  tio.c_cc[VMIN]  = 0;
  tio.c_cc[VTIME] = 0;

  if (::tcsetattr(fd, TCSANOW, &tio) != 0) {
    std::string msg = std::string("tcsetattr failed: ") + std::strerror(errno);
    ::close(fd);
    set_err(err, msg);
    return false;
  }

  // 6) DTR/RTS（可能な環境のみ）
#ifdef TIOCM_DTR
  int mflags = 0;
  if (::ioctl(fd, TIOCMGET, &mflags) != -1) {
    if (dtr_on) mflags |= TIOCM_DTR; else mflags &= ~TIOCM_DTR;
#ifdef TIOCM_RTS
    if (rts_on) mflags |= TIOCM_RTS; else mflags &= ~TIOCM_RTS;
#endif
    (void)::ioctl(fd, TIOCMSET, &mflags); 
  }
#endif

  ::tcflush(fd, TCIOFLUSH);

  fd_out = fd;
  return true;
}

inline void close_serial(int& fd) {
  if (fd >= 0) { ::close(fd); fd = -1; }
}

inline bool send_frame(int fd, const std::vector<uint8_t>& frame) {
  ssize_t n = ::write(fd, frame.data(), frame.size());
  return n == static_cast<ssize_t>(frame.size());
}