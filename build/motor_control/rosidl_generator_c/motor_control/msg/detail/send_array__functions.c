// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_control:msg/SendArray.idl
// generated code does not contain a copyright notice
#include "motor_control/msg/detail/send_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `cmds`
#include "motor_control/msg/detail/send_at__functions.h"

bool
motor_control__msg__SendArray__init(motor_control__msg__SendArray * msg)
{
  if (!msg) {
    return false;
  }
  // cmds
  if (!motor_control__msg__SendAt__Sequence__init(&msg->cmds, 0)) {
    motor_control__msg__SendArray__fini(msg);
    return false;
  }
  return true;
}

void
motor_control__msg__SendArray__fini(motor_control__msg__SendArray * msg)
{
  if (!msg) {
    return;
  }
  // cmds
  motor_control__msg__SendAt__Sequence__fini(&msg->cmds);
}

bool
motor_control__msg__SendArray__are_equal(const motor_control__msg__SendArray * lhs, const motor_control__msg__SendArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // cmds
  if (!motor_control__msg__SendAt__Sequence__are_equal(
      &(lhs->cmds), &(rhs->cmds)))
  {
    return false;
  }
  return true;
}

bool
motor_control__msg__SendArray__copy(
  const motor_control__msg__SendArray * input,
  motor_control__msg__SendArray * output)
{
  if (!input || !output) {
    return false;
  }
  // cmds
  if (!motor_control__msg__SendAt__Sequence__copy(
      &(input->cmds), &(output->cmds)))
  {
    return false;
  }
  return true;
}

motor_control__msg__SendArray *
motor_control__msg__SendArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__SendArray * msg = (motor_control__msg__SendArray *)allocator.allocate(sizeof(motor_control__msg__SendArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_control__msg__SendArray));
  bool success = motor_control__msg__SendArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_control__msg__SendArray__destroy(motor_control__msg__SendArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_control__msg__SendArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_control__msg__SendArray__Sequence__init(motor_control__msg__SendArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__SendArray * data = NULL;

  if (size) {
    data = (motor_control__msg__SendArray *)allocator.zero_allocate(size, sizeof(motor_control__msg__SendArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_control__msg__SendArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_control__msg__SendArray__fini(&data[i - 1]);
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
motor_control__msg__SendArray__Sequence__fini(motor_control__msg__SendArray__Sequence * array)
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
      motor_control__msg__SendArray__fini(&array->data[i]);
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

motor_control__msg__SendArray__Sequence *
motor_control__msg__SendArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__SendArray__Sequence * array = (motor_control__msg__SendArray__Sequence *)allocator.allocate(sizeof(motor_control__msg__SendArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_control__msg__SendArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_control__msg__SendArray__Sequence__destroy(motor_control__msg__SendArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_control__msg__SendArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_control__msg__SendArray__Sequence__are_equal(const motor_control__msg__SendArray__Sequence * lhs, const motor_control__msg__SendArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_control__msg__SendArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_control__msg__SendArray__Sequence__copy(
  const motor_control__msg__SendArray__Sequence * input,
  motor_control__msg__SendArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_control__msg__SendArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motor_control__msg__SendArray * data =
      (motor_control__msg__SendArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_control__msg__SendArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motor_control__msg__SendArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_control__msg__SendArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
