// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from robstride_core:msg/MitCmd.idl
// generated code does not contain a copyright notice

#ifndef ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__FUNCTIONS_H_
#define ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "robstride_core/msg/rosidl_generator_c__visibility_control.h"

#include "robstride_core/msg/detail/mit_cmd__struct.h"

/// Initialize msg/MitCmd message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robstride_core__msg__MitCmd
 * )) before or use
 * robstride_core__msg__MitCmd__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__MitCmd__init(robstride_core__msg__MitCmd * msg);

/// Finalize msg/MitCmd message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__MitCmd__fini(robstride_core__msg__MitCmd * msg);

/// Create msg/MitCmd message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robstride_core__msg__MitCmd__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
robstride_core__msg__MitCmd *
robstride_core__msg__MitCmd__create();

/// Destroy msg/MitCmd message.
/**
 * It calls
 * robstride_core__msg__MitCmd__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__MitCmd__destroy(robstride_core__msg__MitCmd * msg);

/// Check for msg/MitCmd message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__MitCmd__are_equal(const robstride_core__msg__MitCmd * lhs, const robstride_core__msg__MitCmd * rhs);

/// Copy a msg/MitCmd message.
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
robstride_core__msg__MitCmd__copy(
  const robstride_core__msg__MitCmd * input,
  robstride_core__msg__MitCmd * output);

/// Initialize array of msg/MitCmd messages.
/**
 * It allocates the memory for the number of elements and calls
 * robstride_core__msg__MitCmd__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__MitCmd__Sequence__init(robstride_core__msg__MitCmd__Sequence * array, size_t size);

/// Finalize array of msg/MitCmd messages.
/**
 * It calls
 * robstride_core__msg__MitCmd__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__MitCmd__Sequence__fini(robstride_core__msg__MitCmd__Sequence * array);

/// Create array of msg/MitCmd messages.
/**
 * It allocates the memory for the array and calls
 * robstride_core__msg__MitCmd__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
robstride_core__msg__MitCmd__Sequence *
robstride_core__msg__MitCmd__Sequence__create(size_t size);

/// Destroy array of msg/MitCmd messages.
/**
 * It calls
 * robstride_core__msg__MitCmd__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
void
robstride_core__msg__MitCmd__Sequence__destroy(robstride_core__msg__MitCmd__Sequence * array);

/// Check for msg/MitCmd message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robstride_core
bool
robstride_core__msg__MitCmd__Sequence__are_equal(const robstride_core__msg__MitCmd__Sequence * lhs, const robstride_core__msg__MitCmd__Sequence * rhs);

/// Copy an array of msg/MitCmd messages.
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
robstride_core__msg__MitCmd__Sequence__copy(
  const robstride_core__msg__MitCmd__Sequence * input,
  robstride_core__msg__MitCmd__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROBSTRIDE_CORE__MSG__DETAIL__MIT_CMD__FUNCTIONS_H_
