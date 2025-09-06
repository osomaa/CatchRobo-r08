// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robstride_core:msg/MitCmd.idl
// generated code does not contain a copyright notice
#include "robstride_core/msg/detail/mit_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
robstride_core__msg__MitCmd__init(robstride_core__msg__MitCmd * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // position
  // velocity
  // torque
  // kp
  // kd
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    robstride_core__msg__MitCmd__fini(msg);
    return false;
  }
  return true;
}

void
robstride_core__msg__MitCmd__fini(robstride_core__msg__MitCmd * msg)
{
  if (!msg) {
    return;
  }
  // id
  // position
  // velocity
  // torque
  // kp
  // kd
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
robstride_core__msg__MitCmd__are_equal(const robstride_core__msg__MitCmd * lhs, const robstride_core__msg__MitCmd * rhs)
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
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // torque
  if (lhs->torque != rhs->torque) {
    return false;
  }
  // kp
  if (lhs->kp != rhs->kp) {
    return false;
  }
  // kd
  if (lhs->kd != rhs->kd) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
robstride_core__msg__MitCmd__copy(
  const robstride_core__msg__MitCmd * input,
  robstride_core__msg__MitCmd * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // position
  output->position = input->position;
  // velocity
  output->velocity = input->velocity;
  // torque
  output->torque = input->torque;
  // kp
  output->kp = input->kp;
  // kd
  output->kd = input->kd;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

robstride_core__msg__MitCmd *
robstride_core__msg__MitCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robstride_core__msg__MitCmd * msg = (robstride_core__msg__MitCmd *)allocator.allocate(sizeof(robstride_core__msg__MitCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robstride_core__msg__MitCmd));
  bool success = robstride_core__msg__MitCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robstride_core__msg__MitCmd__destroy(robstride_core__msg__MitCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robstride_core__msg__MitCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robstride_core__msg__MitCmd__Sequence__init(robstride_core__msg__MitCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robstride_core__msg__MitCmd * data = NULL;

  if (size) {
    data = (robstride_core__msg__MitCmd *)allocator.zero_allocate(size, sizeof(robstride_core__msg__MitCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robstride_core__msg__MitCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robstride_core__msg__MitCmd__fini(&data[i - 1]);
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
robstride_core__msg__MitCmd__Sequence__fini(robstride_core__msg__MitCmd__Sequence * array)
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
      robstride_core__msg__MitCmd__fini(&array->data[i]);
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

robstride_core__msg__MitCmd__Sequence *
robstride_core__msg__MitCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robstride_core__msg__MitCmd__Sequence * array = (robstride_core__msg__MitCmd__Sequence *)allocator.allocate(sizeof(robstride_core__msg__MitCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robstride_core__msg__MitCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robstride_core__msg__MitCmd__Sequence__destroy(robstride_core__msg__MitCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robstride_core__msg__MitCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robstride_core__msg__MitCmd__Sequence__are_equal(const robstride_core__msg__MitCmd__Sequence * lhs, const robstride_core__msg__MitCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robstride_core__msg__MitCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robstride_core__msg__MitCmd__Sequence__copy(
  const robstride_core__msg__MitCmd__Sequence * input,
  robstride_core__msg__MitCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robstride_core__msg__MitCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robstride_core__msg__MitCmd * data =
      (robstride_core__msg__MitCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robstride_core__msg__MitCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robstride_core__msg__MitCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robstride_core__msg__MitCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
