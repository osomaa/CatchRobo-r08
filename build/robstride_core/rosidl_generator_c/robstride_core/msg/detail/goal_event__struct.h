// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robstride_core:msg/GoalEvent.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__STRUCT_H_
#define ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'state'
#include "rosidl_runtime_c/string.h"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/GoalEvent in the package robstride_core.
typedef struct robstride_core__msg__GoalEvent
{
  uint8_t id;
  /// "goal" | "wait" | "timeout"
  rosidl_runtime_c__String state;
  /// |pos - target|
  float error;
  builtin_interfaces__msg__Time stamp;
} robstride_core__msg__GoalEvent;

// Struct for a sequence of robstride_core__msg__GoalEvent.
typedef struct robstride_core__msg__GoalEvent__Sequence
{
  robstride_core__msg__GoalEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robstride_core__msg__GoalEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__STRUCT_H_
