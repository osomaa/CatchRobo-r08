#include <rclcpp/rclcpp.hpp>
#include <vector>

static const std::array<uint8_t,2> CRLF_{{'\r','\n'}};

inline uint32_t build_addr(uint8_t mode5, uint16_t data16, uint8_t id8) {
  uint32_t addr = (uint32_t(mode5) << 27) | (uint32_t(data16) << 11) | ((uint32_t(id8)) << 3) | 0x04u;
  return addr; 
}
std::vector<uint8_t> payload(uint16_t val1, uint16_t val2, uint32_t val3) {
  std::vector<uint8_t> bytes;
    bytes.reserve(8);
    bytes.push_back(val1 & 0xFF);
    bytes.push_back((val1 >> 8) & 0xFF);
    bytes.push_back(val2 & 0xFF);
    bytes.push_back((val2 >> 8) & 0xFF);
    bytes.push_back(val3 & 0xFF);
    bytes.push_back((val3 >> 8) & 0xFF);
    bytes.push_back((val3 >> 16) & 0xFF);
    bytes.push_back((val3 >> 24) & 0xFF);
    return bytes;
}
std::vector<uint8_t> cmd2at (uint8_t mode5, uint16_t data16, uint8_t id8, uint16_t com1, uint16_t com2, uint32_t com3) {
    uint32_t addr = build_addr(mode5, data16, id8);
    std::vector<uint8_t> payload = payload(com1, com2, com3);

    std::vector<uint8_t> frame;
    frame.reserve(2+4+1+payload.size()+2);

    frame.push_back('A'); 
    frame.push_back('T');
    frame.push_back((addr >> 24) & 0xFF);   
    frame.push_back((addr >> 16) & 0xFF);
    frame.push_back((addr >> 8) & 0xFF);
    frame.push_back((addr >> 0) & 0xFF);
    frame.push_back(payload.size() & 0xFF);
    frame.insert(frame.end(), payload.begin(), payload.end());
    frame.push_back('\r'); 
    frame.push_back('\n');
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
void analysis_payload (uint64_t payload, float& val) {
    uint32_t val_int = (payload & 0xFF) << 24 | ((payload >> 8) & 0xFF) << 16 | ((payload >> 16) & 0xFF) << 8 | ((payload >> 24) & 0xFF);
    memcpy(&val, &val_int, sizeof(float));
}
std::vector<uint8_t> at2cmd (const std::vector<uint8_t>& frame) {
    uint32_t addr;
    uint64_t payload;
    uint8_t payload_size = split_frame(frame, addr, payload);
    uint8_t mode5;
    uint16_t data16;
    uint8_t id8;
    split_addr(addr, mode5, data16, id8);
    float val;
    analysis_payload(payload, val);
    return cmd2at(mode5, data16, id8, com1, com2, com3, com4);
}

//static_cast<uint16_t>
int float2uint(float x, float x_min, float x_max, int bits) {
    float span = x_max - x_min;
    float offset = x_min;

    if (x < x_min) x = x_min;
    else if (x > x_max) x = x_max;

    return (int)( (x - offset) * (float)((1 << bits) - 1) / span );
}
 
float uint2float(int x_int, float x_min, float x_max, int bits) {
    float span = x_max - x_min;
    float offset = x_min;
    return (float)x_int * span / (float)((1 << bits) - 1) + offset;
}