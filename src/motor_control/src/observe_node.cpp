class ObserveNode : public rclcpp::Node{
public:
    ObserveNode() : rclcpp::Node("observe_node") {
        pub_cmd_ = create_publisher<motor_control::msg::MotorConfig>("motor/cmd", 10);
        sub_cmd_batch_ = create_subscription<motor_control::msg::SendArray>(
            "motor/cmd_batch", 10,
            std::bind(&ObserveNode::on_cmd_batch, this, std::placeholders::_1));
        sub_state_ = create_subscription<motor_control::msg::ReturnAt>(
            "motor/state", 10,
            std::bind(&ObserveNode::on_state, this, std::placeholders::_1));
        pub_done_ = create_publisher<std_msgs::msg::Bool>("motor/observe/done", 10);

        timer_ = create_wall_timer(
            std::chrono::milliseconds(50),
            std::bind(&ObserveNode::tick, this));
    }
    ~ObserveNode() override {
    }

private:

    static constexpr int kjoints = 6;

    void on_cmd_batch(const motor_control::msg::SendArray::SharedPtr msg) {
        last_cmds_ = msg;
        for (const auto& cmd : msg->cmds) {
            pub_cmd_->publish(cmd);
        };
    }
    void on_state(const motor_control::msg::ReturnAt::SharedPtr msg) {
        int id_num = msg->id-1;
        last_state_[id_num] = *msg;
    }
    bool is_different(const motor_control::msg::SendArray& cmd, const motor_control::msg::ReturnAt[]& state) {\
        bool different = false;
        for (const auto& c : cmd.cmds) {
            int id_num = c.id - 1;
            const auto& s = state[id_num];
            if (std::abs(c.position - s.position) > 0.01f) return true;
            if (std::abs(c.velocity - s.velocity) > 0.01f) return true;
            if (std::abs(c.torque - s.torque) > 0.01f) return true;
        }
        return different;
    }
    void tick() {
        std::lock_guard<std::mutex> lock(m_);
        bool res = is_different(*last_cmds_, last_state_);
        pub_done_->publish(std_msgs::msg::Bool().set__data(!res));
    }


    std::mutex m_;
    motor_control::msg::SendArray last_cmds_{};
    std::array<motor_control::msg::ReturnAt, kjoints> last_state_{};

    rclcpp::Publisher<motor_control::msg::MotorConfig>::SharedPtr pub_cmd_;
    rclcpp::Subscription<motor_control::msg::MotorConfigBatch>::SharedPtr sub_cmd_batch_;
    rclcpp::Subscription<motor_control::msg::ReturnAt>::SharedPtr sub_state_;
};

main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ObserveNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
