// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_control:msg/ReturnAt.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__STRUCT_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motor_control__msg__ReturnAt __attribute__((deprecated))
#else
# define DEPRECATED__motor_control__msg__ReturnAt __declspec(deprecated)
#endif

namespace motor_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ReturnAt_
{
  using Type = ReturnAt_<ContainerAllocator>;

  explicit ReturnAt_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->position = 0.0f;
    }
  }

  explicit ReturnAt_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->position = 0.0f;
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _position_type =
    float;
  _position_type position;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__position(
    const float & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_control::msg::ReturnAt_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_control::msg::ReturnAt_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_control::msg::ReturnAt_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_control::msg::ReturnAt_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_control::msg::ReturnAt_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_control::msg::ReturnAt_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_control::msg::ReturnAt_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_control::msg::ReturnAt_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_control::msg::ReturnAt_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_control::msg::ReturnAt_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_control__msg__ReturnAt
    std::shared_ptr<motor_control::msg::ReturnAt_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_control__msg__ReturnAt
    std::shared_ptr<motor_control::msg::ReturnAt_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReturnAt_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReturnAt_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReturnAt_

// alias to use template instance with default allocator
using ReturnAt =
  motor_control::msg::ReturnAt_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__RETURN_AT__STRUCT_HPP_
