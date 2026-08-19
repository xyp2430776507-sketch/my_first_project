# Copyright(c) 2020 livoxtech limited.

cmake_minimum_required(VERSION 3.14)
project(livox_ros_driver2)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake/modules")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# Printf version info
include(cmake/version.cmake)
project(${PROJECT_NAME} VERSION ${LIVOX_ROS_DRIVER2_VERSION} LANGUAGES CXX)
message(STATUS "${PROJECT_NAME} version: ${LIVOX_ROS_DRIVER2_VERSION}")

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
find_package(PCL REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# check apr
find_package(PkgConfig)
pkg_check_modules(APR apr-1)
if(APR_FOUND)
  message(STATUS "APR include directories: ${APR_INCLUDE_DIRS}")
  message(STATUS "APR libraries: ${APR_LIBRARIES}")
endif()

# generate custom msg headers
set(LIVOX_INTERFACES livox_interfaces2)
rosidl_generate_interfaces(${LIVOX_INTERFACES}
  "msg/CustomPoint.msg"
  "msg/CustomMsg.msg"
  DEPENDENCIES builtin_interfaces std_msgs
  LIBRARY_NAME ${PROJECT_NAME}
)

## Use the bundled Livox-SDK2 library for the target architecture.
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|amd64|AMD64)$")
  set(LIVOX_SDK_ARCH amd64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64|arm64)$")
  set(LIVOX_SDK_ARCH arm64)
else()
  message(FATAL_ERROR
    "Unsupported target architecture: ${CMAKE_SYSTEM_PROCESSOR}"
  )
endif()

set(LIVOX_SDK_ROOT
  "${PROJECT_SOURCE_DIR}/Livox-SDK2"
)
set(LIVOX_LIDAR_SDK_LIBRARY
  "${LIVOX_SDK_ROOT}/lib/${LIVOX_SDK_ARCH}/liblivox_lidar_sdk_shared.so"
)
set(LIVOX_LIDAR_SDK_INCLUDE_DIR
  "${LIVOX_SDK_ROOT}/include"
)

if(NOT EXISTS "${LIVOX_LIDAR_SDK_LIBRARY}")
  message(FATAL_ERROR
    "Livox-SDK2 library not found: ${LIVOX_LIDAR_SDK_LIBRARY}"
  )
endif()

if(NOT EXISTS "${LIVOX_LIDAR_SDK_INCLUDE_DIR}/livox_lidar_api.h")
  message(FATAL_ERROR
    "Livox-SDK2 headers not found: ${LIVOX_LIDAR_SDK_INCLUDE_DIR}"
  )
endif()

message(STATUS "Using bundled Livox-SDK2 for ${LIVOX_SDK_ARCH}")

install(FILES "${LIVOX_LIDAR_SDK_LIBRARY}"
  DESTINATION lib
)

## PCL library
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# livox ros2 driver target
ament_auto_add_library(${PROJECT_NAME} SHARED
  src/livox_ros_driver2.cpp
  src/lddc.cpp
  src/driver_node.cpp
  src/lds.cpp
  src/lds_lidar.cpp

  src/comm/comm.cpp
  src/comm/ldq.cpp
  src/comm/semaphore.cpp
  src/comm/lidar_imu_data_queue.cpp
  src/comm/cache_index.cpp
  src/comm/pub_handler.cpp

  src/parse_cfg_file/parse_cfg_file.cpp
  src/parse_cfg_file/parse_livox_lidar_cfg.cpp

  src/call_back/lidar_common_callback.cpp
  src/call_back/livox_lidar_callback.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${livox_sdk_INCLUDE_DIRS})

# Use the standard ROS environment when DISTRO_ROS was not passed explicitly.
if(NOT DISTRO_ROS AND DEFINED ENV{ROS_DISTRO})
  set(DISTRO_ROS "$ENV{ROS_DISTRO}")
endif()

# get include directories of custom msg headers
if(DISTRO_ROS STREQUAL "humble" OR DISTRO_ROS STREQUAL "jazzy")
  rosidl_get_typesupport_target(cpp_typesupport_target
    ${LIVOX_INTERFACES} "rosidl_typesupport_cpp"
  )
  target_link_libraries(${PROJECT_NAME} "${cpp_typesupport_target}")
else()
  set(LIVOX_INTERFACE_TARGET "${LIVOX_INTERFACES}__rosidl_typesupport_cpp")
  add_dependencies(${PROJECT_NAME} ${LIVOX_INTERFACES})
  get_target_property(LIVOX_INTERFACES_INCLUDE_DIRECTORIES
    ${LIVOX_INTERFACE_TARGET} INTERFACE_INCLUDE_DIRECTORIES
  )
endif()

# include file directory
target_include_directories(${PROJECT_NAME} PUBLIC
  ${PCL_INCLUDE_DIRS}
  ${APR_INCLUDE_DIRS}
  ${LIVOX_LIDAR_SDK_INCLUDE_DIR}
  ${LIVOX_INTERFACES_INCLUDE_DIRECTORIES}   # for custom msgs
  3rdparty
  src
)

# link libraries
target_link_libraries(${PROJECT_NAME}
  ${LIVOX_LIDAR_SDK_LIBRARY}
  ${LIVOX_INTERFACE_TARGET}   # for custom msgs
  ${PPT_LIBRARY}
  ${Boost_LIBRARY}
  ${PCL_LIBRARIES}
  ${APR_LIBRARIES}
)

rclcpp_components_register_node(${PROJECT_NAME}
  PLUGIN "livox_ros::DriverNode"
  EXECUTABLE ${PROJECT_NAME}_node
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package(INSTALL_TO_SHARE
  config
  launch
)
