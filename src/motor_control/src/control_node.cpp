

class ControlNode : public rclcpp::Node {
public:
  ControlNode() : rclcpp::Node("control_node") {
    pub_cmd_batch_ = this->create_publisher<motor_control::msg::SendArray>("motor/cmd_batch", 10);
    sub_done_ = this->create_subscription<std_msgs::msg::Bool>(
      "motor/observe/done", 10,
      std::bind(&ControlNode::on_done, this, std::placeholders::_1));
  }
  ~ControlNode() override {}        
private:
  void on_done(const std_msgs::msg::Bool::SharedPtr msg) {
    if(msg->data) {
      make_batch(cmd_batch);
      pub_cmd_batch_->publish(cmd_batch);
    } else {
      pub_cmd_batch_->publish(cmd_batch)
    }
  }

  bool make_batch(motor_control::msg::SendArray& batch) {
    std::string line;
    getline(ifs, str_buf);
    if (!std::getline(ifs, line)) {
      return false;
    }
    
    std::istringstream ss(line);
    std::string cell;
    batch.cmds.clear();
    
    while (true) {
      motor_control::msg::SendAt cmd;
      if (!std::getline(ss, cell, ',')) break;
      cmd.id = std::stoi(cell);
      if (!std::getline(ss, cell, ',')) break;
      cmd.position = std::stof(cell);
      batch.cmds.push_back(cmd);
    }
    return !batch.cmds.empty();
  }

  std::ifstream ifs(input_csv_file_path);
  motor_control::msg::SendArray cmd_batch;
  rclcpp::Publisher<motor_control::msg::SendArray>::SharedPtr pub_cmd_batch_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr sub_done_;
};
 
int main(int argc, char** argv) {
   rclcpp::init(argc, argv);
   auto node = std::make_shared<ControlNode>();
   rclcpp::spin(node);
   rclcpp::shutdown();
   return 0;
};