// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robstride_core:msg/MitCmd.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__STRUCT_H_
#define ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/MitCmd in the package robstride_core.
typedef struct robstride_core__msg__MitCmd
{
  uint8_t id;
  float position;
  float velocity;
  float torque;
  float kp;
  float kd;
  builtin_interfaces__msg__Time stamp;
} robstride_core__msg__MitCmd;

// Struct for a sequence of robstride_core__msg__MitCmd.
typedef struct robstride_core__msg__MitCmd__Sequence
{
  robstride_core__msg__MitCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robstride_core__msg__MitCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__STRUCT_H_
