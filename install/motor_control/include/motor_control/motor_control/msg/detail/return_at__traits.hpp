// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_control:msg/ReturnAt.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__TRAITS_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motor_control/msg/detail/return_at__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace motor_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const ReturnAt & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ReturnAt & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ReturnAt & msg, bool use_flow_style = false)
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
  const motor_control::msg::ReturnAt & msg,
  std::ostream & out, size_t indentation = 0)
{
  motor_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motor_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const motor_control::msg::ReturnAt & msg)
{
  return motor_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motor_control::msg::ReturnAt>()
{
  return "motor_control::msg::ReturnAt";
}

template<>
inline const char * name<motor_control::msg::ReturnAt>()
{
  return "motor_control/msg/ReturnAt";
}

template<>
struct has_fixed_size<motor_control::msg::ReturnAt>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<motor_control::msg::ReturnAt>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<motor_control::msg::ReturnAt>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__TRAITS_HPP_
