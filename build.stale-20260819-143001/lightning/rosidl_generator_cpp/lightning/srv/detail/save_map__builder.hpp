// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lightning:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
#define LIGHTNING__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lightning/srv/detail/save_map__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lightning
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Request_map_id
{
public:
  Init_SaveMap_Request_map_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lightning::srv::SaveMap_Request map_id(::lightning::srv::SaveMap_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lightning::srv::SaveMap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lightning::srv::SaveMap_Request>()
{
  return lightning::srv::builder::Init_SaveMap_Request_map_id();
}

}  // namespace lightning


namespace lightning
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Response_response
{
public:
  Init_SaveMap_Response_response()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lightning::srv::SaveMap_Response response(::lightning::srv::SaveMap_Response::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lightning::srv::SaveMap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lightning::srv::SaveMap_Response>()
{
  return lightning::srv::builder::Init_SaveMap_Response_response();
}

}  // namespace lightning

#endif  // LIGHTNING__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
