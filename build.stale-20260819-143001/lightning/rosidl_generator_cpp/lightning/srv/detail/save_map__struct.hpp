// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from lightning:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef LIGHTNING__SRV__DETAIL__SAVE_MAP__STRUCT_HPP_
#define LIGHTNING__SRV__DETAIL__SAVE_MAP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__lightning__srv__SaveMap_Request __attribute__((deprecated))
#else
# define DEPRECATED__lightning__srv__SaveMap_Request __declspec(deprecated)
#endif

namespace lightning
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SaveMap_Request_
{
  using Type = SaveMap_Request_<ContainerAllocator>;

  explicit SaveMap_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
    }
  }

  explicit SaveMap_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : map_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->map_id = "";
    }
  }

  // field types and members
  using _map_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_id_type map_id;

  // setters for named parameter idiom
  Type & set__map_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lightning::srv::SaveMap_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const lightning::srv::SaveMap_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lightning::srv::SaveMap_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lightning::srv::SaveMap_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lightning__srv__SaveMap_Request
    std::shared_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lightning__srv__SaveMap_Request
    std::shared_ptr<lightning::srv::SaveMap_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SaveMap_Request_ & other) const
  {
    if (this->map_id != other.map_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const SaveMap_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SaveMap_Request_

// alias to use template instance with default allocator
using SaveMap_Request =
  lightning::srv::SaveMap_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace lightning


#ifndef _WIN32
# define DEPRECATED__lightning__srv__SaveMap_Response __attribute__((deprecated))
#else
# define DEPRECATED__lightning__srv__SaveMap_Response __declspec(deprecated)
#endif

namespace lightning
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SaveMap_Response_
{
  using Type = SaveMap_Response_<ContainerAllocator>;

  explicit SaveMap_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response = 0ul;
    }
  }

  explicit SaveMap_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->response = 0ul;
    }
  }

  // field types and members
  using _response_type =
    uint32_t;
  _response_type response;

  // setters for named parameter idiom
  Type & set__response(
    const uint32_t & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    lightning::srv::SaveMap_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const lightning::srv::SaveMap_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      lightning::srv::SaveMap_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      lightning::srv::SaveMap_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__lightning__srv__SaveMap_Response
    std::shared_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__lightning__srv__SaveMap_Response
    std::shared_ptr<lightning::srv::SaveMap_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SaveMap_Response_ & other) const
  {
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SaveMap_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SaveMap_Response_

// alias to use template instance with default allocator
using SaveMap_Response =
  lightning::srv::SaveMap_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace lightning

namespace lightning
{

namespace srv
{

struct SaveMap
{
  using Request = lightning::srv::SaveMap_Request;
  using Response = lightning::srv::SaveMap_Response;
};

}  // namespace srv

}  // namespace lightning

#endif  // LIGHTNING__SRV__DETAIL__SAVE_MAP__STRUCT_HPP_
