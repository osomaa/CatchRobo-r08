// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__BUILDER_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_control/msg/detail/send_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_control
{

namespace msg
{

namespace builder
{

class Init_SendArray_cmds
{
public:
  Init_SendArray_cmds()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::motor_control::msg::SendArray cmds(::motor_control::msg::SendArray::_cmds_type arg)
  {
    msg_.cmds = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_control::msg::SendArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_control::msg::SendArray>()
{
  return motor_control::msg::builder::Init_SendArray_cmds();
}

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__BUILDER_HPP_
