cmake_minimum_required(VERSION 3.8)
project(xyp_mid360_navigation)

find_package(ament_cmake REQUIRED)

install(PROGRAMS
  scripts/lightning_map_to_odom_tf.py
  scripts/odom_handedness_adapter.py
  scripts/plan_follow_waypoints.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  config
  launch
  DESTINATION share/${PROJECT_NAME}
  PATTERN "__pycache__" EXCLUDE
)

ament_package()
