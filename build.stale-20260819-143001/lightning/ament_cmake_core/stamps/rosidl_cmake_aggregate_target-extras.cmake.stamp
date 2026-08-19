# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target lightning::lightning
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${lightning_TARGETS}.
if(lightning_TARGETS AND NOT TARGET lightning::lightning)
  add_library(lightning::lightning INTERFACE IMPORTED)
  set_target_properties(lightning::lightning PROPERTIES
    INTERFACE_LINK_LIBRARIES "${lightning_TARGETS}")
endif()
