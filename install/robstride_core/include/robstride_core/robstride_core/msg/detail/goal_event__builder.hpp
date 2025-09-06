// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robstride_core:msg/GoalEvent.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__BUILDER_HPP_
#define ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robstride_core/msg/detail/goal_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robstride_core
{

namespace msg
{

namespace builder
{

class Init_GoalEvent_stamp
{
public:
  explicit Init_GoalEvent_stamp(::robstride_core::msg::GoalEvent & msg)
  : msg_(msg)
  {}
  ::robstride_core::msg::GoalEvent stamp(::robstride_core::msg::GoalEvent::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robstride_core::msg::GoalEvent msg_;
};

class Init_GoalEvent_error
{
public:
  explicit Init_GoalEvent_error(::robstride_core::msg::GoalEvent & msg)
  : msg_(msg)
  {}
  Init_GoalEvent_stamp error(::robstride_core::msg::GoalEvent::_error_type arg)
  {
    msg_.error = std::move(arg);
    return Init_GoalEvent_stamp(msg_);
  }

private:
  ::robstride_core::msg::GoalEvent msg_;
};

class Init_GoalEvent_state
{
public:
  explicit Init_GoalEvent_state(::robstride_core::msg::GoalEvent & msg)
  : msg_(msg)
  {}
  Init_GoalEvent_error state(::robstride_core::msg::GoalEvent::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_GoalEvent_error(msg_);
  }

private:
  ::robstride_core::msg::GoalEvent msg_;
};

class Init_GoalEvent_id
{
public:
  Init_GoalEvent_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoalEvent_state id(::robstride_core::msg::GoalEvent::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_GoalEvent_state(msg_);
  }

private:
  ::robstride_core::msg::GoalEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robstride_core::msg::GoalEvent>()
{
  return robstride_core::msg::builder::Init_GoalEvent_id();
}

}  // namespace robstride_core

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__BUILDER_HPP_
