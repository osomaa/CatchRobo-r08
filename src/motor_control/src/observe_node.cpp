#include <rclcpp/rclcpp.hpp>
#include <motor_control/msg/send_at.hpp>        // ← 念のため明示
#include <motor_control/msg/return_at.hpp>
#include <motor_control/msg/send_array.hpp>
#include <std_msgs/msg/bool.hpp>
#include <array>
#include <mutex>
#include <cmath>
#include <functional>

class ObserveNode : public rclcpp::Node{
public:
  ObserveNode() : rclcpp::Node("observe_node") {
    pub_cmd_ = create_publisher<motor_control::msg::SendAt>("motor/cmd", 10);
    sub_cmd_batch_ = create_subscription<motor_control::msg::SendArray>(
      "motor/cmd_batch", 10,
      std::bind(&ObserveNode::on_cmd_batch, this, std::placeholders::_1));
    sub_state_ = create_subscription<motor_control::msg::ReturnAt>(
      "motor/state", 10,
      std::bind(&ObserveNode::on_state, this, std::placeholders::_1));
    pub_done_ = create_publisher<std_msgs::msg::Bool>("motor/observe/done", 10);

    // 明示初期化（全要素デフォルト値に）
    last_state_.fill(motor_control::msg::ReturnAt{});

    timer_ = create_wall_timer(
      std::chrono::milliseconds(50),
      std::bind(&ObserveNode::tick, this));
  }

private:
  static constexpr int kjoints = 6;

  void on_cmd_batch(const motor_control::msg::SendArray::SharedPtr msg) {
    std::lock_guard<std::mutex> lk(m_);

    for (const auto& cmd : msg->cmds) {
      if (cmd.id < 1 || cmd.id > kjoints) {
        RCLCPP_WARN(get_logger(), "Ignore cmd with out-of-range id=%u", cmd.id);
        continue;
      }
      pub_cmd_->publish(cmd);
      std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    // 最後にスナップショットを更新
    last_cmds_ = *msg;
  }

  void on_state(const motor_control::msg::ReturnAt::SharedPtr msg) {
    if (!msg) return;
    if (msg->id < 1 || msg->id > kjoints) {
      RCLCPP_WARN(get_logger(), "Ignore state with out-of-range id=%u", msg->id);
      return;
    }
    std::lock_guard<std::mutex> lk(m_);
    const int idx = static_cast<int>(msg->id) - 1;
    last_state_[idx] = *msg;
    have_state_[idx] = true;
  }

  static bool almost_equal(float a, float b, float eps = 0.01f) {
    return std::fabs(a - b) <= eps;
  }

  bool is_different_unlocked(const motor_control::msg::SendArray& cmd) const {
    for (const auto& c : cmd.cmds) {
      if (c.id < 1 || c.id > kjoints) continue;  // すでに warn 済み
      const int idx = static_cast<int>(c.id) - 1;

      // まだこのIDのstateを受け取っていないなら“違う”扱いにしておく
      if (!have_state_[idx]) return true;

      const auto& s = last_state_[idx];
      if (!almost_equal(c.position, s.position)) return true;
    }
    return false;
  }

  void tick() {
    std::lock_guard<std::mutex> lk(m_);

    if (last_cmds_.cmds.empty()) {
      return;
    }

    const bool diff = is_different_unlocked(last_cmds_);
    std_msgs::msg::Bool done;
    done.data = !diff;
    pub_done_->publish(done);
  }

  std::mutex m_;
  motor_control::msg::SendArray last_cmds_{};
  std::array<motor_control::msg::ReturnAt, kjoints> last_state_{};
  std::array<bool, kjoints> have_state_{{false,false,false,false,false,false}};
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<motor_control::msg::SendAt>::SharedPtr pub_cmd_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_done_;
  rclcpp::Subscription<motor_control::msg::SendArray>::SharedPtr sub_cmd_batch_;
  rclcpp::Subscription<motor_control::msg::ReturnAt>::SharedPtr sub_state_;
};


int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ObserveNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
