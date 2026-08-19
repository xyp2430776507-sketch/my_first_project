// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lightning:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__SAVE_MAP__STRUCT_H_
#define LIGHTNING__SRV__DETAIL__SAVE_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'map_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SaveMap in the package lightning.
typedef struct lightning__srv__SaveMap_Request
{
  /// 地图名称（唯一标识）
  rosidl_runtime_c__String map_id;
} lightning__srv__SaveMap_Request;

// Struct for a sequence of lightning__srv__SaveMap_Request.
typedef struct lightning__srv__SaveMap_Request__Sequence
{
  lightning__srv__SaveMap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lightning__srv__SaveMap_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SaveMap in the package lightning.
typedef struct lightning__srv__SaveMap_Response
{
  /// 为0时成功， 1保存地图已经在运行 2图像渲染重置失败 3地图数据为空，无法保存，4扩图定位失败
  uint32_t response;
} lightning__srv__SaveMap_Response;

// Struct for a sequence of lightning__srv__SaveMap_Response.
typedef struct lightning__srv__SaveMap_Response__Sequence
{
  lightning__srv__SaveMap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lightning__srv__SaveMap_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIGHTNING__SRV__DETAIL__SAVE_MAP__STRUCT_H_
