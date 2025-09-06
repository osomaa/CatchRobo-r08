// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robstride_core:msg/MitCmd.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__BUILDER_HPP_
#define ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robstride_core/msg/detail/mit_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robstride_core
{

namespace msg
{

namespace builder
{

class Init_MitCmd_stamp
{
public:
  explicit Init_MitCmd_stamp(::robstride_core::msg::MitCmd & msg)
  : msg_(msg)
  {}
  ::robstride_core::msg::MitCmd stamp(::robstride_core::msg::MitCmd::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

class Init_MitCmd_kd
{
public:
  explicit Init_MitCmd_kd(::robstride_core::msg::MitCmd & msg)
  : msg_(msg)
  {}
  Init_MitCmd_stamp kd(::robstride_core::msg::MitCmd::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return Init_MitCmd_stamp(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

class Init_MitCmd_kp
{
public:
  explicit Init_MitCmd_kp(::robstride_core::msg::MitCmd & msg)
  : msg_(msg)
  {}
  Init_MitCmd_kd kp(::robstride_core::msg::MitCmd::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_MitCmd_kd(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

class Init_MitCmd_torque
{
public:
  explicit Init_MitCmd_torque(::robstride_core::msg::MitCmd & msg)
  : msg_(msg)
  {}
  Init_MitCmd_kp torque(::robstride_core::msg::MitCmd::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return Init_MitCmd_kp(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

class Init_MitCmd_velocity
{
public:
  explicit Init_MitCmd_velocity(::robstride_core::msg::MitCmd & msg)
  : msg_(msg)
  {}
  Init_MitCmd_torque velocity(::robstride_core::msg::MitCmd::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_MitCmd_torque(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

class Init_MitCmd_position
{
public:
  explicit Init_MitCmd_position(::robstride_core::msg::MitCmd & msg)
  : msg_(msg)
  {}
  Init_MitCmd_velocity position(::robstride_core::msg::MitCmd::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_MitCmd_velocity(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

class Init_MitCmd_id
{
public:
  Init_MitCmd_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MitCmd_position id(::robstride_core::msg::MitCmd::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_MitCmd_position(msg_);
  }

private:
  ::robstride_core::msg::MitCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robstride_core::msg::MitCmd>()
{
  return robstride_core::msg::builder::Init_MitCmd_id();
}

}  // namespace robstride_core

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__BUILDER_HPP_
