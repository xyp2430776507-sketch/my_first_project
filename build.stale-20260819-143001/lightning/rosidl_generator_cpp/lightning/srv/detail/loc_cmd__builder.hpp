// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__LOC_CMD__BUILDER_HPP_
#define LIGHTNING__SRV__DETAIL__LOC_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "lightning/srv/detail/loc_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace lightning
{

namespace srv
{

namespace builder
{

class Init_LocCmd_Request_header
{
public:
  explicit Init_LocCmd_Request_header(::lightning::srv::LocCmd_Request & msg)
  : msg_(msg)
  {}
  ::lightning::srv::LocCmd_Request header(::lightning::srv::LocCmd_Request::_header_type arg)
  {
    msg_.header = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lightning::srv::LocCmd_Request msg_;
};

class Init_LocCmd_Request_map_id
{
public:
  explicit Init_LocCmd_Request_map_id(::lightning::srv::LocCmd_Request & msg)
  : msg_(msg)
  {}
  Init_LocCmd_Request_header map_id(::lightning::srv::LocCmd_Request::_map_id_type arg)
  {
    msg_.map_id = std::move(arg);
    return Init_LocCmd_Request_header(msg_);
  }

private:
  ::lightning::srv::LocCmd_Request msg_;
};

class Init_LocCmd_Request_z
{
public:
  explicit Init_LocCmd_Request_z(::lightning::srv::LocCmd_Request & msg)
  : msg_(msg)
  {}
  Init_LocCmd_Request_map_id z(::lightning::srv::LocCmd_Request::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_LocCmd_Request_map_id(msg_);
  }

private:
  ::lightning::srv::LocCmd_Request msg_;
};

class Init_LocCmd_Request_y
{
public:
  explicit Init_LocCmd_Request_y(::lightning::srv::LocCmd_Request & msg)
  : msg_(msg)
  {}
  Init_LocCmd_Request_z y(::lightning::srv::LocCmd_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_LocCmd_Request_z(msg_);
  }

private:
  ::lightning::srv::LocCmd_Request msg_;
};

class Init_LocCmd_Request_x
{
public:
  explicit Init_LocCmd_Request_x(::lightning::srv::LocCmd_Request & msg)
  : msg_(msg)
  {}
  Init_LocCmd_Request_y x(::lightning::srv::LocCmd_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_LocCmd_Request_y(msg_);
  }

private:
  ::lightning::srv::LocCmd_Request msg_;
};

class Init_LocCmd_Request_id
{
public:
  Init_LocCmd_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocCmd_Request_x id(::lightning::srv::LocCmd_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_LocCmd_Request_x(msg_);
  }

private:
  ::lightning::srv::LocCmd_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lightning::srv::LocCmd_Request>()
{
  return lightning::srv::builder::Init_LocCmd_Request_id();
}

}  // namespace lightning


namespace lightning
{

namespace srv
{

namespace builder
{

class Init_LocCmd_Response_result
{
public:
  Init_LocCmd_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::lightning::srv::LocCmd_Response result(::lightning::srv::LocCmd_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::lightning::srv::LocCmd_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::lightning::srv::LocCmd_Response>()
{
  return lightning::srv::builder::Init_LocCmd_Response_result();
}

}  // namespace lightning

#endif  // LIGHTNING__SRV__DETAIL__LOC_CMD__BUILDER_HPP_
