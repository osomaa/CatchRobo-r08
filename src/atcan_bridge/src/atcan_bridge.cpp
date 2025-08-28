#include "atcan_bridge/atcan_bridge.hpp"

int main(int argc, char** argv){
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<atcan::AtCanBridgeNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
  } catch (const std::exception& e) {
    fprintf(stderr, "Fatal: %s\n", e.what());
    rclcpp::shutdown();
    return 1;
  }
  return 0;
}
