// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "lightning/srv/detail/loc_cmd__rosidl_typesupport_introspection_c.h"
#include "lightning/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "lightning/srv/detail/loc_cmd__functions.h"
#include "lightning/srv/detail/loc_cmd__struct.h"


// Include directives for member types
// Member `map_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lightning__srv__LocCmd_Request__init(message_memory);
}

void lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_fini_function(void * message_memory)
{
  lightning__srv__LocCmd_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_member_array[6] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Request, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Request, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Request, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Request, z),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Request, map_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Request, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_members = {
  "lightning__srv",  // message namespace
  "LocCmd_Request",  // message name
  6,  // number of fields
  sizeof(lightning__srv__LocCmd_Request),
  lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_member_array,  // message members
  lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_type_support_handle = {
  0,
  &lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lightning
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Request)() {
  lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_type_support_handle.typesupport_identifier) {
    lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lightning__srv__LocCmd_Request__rosidl_typesupport_introspection_c__LocCmd_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "lightning/srv/detail/loc_cmd__rosidl_typesupport_introspection_c.h"
// already included above
// #include "lightning/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "lightning/srv/detail/loc_cmd__functions.h"
// already included above
// #include "lightning/srv/detail/loc_cmd__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lightning__srv__LocCmd_Response__init(message_memory);
}

void lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_fini_function(void * message_memory)
{
  lightning__srv__LocCmd_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lightning__srv__LocCmd_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_members = {
  "lightning__srv",  // message namespace
  "LocCmd_Response",  // message name
  1,  // number of fields
  sizeof(lightning__srv__LocCmd_Response),
  lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_member_array,  // message members
  lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_type_support_handle = {
  0,
  &lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lightning
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Response)() {
  if (!lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_type_support_handle.typesupport_identifier) {
    lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lightning__srv__LocCmd_Response__rosidl_typesupport_introspection_c__LocCmd_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "lightning/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "lightning/srv/detail/loc_cmd__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_members = {
  "lightning__srv",  // service namespace
  "LocCmd",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_Request_message_type_support_handle,
  NULL  // response message
  // lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_Response_message_type_support_handle
};

static rosidl_service_type_support_t lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_type_support_handle = {
  0,
  &lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lightning
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd)() {
  if (!lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_type_support_handle.typesupport_identifier) {
    lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Response)()->data;
  }

  return &lightning__srv__detail__loc_cmd__rosidl_typesupport_introspection_c__LocCmd_service_type_support_handle;
}
