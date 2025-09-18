// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motor_control/msg/detail/send_array__rosidl_typesupport_introspection_c.h"
#include "motor_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motor_control/msg/detail/send_array__functions.h"
#include "motor_control/msg/detail/send_array__struct.h"


// Include directives for member types
// Member `cmds`
#include "motor_control/msg/send_at.h"
// Member `cmds`
#include "motor_control/msg/detail/send_at__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motor_control__msg__SendArray__init(message_memory);
}

void motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_fini_function(void * message_memory)
{
  motor_control__msg__SendArray__fini(message_memory);
}

size_t motor_control__msg__SendArray__rosidl_typesupport_introspection_c__size_function__SendArray__cmds(
  const void * untyped_member)
{
  const motor_control__msg__SendAt__Sequence * member =
    (const motor_control__msg__SendAt__Sequence *)(untyped_member);
  return member->size;
}

const void * motor_control__msg__SendArray__rosidl_typesupport_introspection_c__get_const_function__SendArray__cmds(
  const void * untyped_member, size_t index)
{
  const motor_control__msg__SendAt__Sequence * member =
    (const motor_control__msg__SendAt__Sequence *)(untyped_member);
  return &member->data[index];
}

void * motor_control__msg__SendArray__rosidl_typesupport_introspection_c__get_function__SendArray__cmds(
  void * untyped_member, size_t index)
{
  motor_control__msg__SendAt__Sequence * member =
    (motor_control__msg__SendAt__Sequence *)(untyped_member);
  return &member->data[index];
}

void motor_control__msg__SendArray__rosidl_typesupport_introspection_c__fetch_function__SendArray__cmds(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const motor_control__msg__SendAt * item =
    ((const motor_control__msg__SendAt *)
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__get_const_function__SendArray__cmds(untyped_member, index));
  motor_control__msg__SendAt * value =
    (motor_control__msg__SendAt *)(untyped_value);
  *value = *item;
}

void motor_control__msg__SendArray__rosidl_typesupport_introspection_c__assign_function__SendArray__cmds(
  void * untyped_member, size_t index, const void * untyped_value)
{
  motor_control__msg__SendAt * item =
    ((motor_control__msg__SendAt *)
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__get_function__SendArray__cmds(untyped_member, index));
  const motor_control__msg__SendAt * value =
    (const motor_control__msg__SendAt *)(untyped_value);
  *item = *value;
}

bool motor_control__msg__SendArray__rosidl_typesupport_introspection_c__resize_function__SendArray__cmds(
  void * untyped_member, size_t size)
{
  motor_control__msg__SendAt__Sequence * member =
    (motor_control__msg__SendAt__Sequence *)(untyped_member);
  motor_control__msg__SendAt__Sequence__fini(member);
  return motor_control__msg__SendAt__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_member_array[1] = {
  {
    "cmds",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_control__msg__SendArray, cmds),  // bytes offset in struct
    NULL,  // default value
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__size_function__SendArray__cmds,  // size() function pointer
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__get_const_function__SendArray__cmds,  // get_const(index) function pointer
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__get_function__SendArray__cmds,  // get(index) function pointer
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__fetch_function__SendArray__cmds,  // fetch(index, &value) function pointer
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__assign_function__SendArray__cmds,  // assign(index, value) function pointer
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__resize_function__SendArray__cmds  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_members = {
  "motor_control__msg",  // message namespace
  "SendArray",  // message name
  1,  // number of fields
  sizeof(motor_control__msg__SendArray),
  motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_member_array,  // message members
  motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_init_function,  // function to initialize message memory (memory has to be allocated)
  motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_type_support_handle = {
  0,
  &motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motor_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motor_control, msg, SendArray)() {
  motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motor_control, msg, SendAt)();
  if (!motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_type_support_handle.typesupport_identifier) {
    motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motor_control__msg__SendArray__rosidl_typesupport_introspection_c__SendArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
