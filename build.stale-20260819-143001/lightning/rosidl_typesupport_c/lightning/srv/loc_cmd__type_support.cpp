// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "lightning/srv/detail/loc_cmd__struct.h"
#include "lightning/srv/detail/loc_cmd__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace lightning
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _LocCmd_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocCmd_Request_type_support_ids_t;

static const _LocCmd_Request_type_support_ids_t _LocCmd_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocCmd_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocCmd_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocCmd_Request_type_support_symbol_names_t _LocCmd_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, lightning, srv, LocCmd_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Request)),
  }
};

typedef struct _LocCmd_Request_type_support_data_t
{
  void * data[2];
} _LocCmd_Request_type_support_data_t;

static _LocCmd_Request_type_support_data_t _LocCmd_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocCmd_Request_message_typesupport_map = {
  2,
  "lightning",
  &_LocCmd_Request_message_typesupport_ids.typesupport_identifier[0],
  &_LocCmd_Request_message_typesupport_symbol_names.symbol_name[0],
  &_LocCmd_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t LocCmd_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocCmd_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace lightning

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, lightning, srv, LocCmd_Request)() {
  return &::lightning::srv::rosidl_typesupport_c::LocCmd_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "lightning/srv/detail/loc_cmd__struct.h"
// already included above
// #include "lightning/srv/detail/loc_cmd__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace lightning
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _LocCmd_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocCmd_Response_type_support_ids_t;

static const _LocCmd_Response_type_support_ids_t _LocCmd_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocCmd_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocCmd_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocCmd_Response_type_support_symbol_names_t _LocCmd_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, lightning, srv, LocCmd_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd_Response)),
  }
};

typedef struct _LocCmd_Response_type_support_data_t
{
  void * data[2];
} _LocCmd_Response_type_support_data_t;

static _LocCmd_Response_type_support_data_t _LocCmd_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocCmd_Response_message_typesupport_map = {
  2,
  "lightning",
  &_LocCmd_Response_message_typesupport_ids.typesupport_identifier[0],
  &_LocCmd_Response_message_typesupport_symbol_names.symbol_name[0],
  &_LocCmd_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t LocCmd_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocCmd_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace lightning

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, lightning, srv, LocCmd_Response)() {
  return &::lightning::srv::rosidl_typesupport_c::LocCmd_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "lightning/srv/detail/loc_cmd__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace lightning
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _LocCmd_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocCmd_type_support_ids_t;

static const _LocCmd_type_support_ids_t _LocCmd_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocCmd_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocCmd_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocCmd_type_support_symbol_names_t _LocCmd_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, lightning, srv, LocCmd)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lightning, srv, LocCmd)),
  }
};

typedef struct _LocCmd_type_support_data_t
{
  void * data[2];
} _LocCmd_type_support_data_t;

static _LocCmd_type_support_data_t _LocCmd_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocCmd_service_typesupport_map = {
  2,
  "lightning",
  &_LocCmd_service_typesupport_ids.typesupport_identifier[0],
  &_LocCmd_service_typesupport_symbol_names.symbol_name[0],
  &_LocCmd_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t LocCmd_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocCmd_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace lightning

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, lightning, srv, LocCmd)() {
  return &::lightning::srv::rosidl_typesupport_c::LocCmd_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
