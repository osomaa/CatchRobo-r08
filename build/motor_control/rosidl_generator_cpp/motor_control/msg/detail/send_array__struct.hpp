// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__STRUCT_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'cmds'
#include "motor_control/msg/detail/send_at__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motor_control__msg__SendArray __attribute__((deprecated))
#else
# define DEPRECATED__motor_control__msg__SendArray __declspec(deprecated)
#endif

namespace motor_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SendArray_
{
  using Type = SendArray_<ContainerAllocator>;

  explicit SendArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SendArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _cmds_type =
    std::vector<motor_control::msg::SendAt_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<motor_control::msg::SendAt_<ContainerAllocator>>>;
  _cmds_type cmds;

  // setters for named parameter idiom
  Type & set__cmds(
    const std::vector<motor_control::msg::SendAt_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<motor_control::msg::SendAt_<ContainerAllocator>>> & _arg)
  {
    this->cmds = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_control::msg::SendArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_control::msg::SendArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_control::msg::SendArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_control::msg::SendArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_control::msg::SendArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_control::msg::SendArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_control::msg::SendArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_control::msg::SendArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_control::msg::SendArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_control::msg::SendArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_control__msg__SendArray
    std::shared_ptr<motor_control::msg::SendArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_control__msg__SendArray
    std::shared_ptr<motor_control::msg::SendArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SendArray_ & other) const
  {
    if (this->cmds != other.cmds) {
      return false;
    }
    return true;
  }
  bool operator!=(const SendArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SendArray_

// alias to use template instance with default allocator
using SendArray =
  motor_control::msg::SendArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__STRUCT_HPP_
