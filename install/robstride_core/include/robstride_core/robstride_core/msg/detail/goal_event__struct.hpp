// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robstride_core:msg/GoalEvent.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__STRUCT_HPP_
#define ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robstride_core__msg__GoalEvent __attribute__((deprecated))
#else
# define DEPRECATED__robstride_core__msg__GoalEvent __declspec(deprecated)
#endif

namespace robstride_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GoalEvent_
{
  using Type = GoalEvent_<ContainerAllocator>;

  explicit GoalEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->state = "";
      this->error = 0.0f;
    }
  }

  explicit GoalEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc),
    stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->state = "";
      this->error = 0.0f;
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;
  using _error_type =
    float;
  _error_type error;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__error(
    const float & _arg)
  {
    this->error = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robstride_core::msg::GoalEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const robstride_core::msg::GoalEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robstride_core::msg::GoalEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robstride_core::msg::GoalEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robstride_core__msg__GoalEvent
    std::shared_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robstride_core__msg__GoalEvent
    std::shared_ptr<robstride_core::msg::GoalEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoalEvent_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->error != other.error) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoalEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoalEvent_

// alias to use template instance with default allocator
using GoalEvent =
  robstride_core::msg::GoalEvent_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robstride_core

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__STRUCT_HPP_
