// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motor_control:msg/ReturnAt.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motor_control/msg/detail/return_at__rosidl_typesupport_introspection_c.h"
#include "motor_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motor_control/msg/detail/return_at__functions.h"
#include "motor_control/msg/detail/return_at__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motor_control__msg__ReturnAt__init(message_memory);
}

void motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_fini_function(void * message_memory)
{
  motor_control__msg__ReturnAt__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_member_array[2] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control__msg__ReturnAt, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control__msg__ReturnAt, position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_members = {
  "motor_control__msg",  // message namespace
  "ReturnAt",  // message name
  2,  // number of fields
  sizeof(motor_control__msg__ReturnAt),
  motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_member_array,  // message members
  motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_init_function,  // function to initialize message memory (memory has to be allocated)
  motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_type_support_handle = {
  0,
  &motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motor_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motor_control, msg, ReturnAt)() {
  if (!motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_type_support_handle.typesupport_identifier) {
    motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motor_control__msg__ReturnAt__rosidl_typesupport_introspection_c__ReturnAt_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
