// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "motor_control/msg/detail/gpio_cmd__struct.hpp"
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

void GpioCmd_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) motor_control::msg::GpioCmd(_init);
}

void GpioCmd_fini_function(void * message_memory)
{
  auto typed_message = static_cast<motor_control::msg::GpioCmd *>(message_memory);
  typed_message->~GpioCmd();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GpioCmd_message_member_array[2] = {
  {
    "pin_index",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control::msg::GpioCmd, pin_index),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "toggle",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control::msg::GpioCmd, toggle),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GpioCmd_message_members = {
  "motor_control::msg",  // message namespace
  "GpioCmd",  // message name
  2,  // number of fields
  sizeof(motor_control::msg::GpioCmd),
  GpioCmd_message_member_array,  // message members
  GpioCmd_init_function,  // function to initialize message memory (memory has to be allocated)
  GpioCmd_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GpioCmd_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GpioCmd_message_members,
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
get_message_type_support_handle<motor_control::msg::GpioCmd>()
{
  return &::motor_control::msg::rosidl_typesupport_introspection_cpp::GpioCmd_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, motor_control, msg, GpioCmd)() {
  return &::motor_control::msg::rosidl_typesupport_introspection_cpp::GpioCmd_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
