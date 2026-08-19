# xyp_mid360_navigation

Isolated adapter for the K3W Mid-360 omni-chassis navigation test.

The first launch file, `inspect_costmaps.launch.py`, starts only the controller
and planner costmaps. All controller velocity output is remapped to
`/xyp/nav_cmd_vel_unconnected`; it is deliberately not connected to
`/chassis_cmd_vel`.

Required live inputs:

- `/livox/lidar` (`sensor_msgs/msg/PointCloud2`)
- `/odom` (`nav_msgs/msg/Odometry`)
- `odom -> base_link -> livox_frame` TF

The package does not modify `kepler_nav` or `livox_ros_driver2`.

`navigation_chassis.launch.py` is an explicitly selected real-motion test
mode.  It reuses the installed chassis configuration, subscribes only to
`/xyp/nav_cmd_vel_unconnected`, and clamps chassis limits to 0.08 m/s and
0.20 rad/s.  Stop the original chassis launch before starting it, and never
run both chassis launches at the same time.
