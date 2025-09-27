// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__STRUCT_HPP_
#define MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__motor_control__msg__GpioCmd __attribute__((deprecated))
#else
# define DEPRECATED__motor_control__msg__GpioCmd __declspec(deprecated)
#endif

namespace motor_control
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GpioCmd_
{
  using Type = GpioCmd_<ContainerAllocator>;

  explicit GpioCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pin_index = 0l;
      this->toggle = false;
    }
  }

  explicit GpioCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pin_index = 0l;
      this->toggle = false;
    }
  }

  // field types and members
  using _pin_index_type =
    int32_t;
  _pin_index_type pin_index;
  using _toggle_type =
    bool;
  _toggle_type toggle;

  // setters for named parameter idiom
  Type & set__pin_index(
    const int32_t & _arg)
  {
    this->pin_index = _arg;
    return *this;
  }
  Type & set__toggle(
    const bool & _arg)
  {
    this->toggle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_control::msg::GpioCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_control::msg::GpioCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_control::msg::GpioCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_control::msg::GpioCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_control::msg::GpioCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_control::msg::GpioCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_control::msg::GpioCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_control::msg::GpioCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_control::msg::GpioCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_control::msg::GpioCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_control__msg__GpioCmd
    std::shared_ptr<motor_control::msg::GpioCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_control__msg__GpioCmd
    std::shared_ptr<motor_control::msg::GpioCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GpioCmd_ & other) const
  {
    if (this->pin_index != other.pin_index) {
      return false;
    }
    if (this->toggle != other.toggle) {
      return false;
    }
    return true;
  }
  bool operator!=(const GpioCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GpioCmd_

// alias to use template instance with default allocator
using GpioCmd =
  motor_control::msg::GpioCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_control

#endif  // MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__STRUCT_HPP_
