// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice
#include "motor_control/msg/detail/gpio_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
motor_control__msg__GpioCmd__init(motor_control__msg__GpioCmd * msg)
{
  if (!msg) {
    return false;
  }
  // pin_index
  // toggle
  return true;
}

void
motor_control__msg__GpioCmd__fini(motor_control__msg__GpioCmd * msg)
{
  if (!msg) {
    return;
  }
  // pin_index
  // toggle
}

bool
motor_control__msg__GpioCmd__are_equal(const motor_control__msg__GpioCmd * lhs, const motor_control__msg__GpioCmd * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pin_index
  if (lhs->pin_index != rhs->pin_index) {
    return false;
  }
  // toggle
  if (lhs->toggle != rhs->toggle) {
    return false;
  }
  return true;
}

bool
motor_control__msg__GpioCmd__copy(
  const motor_control__msg__GpioCmd * input,
  motor_control__msg__GpioCmd * output)
{
  if (!input || !output) {
    return false;
  }
  // pin_index
  output->pin_index = input->pin_index;
  // toggle
  output->toggle = input->toggle;
  return true;
}

motor_control__msg__GpioCmd *
motor_control__msg__GpioCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__GpioCmd * msg = (motor_control__msg__GpioCmd *)allocator.allocate(sizeof(motor_control__msg__GpioCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_control__msg__GpioCmd));
  bool success = motor_control__msg__GpioCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_control__msg__GpioCmd__destroy(motor_control__msg__GpioCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_control__msg__GpioCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_control__msg__GpioCmd__Sequence__init(motor_control__msg__GpioCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__GpioCmd * data = NULL;

  if (size) {
    data = (motor_control__msg__GpioCmd *)allocator.zero_allocate(size, sizeof(motor_control__msg__GpioCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_control__msg__GpioCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_control__msg__GpioCmd__fini(&data[i - 1]);
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
motor_control__msg__GpioCmd__Sequence__fini(motor_control__msg__GpioCmd__Sequence * array)
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
      motor_control__msg__GpioCmd__fini(&array->data[i]);
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

motor_control__msg__GpioCmd__Sequence *
motor_control__msg__GpioCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_control__msg__GpioCmd__Sequence * array = (motor_control__msg__GpioCmd__Sequence *)allocator.allocate(sizeof(motor_control__msg__GpioCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_control__msg__GpioCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_control__msg__GpioCmd__Sequence__destroy(motor_control__msg__GpioCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_control__msg__GpioCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_control__msg__GpioCmd__Sequence__are_equal(const motor_control__msg__GpioCmd__Sequence * lhs, const motor_control__msg__GpioCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_control__msg__GpioCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_control__msg__GpioCmd__Sequence__copy(
  const motor_control__msg__GpioCmd__Sequence * input,
  motor_control__msg__GpioCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_control__msg__GpioCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motor_control__msg__GpioCmd * data =
      (motor_control__msg__GpioCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_control__msg__GpioCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motor_control__msg__GpioCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_control__msg__GpioCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
