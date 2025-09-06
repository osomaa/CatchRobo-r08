// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robstride_core:msg/MitCmd.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__STRUCT_HPP_
#define ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__STRUCT_HPP_

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
# define DEPRECATED__robstride_core__msg__MitCmd __attribute__((deprecated))
#else
# define DEPRECATED__robstride_core__msg__MitCmd __declspec(deprecated)
#endif

namespace robstride_core
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MitCmd_
{
  using Type = MitCmd_<ContainerAllocator>;

  explicit MitCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->torque = 0.0f;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  explicit MitCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->position = 0.0f;
      this->velocity = 0.0f;
      this->torque = 0.0f;
      this->kp = 0.0f;
      this->kd = 0.0f;
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _position_type =
    float;
  _position_type position;
  using _velocity_type =
    float;
  _velocity_type velocity;
  using _torque_type =
    float;
  _torque_type torque;
  using _kp_type =
    float;
  _kp_type kp;
  using _kd_type =
    float;
  _kd_type kd;
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
  Type & set__position(
    const float & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__velocity(
    const float & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__torque(
    const float & _arg)
  {
    this->torque = _arg;
    return *this;
  }
  Type & set__kp(
    const float & _arg)
  {
    this->kp = _arg;
    return *this;
  }
  Type & set__kd(
    const float & _arg)
  {
    this->kd = _arg;
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
    robstride_core::msg::MitCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const robstride_core::msg::MitCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robstride_core::msg::MitCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robstride_core::msg::MitCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robstride_core::msg::MitCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robstride_core::msg::MitCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robstride_core::msg::MitCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robstride_core::msg::MitCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robstride_core::msg::MitCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robstride_core::msg::MitCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robstride_core__msg__MitCmd
    std::shared_ptr<robstride_core::msg::MitCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robstride_core__msg__MitCmd
    std::shared_ptr<robstride_core::msg::MitCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MitCmd_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->torque != other.torque) {
      return false;
    }
    if (this->kp != other.kp) {
      return false;
    }
    if (this->kd != other.kd) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MitCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MitCmd_

// alias to use template instance with default allocator
using MitCmd =
  robstride_core::msg::MitCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robstride_core

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__STRUCT_HPP_
