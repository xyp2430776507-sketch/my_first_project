// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lightning:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__SAVE_MAP__TRAITS_HPP_
#define LIGHTNING__SRV__DETAIL__SAVE_MAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lightning/srv/detail/save_map__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace lightning
{

namespace srv
{

inline void to_flow_style_yaml(
  const SaveMap_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: map_id
  {
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SaveMap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: map_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_id: ";
    rosidl_generator_traits::value_to_yaml(msg.map_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SaveMap_Request & msg, bool use_flow_style = false)
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
  const lightning::srv::SaveMap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  lightning::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lightning::srv::to_yaml() instead")]]
inline std::string to_yaml(const lightning::srv::SaveMap_Request & msg)
{
  return lightning::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lightning::srv::SaveMap_Request>()
{
  return "lightning::srv::SaveMap_Request";
}

template<>
inline const char * name<lightning::srv::SaveMap_Request>()
{
  return "lightning/srv/SaveMap_Request";
}

template<>
struct has_fixed_size<lightning::srv::SaveMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lightning::srv::SaveMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lightning::srv::SaveMap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace lightning
{

namespace srv
{

inline void to_flow_style_yaml(
  const SaveMap_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: response
  {
    out << "response: ";
    rosidl_generator_traits::value_to_yaml(msg.response, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SaveMap_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "response: ";
    rosidl_generator_traits::value_to_yaml(msg.response, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SaveMap_Response & msg, bool use_flow_style = false)
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
  const lightning::srv::SaveMap_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  lightning::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lightning::srv::to_yaml() instead")]]
inline std::string to_yaml(const lightning::srv::SaveMap_Response & msg)
{
  return lightning::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lightning::srv::SaveMap_Response>()
{
  return "lightning::srv::SaveMap_Response";
}

template<>
inline const char * name<lightning::srv::SaveMap_Response>()
{
  return "lightning/srv/SaveMap_Response";
}

template<>
struct has_fixed_size<lightning::srv::SaveMap_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lightning::srv::SaveMap_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lightning::srv::SaveMap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lightning::srv::SaveMap>()
{
  return "lightning::srv::SaveMap";
}

template<>
inline const char * name<lightning::srv::SaveMap>()
{
  return "lightning/srv/SaveMap";
}

template<>
struct has_fixed_size<lightning::srv::SaveMap>
  : std::integral_constant<
    bool,
    has_fixed_size<lightning::srv::SaveMap_Request>::value &&
    has_fixed_size<lightning::srv::SaveMap_Response>::value
  >
{
};

template<>
struct has_bounded_size<lightning::srv::SaveMap>
  : std::integral_constant<
    bool,
    has_bounded_size<lightning::srv::SaveMap_Request>::value &&
    has_bounded_size<lightning::srv::SaveMap_Response>::value
  >
{
};

template<>
struct is_service<lightning::srv::SaveMap>
  : std::true_type
{
};

template<>
struct is_service_request<lightning::srv::SaveMap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<lightning::srv::SaveMap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // LIGHTNING__SRV__DETAIL__SAVE_MAP__TRAITS_HPP_
