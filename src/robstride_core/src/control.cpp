#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include "robstride_core/msg/goal_event.hpp"
#include "robstride_core/msg/mit_cmd.hpp"
#include <builtin_interfaces/msg/time.hpp>
#include <rclcpp/time.hpp>

#include <unordered_map>
#include <cstdint>
#include <cmath>
#include <string>
#include <algorithm>

struct TargetState {
  double target_pos = 0.0;
  rclcpp::Time deadline;
  int stable_hits = 0;
  std::string last_state;
};

class ControlNode : public rclcpp::Node {
public:
  ControlNode() : Node("control_node") {
    // 判定パラメータ
    epsilon_     = declare_parameter<double>("epsilon", 0.01);
    stable_need_ = declare_parameter<int>("stable_need", 3);
    timeout_ms_  = declare_parameter<int>("timeout_ms", 1000);

    // 観測のインデックス（/robstride/obs は [id,pos_u16,vel_u16,tor_u8,kp_u16,kd_u16]）
    idx_id_  = declare_parameter<int>("idx_id", 0);
    idx_pos_ = declare_parameter<int>("idx_pos", 1); // pos_u16（必要に応じてスケール戻し）

    // pos の逆スケール（at_bridge と合わせる）
    pos_scale_ = declare_parameter<double>("pos_scale", 1000.0);

    // 到達イベント
    pub_goal_ = create_publisher<robstride_core::msg::GoalEvent>(
      "robstride/goal_event", rclcpp::QoS(10).reliable().transient_local());

    // 上位からの命令を受けて at ブリッジに流す公式トピックに転送
    sub_cmd_in_ = create_subscription<robstride_core::msg::MitCmd>(
      "/robstride/cmd/mit_in", 50,
      std::bind(&ControlNode::on_cmd_in, this, std::placeholders::_1));
    pub_cmd_out_ = create_publisher<robstride_core::msg::MitCmd>("/robstride/cmd/mit", 50);

    // 観測の自動入力を購読
    sub_obs_ = create_subscription<std_msgs::msg::UInt16MultiArray>(
      "/robstride/obs", 100,
      std::bind(&ControlNode::on_observe, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "control_node ready");
  }

private:
  void on_cmd_in(const robstride_core::msg::MitCmd &m) {
    auto &st = targets_[m.id];
    st.target_pos = m.position; // float の目標（rad 等）
    st.deadline   = now() + rclcpp::Duration::from_seconds(timeout_ms_/1000.0);
    st.stable_hits = 0;

    pub_cmd_out_->publish(m); // at_bridge へ
  }

  void on_observe(const std_msgs::msg::UInt16MultiArray::SharedPtr obs) {
    if (obs->data.size() <= static_cast<size_t>(std::max(idx_id_, idx_pos_))) return;

    const uint8_t id = static_cast<uint8_t>(obs->data[idx_id_] & 0xFF);

    // pos は u16（at_bridge スケール）なので float に戻す
    const double pos = static_cast<double>(obs->data[idx_pos_]) / std::max(1.0, pos_scale_);

    auto it = targets_.find(id);
    if (it == targets_.end()) return;

    auto &st = it->second;
    const double err = std::abs(pos - st.target_pos);
    if (err <= epsilon_) st.stable_hits++; else st.stable_hits = 0;

    std::string state;
    if (st.stable_hits >= stable_need_) state = "goal";
    else if (now() > st.deadline)       state = "timeout";
    else                                state = "wait";

    if (state != st.last_state) {
      robstride_core::msg::GoalEvent ev;
      ev.id = id; ev.state = state; ev.error = static_cast<float>(err);
      ev.stamp = this->get_clock()->now();
      pub_goal_->publish(ev);
      st.last_state = state;
    }
  }

private:
  rclcpp::Subscription<robstride_core::msg::MitCmd>::SharedPtr sub_cmd_in_;
  rclcpp::Publisher<robstride_core::msg::MitCmd>::SharedPtr     pub_cmd_out_;
  rclcpp::Subscription<std_msgs::msg::UInt16MultiArray>::SharedPtr sub_obs_;
  rclcpp::Publisher<robstride_core::msg::GoalEvent>::SharedPtr  pub_goal_;

  std::unordered_map<uint8_t, TargetState> targets_;

  double epsilon_; int stable_need_; int timeout_ms_;
  int idx_id_, idx_pos_;
  double pos_scale_;
};

int main(int argc, char** argv){
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControlNode>());
  rclcpp::shutdown();
  return 0;
}
