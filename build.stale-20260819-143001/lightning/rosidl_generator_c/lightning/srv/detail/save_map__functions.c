// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lightning:srv/SaveMap.idl
// generated code does not contain a copyright notice
#include "lightning/srv/detail/save_map__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `map_id`
#include "rosidl_runtime_c/string_functions.h"

bool
lightning__srv__SaveMap_Request__init(lightning__srv__SaveMap_Request * msg)
{
  if (!msg) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__init(&msg->map_id)) {
    lightning__srv__SaveMap_Request__fini(msg);
    return false;
  }
  return true;
}

void
lightning__srv__SaveMap_Request__fini(lightning__srv__SaveMap_Request * msg)
{
  if (!msg) {
    return;
  }
  // map_id
  rosidl_runtime_c__String__fini(&msg->map_id);
}

bool
lightning__srv__SaveMap_Request__are_equal(const lightning__srv__SaveMap_Request * lhs, const lightning__srv__SaveMap_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_id), &(rhs->map_id)))
  {
    return false;
  }
  return true;
}

bool
lightning__srv__SaveMap_Request__copy(
  const lightning__srv__SaveMap_Request * input,
  lightning__srv__SaveMap_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // map_id
  if (!rosidl_runtime_c__String__copy(
      &(input->map_id), &(output->map_id)))
  {
    return false;
  }
  return true;
}

lightning__srv__SaveMap_Request *
lightning__srv__SaveMap_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__SaveMap_Request * msg = (lightning__srv__SaveMap_Request *)allocator.allocate(sizeof(lightning__srv__SaveMap_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lightning__srv__SaveMap_Request));
  bool success = lightning__srv__SaveMap_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lightning__srv__SaveMap_Request__destroy(lightning__srv__SaveMap_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lightning__srv__SaveMap_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lightning__srv__SaveMap_Request__Sequence__init(lightning__srv__SaveMap_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__SaveMap_Request * data = NULL;

  if (size) {
    data = (lightning__srv__SaveMap_Request *)allocator.zero_allocate(size, sizeof(lightning__srv__SaveMap_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lightning__srv__SaveMap_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lightning__srv__SaveMap_Request__fini(&data[i - 1]);
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
lightning__srv__SaveMap_Request__Sequence__fini(lightning__srv__SaveMap_Request__Sequence * array)
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
      lightning__srv__SaveMap_Request__fini(&array->data[i]);
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

lightning__srv__SaveMap_Request__Sequence *
lightning__srv__SaveMap_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__SaveMap_Request__Sequence * array = (lightning__srv__SaveMap_Request__Sequence *)allocator.allocate(sizeof(lightning__srv__SaveMap_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lightning__srv__SaveMap_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lightning__srv__SaveMap_Request__Sequence__destroy(lightning__srv__SaveMap_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lightning__srv__SaveMap_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lightning__srv__SaveMap_Request__Sequence__are_equal(const lightning__srv__SaveMap_Request__Sequence * lhs, const lightning__srv__SaveMap_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lightning__srv__SaveMap_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lightning__srv__SaveMap_Request__Sequence__copy(
  const lightning__srv__SaveMap_Request__Sequence * input,
  lightning__srv__SaveMap_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lightning__srv__SaveMap_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lightning__srv__SaveMap_Request * data =
      (lightning__srv__SaveMap_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lightning__srv__SaveMap_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lightning__srv__SaveMap_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lightning__srv__SaveMap_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
lightning__srv__SaveMap_Response__init(lightning__srv__SaveMap_Response * msg)
{
  if (!msg) {
    return false;
  }
  // response
  return true;
}

void
lightning__srv__SaveMap_Response__fini(lightning__srv__SaveMap_Response * msg)
{
  if (!msg) {
    return;
  }
  // response
}

bool
lightning__srv__SaveMap_Response__are_equal(const lightning__srv__SaveMap_Response * lhs, const lightning__srv__SaveMap_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // response
  if (lhs->response != rhs->response) {
    return false;
  }
  return true;
}

bool
lightning__srv__SaveMap_Response__copy(
  const lightning__srv__SaveMap_Response * input,
  lightning__srv__SaveMap_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // response
  output->response = input->response;
  return true;
}

lightning__srv__SaveMap_Response *
lightning__srv__SaveMap_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__SaveMap_Response * msg = (lightning__srv__SaveMap_Response *)allocator.allocate(sizeof(lightning__srv__SaveMap_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lightning__srv__SaveMap_Response));
  bool success = lightning__srv__SaveMap_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lightning__srv__SaveMap_Response__destroy(lightning__srv__SaveMap_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lightning__srv__SaveMap_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lightning__srv__SaveMap_Response__Sequence__init(lightning__srv__SaveMap_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__SaveMap_Response * data = NULL;

  if (size) {
    data = (lightning__srv__SaveMap_Response *)allocator.zero_allocate(size, sizeof(lightning__srv__SaveMap_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lightning__srv__SaveMap_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lightning__srv__SaveMap_Response__fini(&data[i - 1]);
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
lightning__srv__SaveMap_Response__Sequence__fini(lightning__srv__SaveMap_Response__Sequence * array)
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
      lightning__srv__SaveMap_Response__fini(&array->data[i]);
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

lightning__srv__SaveMap_Response__Sequence *
lightning__srv__SaveMap_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lightning__srv__SaveMap_Response__Sequence * array = (lightning__srv__SaveMap_Response__Sequence *)allocator.allocate(sizeof(lightning__srv__SaveMap_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lightning__srv__SaveMap_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lightning__srv__SaveMap_Response__Sequence__destroy(lightning__srv__SaveMap_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lightning__srv__SaveMap_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lightning__srv__SaveMap_Response__Sequence__are_equal(const lightning__srv__SaveMap_Response__Sequence * lhs, const lightning__srv__SaveMap_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lightning__srv__SaveMap_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lightning__srv__SaveMap_Response__Sequence__copy(
  const lightning__srv__SaveMap_Response__Sequence * input,
  lightning__srv__SaveMap_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lightning__srv__SaveMap_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lightning__srv__SaveMap_Response * data =
      (lightning__srv__SaveMap_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lightning__srv__SaveMap_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lightning__srv__SaveMap_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lightning__srv__SaveMap_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
