// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from motor_control:msg/SendAt.idl
// generated code does not contain a copyright notice

#ifndef MOTOR_CONTROL__MSG__DETAIL__SEND_AT__FUNCTIONS_H_
#define MOTOR_CONTROL__MSG__DETAIL__SEND_AT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "motor_control/msg/rosidl_generator_c__visibility_control.h"

#include "motor_control/msg/detail/send_at__struct.h"

/// Initialize msg/SendAt message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * motor_control__msg__SendAt
 * )) before or use
 * motor_control__msg__SendAt__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
bool
motor_control__msg__SendAt__init(motor_control__msg__SendAt * msg);

/// Finalize msg/SendAt message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
void
motor_control__msg__SendAt__fini(motor_control__msg__SendAt * msg);

/// Create msg/SendAt message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * motor_control__msg__SendAt__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
motor_control__msg__SendAt *
motor_control__msg__SendAt__create();

/// Destroy msg/SendAt message.
/**
 * It calls
 * motor_control__msg__SendAt__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
void
motor_control__msg__SendAt__destroy(motor_control__msg__SendAt * msg);

/// Check for msg/SendAt message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
bool
motor_control__msg__SendAt__are_equal(const motor_control__msg__SendAt * lhs, const motor_control__msg__SendAt * rhs);

/// Copy a msg/SendAt message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
bool
motor_control__msg__SendAt__copy(
  const motor_control__msg__SendAt * input,
  motor_control__msg__SendAt * output);

/// Initialize array of msg/SendAt messages.
/**
 * It allocates the memory for the number of elements and calls
 * motor_control__msg__SendAt__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
bool
motor_control__msg__SendAt__Sequence__init(motor_control__msg__SendAt__Sequence * array, size_t size);

/// Finalize array of msg/SendAt messages.
/**
 * It calls
 * motor_control__msg__SendAt__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
void
motor_control__msg__SendAt__Sequence__fini(motor_control__msg__SendAt__Sequence * array);

/// Create array of msg/SendAt messages.
/**
 * It allocates the memory for the array and calls
 * motor_control__msg__SendAt__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
motor_control__msg__SendAt__Sequence *
motor_control__msg__SendAt__Sequence__create(size_t size);

/// Destroy array of msg/SendAt messages.
/**
 * It calls
 * motor_control__msg__SendAt__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
void
motor_control__msg__SendAt__Sequence__destroy(motor_control__msg__SendAt__Sequence * array);

/// Check for msg/SendAt message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
bool
motor_control__msg__SendAt__Sequence__are_equal(const motor_control__msg__SendAt__Sequence * lhs, const motor_control__msg__SendAt__Sequence * rhs);

/// Copy an array of msg/SendAt messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_motor_control
bool
motor_control__msg__SendAt__Sequence__copy(
  const motor_control__msg__SendAt__Sequence * input,
  motor_control__msg__SendAt__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_CONTROL__MSG__DETAIL__SEND_AT__FUNCTIONS_H_
