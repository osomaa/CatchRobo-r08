#include <rclcpp/rclcpp.hpp>
#include <vector>

inline uint32_t build_addr(uint8_t mode5, uint16_t data16, uint8_t id8) {
  uint32_t addr = (uint32_t(mode5) << 27) | (uint32_t(data16) << 11) | ((uint32_t(id8)) << 3) | 0x04u;
  return addr; 
}
std::vector<uint8_t> payload(uint16_t val1, uint16_t val2, uint16_t val3, uint16_t val4) {
  std::vector<uint8_t> bytes;
    bytes.reserve(8);
    bytes.push_back(val1 & 0xFF);
    bytes.push_back((val1 >> 8) & 0xFF);
    bytes.push_back(val2 & 0xFF);
    bytes.push_back((val2 >> 8) & 0xFF);
    bytes.push_back(val3 & 0xFF);
    bytes.push_back((val3 >> 8) & 0xFF);
    bytes.push_back(val4 & 0xFF);
    bytes.push_back((val4 >> 8) & 0xFF);
    return bytes;
}
std::vector<uint8_t> cmd2at (uint8_t mode5, uint16_t data16, uint8_t id8, uint16_t com1, uint16_t com2, uint16_t com3, uint16_t com4) {
    uint32_t addr = build_addr(mode5, data16, id8);
    std::vector<uint8_t> payload = payload(com1, com2, com3, com4);

    std::vector<uint8_t> frame;
    frame.reserve(2+4+1+payload.size()+2);
    frame.push_back('A'); frame.push_back('T');
    frame.push_back((addr >> 24) & 0xFF);   
    frame.push_back((addr >> 16) & 0xFF);
    frame.push_back((addr >> 8) & 0xFF);
    frame.push_back((addr >> 0) & 0xFF);
    frame.push_back(payload.size() & 0xFF);
    frame.insert(frame.end(), payload.begin(), payload.end());
    frame.push_back('\r'); frame.push_back('\n');
  return frame; 
}

uint8_t split_frame (std::vector<uint8_t> frame, uint32_t& addr, uint64_t& payload) {
    addr = (uint32_t(frame[2]) << 24) | (uint32_t(frame[3]) << 16) | (uint32_t(frame[4]) << 8) | uint32_t(frame[5]);
    uint8_t payload_size = frame[6];
    payload = (uint64_t(frame[7]) << 56) | (uint64_t(frame[8]) << 48) | (uint64_t(frame[9]) << 40) | (uint64_t(frame[10]) << 32) |
              (uint64_t(frame[11]) << 24) | (uint64_t(frame[12]) << 16) | (uint64_t(frame[13]) << 8) | uint64_t(frame[14]);
    return payload_size;
}
void split_addr (uint32_t addr, uint8_t& mode5, uint16_t& data16, uint8_t& id8) {
    mode5 = (addr >> 27) & 0x1F;
    data16 = (addr >> 11) & 0xFFFF;
    id8 = (addr >> 3) & 0xFF;
}
void split_payload (uint64_t payload, uint16_t& com1, uint16_t& com2, uint16_t& com3, uint16_t& com4) {
    com1 = (payload >> 28) & 0xFFFF;
    com2 = (payload >> 12) & 0xFFFF;
    com3 = (payload >> 16) & 0xFFFF;
    com4 = (payload >> 0) & 0xFFFF;
}
std::vector<uint8_t> at2cmd (const std::vector<uint8_t>& frame) {
    uint32_t addr;
    uint64_t payload;
    uint8_t payload_size = split_frame(frame, addr, payload);
    uint8_t mode5;
    uint16_t data16;
    uint8_t id8;
    split_addr(addr, mode5, data16, id8);
    uint16_t com1, com2, com3, com4;
    split_payload(payload, com1, com2, com3, com4);
    return cmd2at(mode5, data16, id8, com1, com2, com3, com4);
}

