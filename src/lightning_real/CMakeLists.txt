cmake_minimum_required(VERSION 3.8)
project(lightning_real)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(livox_ros_driver2 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(livox_custom_to_pointcloud2 src/livox_custom_to_pointcloud2.cpp)
ament_target_dependencies(livox_custom_to_pointcloud2
  livox_ros_driver2
  rclcpp
  sensor_msgs
)

install(TARGETS livox_custom_to_pointcloud2
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/run_offline_slam.sh
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch rviz config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
