// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__BUILDER_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_control/msg/detail/gpio_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_control
{

namespace msg
{

namespace builder
{

class Init_GpioCmd_toggle
{
public:
  explicit Init_GpioCmd_toggle(::motor_control::msg::GpioCmd & msg)
  : msg_(msg)
  {}
  ::motor_control::msg::GpioCmd toggle(::motor_control::msg::GpioCmd::_toggle_type arg)
  {
    msg_.toggle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_control::msg::GpioCmd msg_;
};

class Init_GpioCmd_pin_index
{
public:
  Init_GpioCmd_pin_index()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GpioCmd_toggle pin_index(::motor_control::msg::GpioCmd::_pin_index_type arg)
  {
    msg_.pin_index = std::move(arg);
    return Init_GpioCmd_toggle(msg_);
  }

private:
  ::motor_control::msg::GpioCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_control::msg::GpioCmd>()
{
  return motor_control::msg::builder::Init_GpioCmd_pin_index();
}

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__BUILDER_HPP_
