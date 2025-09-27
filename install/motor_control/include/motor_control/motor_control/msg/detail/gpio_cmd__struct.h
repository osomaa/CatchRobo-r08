// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__STRUCT_H_
#define MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/GpioCmd in the package motor_control.
typedef struct motor_control__msg__GpioCmd
{
  int32_t pin_index;
  bool toggle;
} motor_control__msg__GpioCmd;

// Struct for a sequence of motor_control__msg__GpioCmd.
typedef struct motor_control__msg__GpioCmd__Sequence
{
  motor_control__msg__GpioCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_control__msg__GpioCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_CONTROL__MSG__DETAIL__GPIO_CMD__STRUCT_H_
