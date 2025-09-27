// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__TRAITS_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motor_control/msg/detail/gpio_cmd__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motor_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const GpioCmd & msg,
  std::ostream & out)
{
  out << "{";
  // member: pin_index
  {
    out << "pin_index: ";
    rosidl_generator_traits::value_to_yaml(msg.pin_index, out);
    out << ", ";
  }

  // member: toggle
  {
    out << "toggle: ";
    rosidl_generator_traits::value_to_yaml(msg.toggle, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GpioCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pin_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pin_index: ";
    rosidl_generator_traits::value_to_yaml(msg.pin_index, out);
    out << "\n";
  }

  // member: toggle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toggle: ";
    rosidl_generator_traits::value_to_yaml(msg.toggle, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GpioCmd & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace motor_control

namespace rosidl_generator_traits
{

[[deprecated("use motor_control::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const motor_control::msg::GpioCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  motor_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motor_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const motor_control::msg::GpioCmd & msg)
{
  return motor_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motor_control::msg::GpioCmd>()
{
  return "motor_control::msg::GpioCmd";
}

template<>
inline const char * name<motor_control::msg::GpioCmd>()
{
  return "motor_control/msg/GpioCmd";
}

template<>
struct has_fixed_size<motor_control::msg::GpioCmd>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motor_control::msg::GpioCmd>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<motor_control::msg::GpioCmd>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__TRAITS_HPP_
