// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__TRAITS_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motor_control/msg/detail/send_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'cmds'
#include "motor_control/msg/detail/send_at__traits.hpp"

namespace motor_control
{

namespace msg
{

inline void to_flow_style_yaml(
  const SendArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: cmds
  {
    if (msg.cmds.size() == 0) {
      out << "cmds: []";
    } else {
      out << "cmds: [";
      size_t pending_items = msg.cmds.size();
      for (auto item : msg.cmds) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SendArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cmds
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.cmds.size() == 0) {
      out << "cmds: []\n";
    } else {
      out << "cmds:\n";
      for (auto item : msg.cmds) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SendArray & msg, bool use_flow_style = false)
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
  const motor_control::msg::SendArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  motor_control::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motor_control::msg::to_yaml() instead")]]
inline std::string to_yaml(const motor_control::msg::SendArray & msg)
{
  return motor_control::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motor_control::msg::SendArray>()
{
  return "motor_control::msg::SendArray";
}

template<>
inline const char * name<motor_control::msg::SendArray>()
{
  return "motor_control/msg/SendArray";
}

template<>
struct has_fixed_size<motor_control::msg::SendArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<motor_control::msg::SendArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<motor_control::msg::SendArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__TRAITS_HPP_
