// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robstride_core:msg/GoalEvent.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robstride_core/msg/detail/goal_event__rosidl_typesupport_introspection_c.h"
#include "robstride_core/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robstride_core/msg/detail/goal_event__functions.h"
#include "robstride_core/msg/detail/goal_event__struct.h"


// Include directives for member types
// Member `state`
#include "rosidl_runtime_c/string_functions.h"
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robstride_core__msg__GoalEvent__init(message_memory);
}

void robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_fini_function(void * message_memory)
{
  robstride_core__msg__GoalEvent__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_member_array[4] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robstride_core__msg__GoalEvent, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robstride_core__msg__GoalEvent, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robstride_core__msg__GoalEvent, error),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robstride_core__msg__GoalEvent, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_members = {
  "robstride_core__msg",  // message namespace
  "GoalEvent",  // message name
  4,  // number of fields
  sizeof(robstride_core__msg__GoalEvent),
  robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_member_array,  // message members
  robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_init_function,  // function to initialize message memory (memory has to be allocated)
  robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_type_support_handle = {
  0,
  &robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robstride_core
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robstride_core, msg, GoalEvent)() {
  robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_type_support_handle.typesupport_identifier) {
    robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robstride_core__msg__GoalEvent__rosidl_typesupport_introspection_c__GoalEvent_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
