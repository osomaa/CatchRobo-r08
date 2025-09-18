// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_control:msg/ReturnAt.idl
// generated code does not contain a copyright notice
#include "motor_control/msg/detail/return_at__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motor_control__msg__ReturnAt__init(motor_control__msg__ReturnAt * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // position
  return true;
}

void
motor_control__msg__ReturnAt__fini(motor_control__msg__ReturnAt * msg)
{
  if (!msg) {
    return;
  }
  // id
  // position
}

bool
motor_control__msg__ReturnAt__are_equal(const motor_control__msg__ReturnAt * lhs, const motor_control__msg__ReturnAt * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  return true;
}

bool
motor_control__msg__ReturnAt__copy(
  const motor_control__msg__ReturnAt * input,
  motor_control__msg__ReturnAt * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // position
  output->position = input->position;
  return true;
}

motor_control__msg__ReturnAt *
motor_control__msg__ReturnAt__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__ReturnAt * msg = (motor_control__msg__ReturnAt *)allocator.allocate(sizeof(motor_control__msg__ReturnAt), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_control__msg__ReturnAt));
  bool success = motor_control__msg__ReturnAt__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_control__msg__ReturnAt__destroy(motor_control__msg__ReturnAt * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_control__msg__ReturnAt__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_control__msg__ReturnAt__Sequence__init(motor_control__msg__ReturnAt__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__ReturnAt * data = NULL;

  if (size) {
    data = (motor_control__msg__ReturnAt *)allocator.zero_allocate(size, sizeof(motor_control__msg__ReturnAt), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_control__msg__ReturnAt__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_control__msg__ReturnAt__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
motor_control__msg__ReturnAt__Sequence__fini(motor_control__msg__ReturnAt__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      motor_control__msg__ReturnAt__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

motor_control__msg__ReturnAt__Sequence *
motor_control__msg__ReturnAt__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__ReturnAt__Sequence * array = (motor_control__msg__ReturnAt__Sequence *)allocator.allocate(sizeof(motor_control__msg__ReturnAt__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_control__msg__ReturnAt__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_control__msg__ReturnAt__Sequence__destroy(motor_control__msg__ReturnAt__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_control__msg__ReturnAt__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_control__msg__ReturnAt__Sequence__are_equal(const motor_control__msg__ReturnAt__Sequence * lhs, const motor_control__msg__ReturnAt__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_control__msg__ReturnAt__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_control__msg__ReturnAt__Sequence__copy(
  const motor_control__msg__ReturnAt__Sequence * input,
  motor_control__msg__ReturnAt__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_control__msg__ReturnAt);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motor_control__msg__ReturnAt * data =
      (motor_control__msg__ReturnAt *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_control__msg__ReturnAt__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motor_control__msg__ReturnAt__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_control__msg__ReturnAt__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
