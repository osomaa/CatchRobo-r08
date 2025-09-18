// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__STRUCT_H_
#define MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'cmds'
#include "motor_control/msg/detail/send_at__struct.h"

/// Struct defined in msg/SendArray in the package motor_control.
typedef struct motor_control__msg__SendArray
{
  motor_control__msg__SendAt__Sequence cmds;
} motor_control__msg__SendArray;

// Struct for a sequence of motor_control__msg__SendArray.
typedef struct motor_control__msg__SendArray__Sequence
{
  motor_control__msg__SendArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_control__msg__SendArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_CONTROL__MSG__DETAIL__SEND_ARRAY__STRUCT_H_
