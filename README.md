# lightning_lm_ws

ROS 2 workspace for integrating Lightning-LM lidar SLAM/localization with Gazebo simulation, Livox Mid-360 data, and an isolated Mid-360 omni-chassis navigation adapter.

## Environment

- OS/ROS target from package docs: Ubuntu 22.04 with ROS 2 Humble or newer.
- Build system: `colcon` with `ament_cmake`.
- Core dependencies visible in package manifests/config: `rclcpp`, `sensor_msgs`, `nav_msgs`, `geometry_msgs`, `tf2_ros`, `pcl_ros`, `pcl_conversions`, `rviz2`, `ros_gz_sim`, `ros_gz_bridge`, Nav2 packages, Livox SDK/driver files.

## ROS 2 Packages

- `lightning` (`src/lightning-lm`): upstream Lightning-LM SLAM/localization core. Builds online/offline SLAM and localization executables, custom services, LIO, loop closing, G2P5 grid projection, map storage, and RViz publications.
- `lightning_sim`: Gazebo Fortress simulation assets, world/model files, `sim_cloud_adapter`, bag recording script, offline SLAM wrapper, and online mapping launch.
- `lightning_real`: real Mid-360 validation tools, `livox_custom_to_pointcloud2`, real-data offline SLAM wrapper, and launch files for raw Mid-360 viewing and online mapping replay.
- `livox_ros_driver2`: Livox ROS 2 driver and `CustomMsg`/`CustomPoint` messages.
- `xyp_mid360_navigation`: isolated Nav2/chassis adapter for Mid-360 omni-chassis tests; includes costmap-only launch, real-motion launch, odometry handedness adapter, and waypoint planner/follower.

## Common Commands

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

Focused builds:

```bash
colcon build --symlink-install --packages-select lightning_sim
colcon build --symlink-install --packages-select lightning_real
colcon build --symlink-install --packages-select xyp_mid360_navigation
```

Simulation:

```bash
ros2 launch lightning_sim world.launch.py
ros2 launch lightning_sim online_mapping.launch.py
src/lightning_sim/scripts/record_sim_bag.sh
src/lightning_sim/scripts/run_offline_slam.sh
```

Real Mid-360:

```bash
ros2 launch livox_ros_driver2 msg_MID360_launch.py
ros2 launch lightning_real view_mid360.launch.py
ros2 launch lightning_real online_mapping.launch.py
src/lightning_real/scripts/run_offline_slam.sh
```

Navigation adapter:

```bash
ros2 launch xyp_mid360_navigation inspect_costmaps.launch.py
ros2 launch xyp_mid360_navigation navigation_chassis.launch.py
ros2 run xyp_mid360_navigation plan_follow_waypoints.py
```

Direct Lightning-LM examples:

```bash
ros2 run lightning run_slam_online --config <config.yaml>
ros2 run lightning run_slam_offline --config <config.yaml> --input_bag <bag_dir>
ros2 run lightning run_loc_online --config <config.yaml>
ros2 run lightning run_loc_offline --config <config.yaml> --input_bag <bag_dir> --map_path <map_dir>
ros2 service call /lightning/save_map lightning/srv/SaveMap "{map_id: new_map}"
```

