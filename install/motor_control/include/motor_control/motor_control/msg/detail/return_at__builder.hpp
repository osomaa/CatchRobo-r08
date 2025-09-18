// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_control:msg/ReturnAt.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__BUILDER_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_control/msg/detail/return_at__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_control
{

namespace msg
{

namespace builder
{

class Init_ReturnAt_position
{
public:
  explicit Init_ReturnAt_position(::motor_control::msg::ReturnAt & msg)
  : msg_(msg)
  {}
  ::motor_control::msg::ReturnAt position(::motor_control::msg::ReturnAt::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_control::msg::ReturnAt msg_;
};

class Init_ReturnAt_id
{
public:
  Init_ReturnAt_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReturnAt_position id(::motor_control::msg::ReturnAt::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_ReturnAt_position(msg_);
  }

private:
  ::motor_control::msg::ReturnAt msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_control::msg::ReturnAt>()
{
  return motor_control::msg::builder::Init_ReturnAt_id();
}

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__BUILDER_HPP_
