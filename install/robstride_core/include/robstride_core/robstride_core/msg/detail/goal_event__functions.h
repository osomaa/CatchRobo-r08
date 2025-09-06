// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from robstride_core:msg/GoalEvent.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__FUNCTIONS_H_
#define ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "robstride_core/msg/rosidl_generator_c__visibility_control.h"

#include "robstride_core/msg/detail/goal_event__struct.h"

/// Initialize msg/GoalEvent message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robstride_core__msg__GoalEvent
 * )) before or use
 * robstride_core__msg__GoalEvent__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__GoalEvent__init(robstride_core__msg__GoalEvent * msg);

/// Finalize msg/GoalEvent message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__GoalEvent__fini(robstride_core__msg__GoalEvent * msg);

/// Create msg/GoalEvent message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robstride_core__msg__GoalEvent__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
robstride_core__msg__GoalEvent *
robstride_core__msg__GoalEvent__create();

/// Destroy msg/GoalEvent message.
/**
 * It calls
 * robstride_core__msg__GoalEvent__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__GoalEvent__destroy(robstride_core__msg__GoalEvent * msg);

/// Check for msg/GoalEvent message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__GoalEvent__are_equal(const robstride_core__msg__GoalEvent * lhs, const robstride_core__msg__GoalEvent * rhs);

/// Copy a msg/GoalEvent message.
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
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__GoalEvent__copy(
  const robstride_core__msg__GoalEvent * input,
  robstride_core__msg__GoalEvent * output);

/// Initialize array of msg/GoalEvent messages.
/**
 * It allocates the memory for the number of elements and calls
 * robstride_core__msg__GoalEvent__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__GoalEvent__Sequence__init(robstride_core__msg__GoalEvent__Sequence * array, size_t size);

/// Finalize array of msg/GoalEvent messages.
/**
 * It calls
 * robstride_core__msg__GoalEvent__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__GoalEvent__Sequence__fini(robstride_core__msg__GoalEvent__Sequence * array);

/// Create array of msg/GoalEvent messages.
/**
 * It allocates the memory for the array and calls
 * robstride_core__msg__GoalEvent__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
robstride_core__msg__GoalEvent__Sequence *
robstride_core__msg__GoalEvent__Sequence__create(size_t size);

/// Destroy array of msg/GoalEvent messages.
/**
 * It calls
 * robstride_core__msg__GoalEvent__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__GoalEvent__Sequence__destroy(robstride_core__msg__GoalEvent__Sequence * array);

/// Check for msg/GoalEvent message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__GoalEvent__Sequence__are_equal(const robstride_core__msg__GoalEvent__Sequence * lhs, const robstride_core__msg__GoalEvent__Sequence * rhs);

/// Copy an array of msg/GoalEvent messages.
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
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__GoalEvent__Sequence__copy(
  const robstride_core__msg__GoalEvent__Sequence * input,
  robstride_core__msg__GoalEvent__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__GOAL_EVENT__FUNCTIONS_H_
