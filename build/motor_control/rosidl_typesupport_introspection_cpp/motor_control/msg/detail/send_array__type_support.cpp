// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "motor_control/msg/detail/send_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace motor_control
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SendArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) motor_control::msg::SendArray(_init);
}

void SendArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<motor_control::msg::SendArray *>(message_memory);
  typed_message->~SendArray();
}

size_t size_function__SendArray__cmds(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<motor_control::msg::SendAt> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SendArray__cmds(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<motor_control::msg::SendAt> *>(untyped_member);
  return &member[index];
}

void * get_function__SendArray__cmds(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<motor_control::msg::SendAt> *>(untyped_member);
  return &member[index];
}

void fetch_function__SendArray__cmds(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const motor_control::msg::SendAt *>(
    get_const_function__SendArray__cmds(untyped_member, index));
  auto & value = *reinterpret_cast<motor_control::msg::SendAt *>(untyped_value);
  value = item;
}

void assign_function__SendArray__cmds(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<motor_control::msg::SendAt *>(
    get_function__SendArray__cmds(untyped_member, index));
  const auto & value = *reinterpret_cast<const motor_control::msg::SendAt *>(untyped_value);
  item = value;
}

void resize_function__SendArray__cmds(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<motor_control::msg::SendAt> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SendArray_message_member_array[1] = {
  {
    "cmds",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<motor_control::msg::SendAt>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control::msg::SendArray, cmds),  // bytes offset in struct
    nullptr,  // default value
    size_function__SendArray__cmds,  // size() function pointer
    get_const_function__SendArray__cmds,  // get_const(index) function pointer
    get_function__SendArray__cmds,  // get(index) function pointer
    fetch_function__SendArray__cmds,  // fetch(index, &value) function pointer
    assign_function__SendArray__cmds,  // assign(index, value) function pointer
    resize_function__SendArray__cmds  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SendArray_message_members = {
  "motor_control::msg",  // message namespace
  "SendArray",  // message name
  1,  // number of fields
  sizeof(motor_control::msg::SendArray),
  SendArray_message_member_array,  // message members
  SendArray_init_function,  // function to initialize message memory (memory has to be allocated)
  SendArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SendArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SendArray_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace motor_control


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<motor_control::msg::SendArray>()
{
  return &::motor_control::msg::rosidl_typesupport_introspection_cpp::SendArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motor_control, msg, SendArray)() {
  return &::motor_control::msg::rosidl_typesupport_introspection_cpp::SendArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
