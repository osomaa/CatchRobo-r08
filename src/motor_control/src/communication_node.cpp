

class CommunicationNode : public rclcpp::Node {
public:
  CommunicationNode() : Node("communication_node") {
    auto qos = rclcpp::QoS(rclcpp::KeepLast(10)).reliable();
    sub_cmd_ = create_subscription<robstride_core::msg::MitAt>(
      "motor/cmd", qos,
      std::bind(&CommunicationNode::on_cmd, this, std::placeholders::_1));
  }
private:
  void on_cmd(const robstride_core::msg::MitAt::SharedPtr msg) {
    uint8_t id = msg->id;
    float position = msg->position;
    float velocity = msg->velocity;
    float torque = msg->torque;
    float kp = msg->kp;
    float kd = msg->kd;
  }
}