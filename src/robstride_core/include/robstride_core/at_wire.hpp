#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace atwire {

// 29bit CAN-ID -> AT 生アドレス(32bit)
// 下位3bitのbit2を拡張IDフラグとして立てる仕様を踏襲
static inline uint32_t build_addr(uint32_t can29) {
  return ((can29 & 0x1FFFFFFFu) << 3) | 0x04u;
}

// "AT" + addr(32bit BE) + len(1) + payload + CRLF を構築
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

static inline std::string hex_dump(const std::vector<uint8_t>& b) {
  static constexpr char H[] = "0123456789ABCDEF";
  std::string s; s.reserve(b.size()*3);
  for (size_t i=0;i<b.size();++i){
    uint8_t x=b[i];
    s.push_back(H[x>>4]); s.push_back(H[x&0xF]);
    if (i+1<b.size()) s.push_back(' ');
  }
  return s;
}

} // namespace atwire
