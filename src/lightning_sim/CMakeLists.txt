cmake_minimum_required(VERSION 3.8)
project(lightning_sim)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(sim_cloud_adapter src/sim_cloud_adapter.cpp)
ament_target_dependencies(sim_cloud_adapter rclcpp sensor_msgs)

install(TARGETS sim_cloud_adapter
  DESTINATION lib/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/record_sim_bag.sh
  scripts/run_offline_slam.sh
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  models
  rviz
  worlds
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
