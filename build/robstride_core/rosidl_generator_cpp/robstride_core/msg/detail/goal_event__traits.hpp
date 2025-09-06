// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robstride_core:msg/GoalEvent.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__TRAITS_HPP_
#define ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robstride_core/msg/detail/goal_event__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace robstride_core
{

namespace msg
{

inline void to_flow_style_yaml(
  const GoalEvent & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: error
  {
    out << "error: ";
    rosidl_generator_traits::value_to_yaml(msg.error, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoalEvent & msg,
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

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error: ";
    rosidl_generator_traits::value_to_yaml(msg.error, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoalEvent & msg, bool use_flow_style = false)
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

}  // namespace robstride_core

namespace rosidl_generator_traits
{

[[deprecated("use robstride_core::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robstride_core::msg::GoalEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  robstride_core::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robstride_core::msg::to_yaml() instead")]]
inline std::string to_yaml(const robstride_core::msg::GoalEvent & msg)
{
  return robstride_core::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robstride_core::msg::GoalEvent>()
{
  return "robstride_core::msg::GoalEvent";
}

template<>
inline const char * name<robstride_core::msg::GoalEvent>()
{
  return "robstride_core/msg/GoalEvent";
}

template<>
struct has_fixed_size<robstride_core::msg::GoalEvent>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robstride_core::msg::GoalEvent>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robstride_core::msg::GoalEvent>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__TRAITS_HPP_
