// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lightning:srv/LocCmd.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__LOC_CMD__STRUCT_HPP_
#define LIGHTNING__SRV__DETAIL__LOC_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__lightning__srv__LocCmd_Request __attribute__((deprecated))
#else
# define DEPRECATED__lightning__srv__LocCmd_Request __declspec(deprecated)
#endif

namespace lightning
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct LocCmd_Request_
{
  using Type = LocCmd_Request_<ContainerAllocator>;

  explicit LocCmd_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->map_id = "";
    }
  }

  explicit LocCmd_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : map_id(_alloc),
    header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->map_id = "";
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;
  using _z_type =
    double;
  _z_type z;
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const double & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const double & _arg)
  {
    this->z = _arg;
    return *this;
  }
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t CMD_LOC_SET_MAP =
    1u;
  static constexpr uint8_t CMD_LOC_INIT_POSE =
    3u;
  static constexpr uint8_t CMD_LOC_INIT_LIST =
    4u;

  // pointer types
  using RawPtr =
    lightning::srv::LocCmd_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const lightning::srv::LocCmd_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lightning::srv::LocCmd_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lightning::srv::LocCmd_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lightning__srv__LocCmd_Request
    std::shared_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lightning__srv__LocCmd_Request
    std::shared_ptr<lightning::srv::LocCmd_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocCmd_Request_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->map_id != other.map_id) {
      return false;
    }
    if (this->header != other.header) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocCmd_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocCmd_Request_

// alias to use template instance with default allocator
using LocCmd_Request =
  lightning::srv::LocCmd_Request_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocCmd_Request_<ContainerAllocator>::CMD_LOC_SET_MAP;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocCmd_Request_<ContainerAllocator>::CMD_LOC_INIT_POSE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocCmd_Request_<ContainerAllocator>::CMD_LOC_INIT_LIST;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace lightning


#ifndef _WIN32
# define DEPRECATED__lightning__srv__LocCmd_Response __attribute__((deprecated))
#else
# define DEPRECATED__lightning__srv__LocCmd_Response __declspec(deprecated)
#endif

namespace lightning
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct LocCmd_Response_
{
  using Type = LocCmd_Response_<ContainerAllocator>;

  explicit LocCmd_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0ul;
    }
  }

  explicit LocCmd_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0ul;
    }
  }

  // field types and members
  using _result_type =
    uint32_t;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const uint32_t & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lightning::srv::LocCmd_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const lightning::srv::LocCmd_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lightning::srv::LocCmd_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lightning::srv::LocCmd_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lightning__srv__LocCmd_Response
    std::shared_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lightning__srv__LocCmd_Response
    std::shared_ptr<lightning::srv::LocCmd_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocCmd_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocCmd_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocCmd_Response_

// alias to use template instance with default allocator
using LocCmd_Response =
  lightning::srv::LocCmd_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace lightning

namespace lightning
{

namespace srv
{

struct LocCmd
{
  using Request = lightning::srv::LocCmd_Request;
  using Response = lightning::srv::LocCmd_Response;
};

}  // namespace srv

}  // namespace lightning

#endif  // LIGHTNING__SRV__DETAIL__LOC_CMD__STRUCT_HPP_
