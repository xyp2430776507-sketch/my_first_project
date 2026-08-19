// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice
#include "lightning/srv/detail/loc_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `map_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
lightning__srv__LocCmd_Request__init(lightning__srv__LocCmd_Request * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // x
  // y
  // z
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    lightning__srv__LocCmd_Request__fini(msg);
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    lightning__srv__LocCmd_Request__fini(msg);
    return false;
  }
  return true;
}

void
lightning__srv__LocCmd_Request__fini(lightning__srv__LocCmd_Request * msg)
{
  if (!msg) {
    return;
  }
  // id
  // x
  // y
  // z
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
  // header
  std_msgs__msg__Header__fini(&msg->header);
}

bool
lightning__srv__LocCmd_Request__are_equal(const lightning__srv__LocCmd_Request * lhs, const lightning__srv__LocCmd_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  return true;
}

bool
lightning__srv__LocCmd_Request__copy(
  const lightning__srv__LocCmd_Request * input,
  lightning__srv__LocCmd_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  return true;
}

lightning__srv__LocCmd_Request *
lightning__srv__LocCmd_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__LocCmd_Request * msg = (lightning__srv__LocCmd_Request *)allocator.allocate(sizeof(lightning__srv__LocCmd_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lightning__srv__LocCmd_Request));
  bool success = lightning__srv__LocCmd_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lightning__srv__LocCmd_Request__destroy(lightning__srv__LocCmd_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lightning__srv__LocCmd_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lightning__srv__LocCmd_Request__Sequence__init(lightning__srv__LocCmd_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__LocCmd_Request * data = NULL;

  if (size) {
    data = (lightning__srv__LocCmd_Request *)allocator.zero_allocate(size, sizeof(lightning__srv__LocCmd_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lightning__srv__LocCmd_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lightning__srv__LocCmd_Request__fini(&data[i - 1]);
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
lightning__srv__LocCmd_Request__Sequence__fini(lightning__srv__LocCmd_Request__Sequence * array)
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
      lightning__srv__LocCmd_Request__fini(&array->data[i]);
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

lightning__srv__LocCmd_Request__Sequence *
lightning__srv__LocCmd_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__LocCmd_Request__Sequence * array = (lightning__srv__LocCmd_Request__Sequence *)allocator.allocate(sizeof(lightning__srv__LocCmd_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lightning__srv__LocCmd_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lightning__srv__LocCmd_Request__Sequence__destroy(lightning__srv__LocCmd_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lightning__srv__LocCmd_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lightning__srv__LocCmd_Request__Sequence__are_equal(const lightning__srv__LocCmd_Request__Sequence * lhs, const lightning__srv__LocCmd_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lightning__srv__LocCmd_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lightning__srv__LocCmd_Request__Sequence__copy(
  const lightning__srv__LocCmd_Request__Sequence * input,
  lightning__srv__LocCmd_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lightning__srv__LocCmd_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lightning__srv__LocCmd_Request * data =
      (lightning__srv__LocCmd_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lightning__srv__LocCmd_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lightning__srv__LocCmd_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lightning__srv__LocCmd_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
lightning__srv__LocCmd_Response__init(lightning__srv__LocCmd_Response * msg)
{
  if (!msg) {
    return false;
  }
  // result
  return true;
}

void
lightning__srv__LocCmd_Response__fini(lightning__srv__LocCmd_Response * msg)
{
  if (!msg) {
    return;
  }
  // result
}

bool
lightning__srv__LocCmd_Response__are_equal(const lightning__srv__LocCmd_Response * lhs, const lightning__srv__LocCmd_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result
  if (lhs->result != rhs->result) {
    return false;
  }
  return true;
}

bool
lightning__srv__LocCmd_Response__copy(
  const lightning__srv__LocCmd_Response * input,
  lightning__srv__LocCmd_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // result
  output->result = input->result;
  return true;
}

lightning__srv__LocCmd_Response *
lightning__srv__LocCmd_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__LocCmd_Response * msg = (lightning__srv__LocCmd_Response *)allocator.allocate(sizeof(lightning__srv__LocCmd_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lightning__srv__LocCmd_Response));
  bool success = lightning__srv__LocCmd_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lightning__srv__LocCmd_Response__destroy(lightning__srv__LocCmd_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lightning__srv__LocCmd_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lightning__srv__LocCmd_Response__Sequence__init(lightning__srv__LocCmd_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__LocCmd_Response * data = NULL;

  if (size) {
    data = (lightning__srv__LocCmd_Response *)allocator.zero_allocate(size, sizeof(lightning__srv__LocCmd_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lightning__srv__LocCmd_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lightning__srv__LocCmd_Response__fini(&data[i - 1]);
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
lightning__srv__LocCmd_Response__Sequence__fini(lightning__srv__LocCmd_Response__Sequence * array)
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
      lightning__srv__LocCmd_Response__fini(&array->data[i]);
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

lightning__srv__LocCmd_Response__Sequence *
lightning__srv__LocCmd_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__LocCmd_Response__Sequence * array = (lightning__srv__LocCmd_Response__Sequence *)allocator.allocate(sizeof(lightning__srv__LocCmd_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lightning__srv__LocCmd_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lightning__srv__LocCmd_Response__Sequence__destroy(lightning__srv__LocCmd_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lightning__srv__LocCmd_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lightning__srv__LocCmd_Response__Sequence__are_equal(const lightning__srv__LocCmd_Response__Sequence * lhs, const lightning__srv__LocCmd_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lightning__srv__LocCmd_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lightning__srv__LocCmd_Response__Sequence__copy(
  const lightning__srv__LocCmd_Response__Sequence * input,
  lightning__srv__LocCmd_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lightning__srv__LocCmd_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lightning__srv__LocCmd_Response * data =
      (lightning__srv__LocCmd_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lightning__srv__LocCmd_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lightning__srv__LocCmd_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lightning__srv__LocCmd_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
