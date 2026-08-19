// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__LOC_CMD__TRAITS_HPP_
#define LIGHTNING__SRV__DETAIL__LOC_CMD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lightning/srv/detail/loc_cmd__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace lightning
{

namespace srv
{

inline void to_flow_style_yaml(
  const LocCmd_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << ", ";
  }

  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocCmd_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: map_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << "\n";
  }

  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocCmd_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace lightning

namespace rosidl_generator_traits
{

[[deprecated("use lightning::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lightning::srv::LocCmd_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  lightning::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lightning::srv::to_yaml() instead")]]
inline std::string to_yaml(const lightning::srv::LocCmd_Request & msg)
{
  return lightning::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lightning::srv::LocCmd_Request>()
{
  return "lightning::srv::LocCmd_Request";
}

template<>
inline const char * name<lightning::srv::LocCmd_Request>()
{
  return "lightning/srv/LocCmd_Request";
}

template<>
struct has_fixed_size<lightning::srv::LocCmd_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lightning::srv::LocCmd_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lightning::srv::LocCmd_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace lightning
{

namespace srv
{

inline void to_flow_style_yaml(
  const LocCmd_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocCmd_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocCmd_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace lightning

namespace rosidl_generator_traits
{

[[deprecated("use lightning::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lightning::srv::LocCmd_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  lightning::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lightning::srv::to_yaml() instead")]]
inline std::string to_yaml(const lightning::srv::LocCmd_Response & msg)
{
  return lightning::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lightning::srv::LocCmd_Response>()
{
  return "lightning::srv::LocCmd_Response";
}

template<>
inline const char * name<lightning::srv::LocCmd_Response>()
{
  return "lightning/srv/LocCmd_Response";
}

template<>
struct has_fixed_size<lightning::srv::LocCmd_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lightning::srv::LocCmd_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lightning::srv::LocCmd_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lightning::srv::LocCmd>()
{
  return "lightning::srv::LocCmd";
}

template<>
inline const char * name<lightning::srv::LocCmd>()
{
  return "lightning/srv/LocCmd";
}

template<>
struct has_fixed_size<lightning::srv::LocCmd>
  : std::integral_constant<
    bool,
    has_fixed_size<lightning::srv::LocCmd_Request>::value &&
    has_fixed_size<lightning::srv::LocCmd_Response>::value
  >
{
};

template<>
struct has_bounded_size<lightning::srv::LocCmd>
  : std::integral_constant<
    bool,
    has_bounded_size<lightning::srv::LocCmd_Request>::value &&
    has_bounded_size<lightning::srv::LocCmd_Response>::value
  >
{
};

template<>
struct is_service<lightning::srv::LocCmd>
  : std::true_type
{
};

template<>
struct is_service_request<lightning::srv::LocCmd_Request>
  : std::true_type
{
};

template<>
struct is_service_response<lightning::srv::LocCmd_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // LIGHTNING__SRV__DETAIL__LOC_CMD__TRAITS_HPP_
