// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__LOC_CMD__STRUCT_H_
#define LIGHTNING__SRV__DETAIL__LOC_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'CMD_LOC_SET_MAP'.
/**
  * 设置地图
 */
enum
{
  lightning__srv__LocCmd_Request__CMD_LOC_SET_MAP = 1
};

/// Constant 'CMD_LOC_INIT_POSE'.
/**
  * 设置重定位姿，参数由x y yaw 给出
 */
enum
{
  lightning__srv__LocCmd_Request__CMD_LOC_INIT_POSE = 3
};

/// Constant 'CMD_LOC_INIT_LIST'.
/**
  * 设置重定位点列表，由建图工具设置并保存成队列
 */
enum
{
  lightning__srv__LocCmd_Request__CMD_LOC_INIT_LIST = 4
};

// Include directives for member types
// Member 'map_id'
#include "rosidl_runtime_c/string.h"
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in srv/LocCmd in the package lightning.
typedef struct lightning__srv__LocCmd_Request
{
  /// 命令id
  uint8_t id;
  /// 重定位点坐标x
  double x;
  /// 重定位点坐标x
  double y;
  /// 重定位点坐标x
  double z;
  /// 地图路径
  rosidl_runtime_c__String map_id;
  /// 时间戳
  std_msgs__msg__Header header;
} lightning__srv__LocCmd_Request;

// Struct for a sequence of lightning__srv__LocCmd_Request.
typedef struct lightning__srv__LocCmd_Request__Sequence
{
  lightning__srv__LocCmd_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lightning__srv__LocCmd_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/LocCmd in the package lightning.
typedef struct lightning__srv__LocCmd_Response
{
  /// 为0表示成功
  uint32_t result;
} lightning__srv__LocCmd_Response;

// Struct for a sequence of lightning__srv__LocCmd_Response.
typedef struct lightning__srv__LocCmd_Response__Sequence
{
  lightning__srv__LocCmd_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} lightning__srv__LocCmd_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LIGHTNING__SRV__DETAIL__LOC_CMD__STRUCT_H_
