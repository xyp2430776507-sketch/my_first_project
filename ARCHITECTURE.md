# Architecture

## Package Relationships

- `lightning` is the core algorithm package. It depends on common ROS 2 messages, TF, PCL conversion, `livox_ros_driver2` message types, and exposes `run_slam_*` / `run_loc_*` executables.
- `livox_ros_driver2` provides the Livox device node and custom point cloud messages consumed by `lightning` and `lightning_real`.
- `lightning_sim` depends on `lightning` at runtime and adapts Gazebo point clouds into the PointCloud2 layout expected by Lightning-LM.
- `lightning_real` depends on `livox_ros_driver2` and provides real-data inspection/replay helpers without modifying `lightning` or the Livox driver.
- `xyp_mid360_navigation` is separate from SLAM internals. It uses Nav2, chassis control, odometry, TF, and Mid-360 lidar topics for navigation validation.

## Core Lightning-LM

Installed executables from `src/lightning-lm/src/app/CMakeLists.txt`:

- `run_slam_online`
- `run_slam_offline`
- `run_loc_online`
- `run_loc_offline`

Main configured input topics:

- `common.lidar_topic`: standard `sensor_msgs/msg/PointCloud2`
- `common.livox_lidar_topic`: `livox_ros_driver2/msg/CustomMsg`
- `common.imu_topic`: `sensor_msgs/msg/Imu`

Online SLAM node:

- Node name: `lightning_slam`
- Subscribes to configured IMU, PointCloud2 lidar, and Livox CustomMsg topics.
- Publishes `/lightning/map`, `/lightning/current_scan`, `/lightning/path`, `/lightning/odom`.
- Broadcasts RViz TF from `map` to `lightning_base_link`.
- Provides service `lightning/save_map` using `lightning/srv/SaveMap`.

Offline SLAM:

- Reads ROS 2 bag data through `RosbagIO`.
- Handles configured IMU and PointCloud2 topics.
- Also handles `/livox/lidar` as Livox `CustomMsg`.
- Saves maps under the active run directory as `data/new_map/`, including `global.pcd`; if G2P5 is enabled, also writes `map.pgm` and `map.yaml`.

Online localization:

- Uses node name `lightning_slam` in `LocSystem`.
- Reads map path from `system.map_path`.
- Subscribes to configured IMU, PointCloud2 lidar, and Livox CustomMsg topics.
- Publishes TF when `pub_tf` is enabled.

## Simulation Link

`lightning_sim/world.launch.py` starts Gazebo Fortress with `baseline_world.sdf`, `ros_gz_bridge`, a static lidar TF, and `sim_cloud_adapter`.

Simulation bridge topics:

- Gazebo `/model/lightning_cart/cmd_vel` remapped to ROS `/cmd_vel`.
- `/clock` bridged to ROS `/clock`.
- `/imu` bridged as `sensor_msgs/msg/Imu`.
- Gazebo `/livox/lidar/points` remapped to ROS `/livox/lidar` as `sensor_msgs/msg/PointCloud2`.

Simulation adapter:

- Node: `sim_cloud_adapter`
- Subscribes: `/livox/lidar` (`sensor_msgs/msg/PointCloud2`)
- Publishes: `/points_raw` (`sensor_msgs/msg/PointCloud2`)
- Adds/normalizes fields `x`, `y`, `z`, `intensity`, `time`, `ring` and sets frame `livox_frame`.

Simulation online mapping:

- `lightning_sim/online_mapping.launch.py` includes the world launch.
- Starts `ros2 run lightning run_slam_online --config <lightning_sim.yaml>`.
- Starts RViz with `online_mapping.rviz`.

Simulation bag path:

- `src/lightning_sim/scripts/record_sim_bag.sh` records `/points_raw`, `/imu`, `/tf`, `/tf_static`, `/odom`, `/clock`, `/cmd_vel`.

## Real Mid-360 Link

Livox driver:

- `msg_MID360_launch.py` starts `livox_ros_driver2_node` as `livox_lidar_publisher`.
- Uses `xfer_format=1`, so lidar output is Livox custom point cloud format.
- `rviz_MID360_launch.py` uses `xfer_format=0`, so lidar output is PointCloud2 for RViz display.

Real display adapter:

- Node: `livox_custom_to_pointcloud2`
- Subscribes: `/livox/lidar` (`livox_ros_driver2/msg/CustomMsg`)
- Publishes: `/livox/points` (`sensor_msgs/msg/PointCloud2`)
- Parameters include `input_topic`, `output_topic`, `frame_override`, `use_current_time`, `min_range`, `max_range`.

Real online mapping:

- `lightning_real/online_mapping.launch.py` starts `run_slam_online` directly from the installed `lightning` package path with `mid360_real.yaml`.
- RViz is configured for `/lightning/map`, `/lightning/current_scan`, `/lightning/path`, and `/lightning/odom`.

Real offline mapping:

- `src/lightning_real/scripts/run_offline_slam.sh` selects a Mid-360 bag, runs `src/lightning-lm/bin/run_slam_offline`, and writes a timestamped directory under `runs/real_mid360/`.

## Navigation Link

Costmap inspection:

- `inspect_costmaps.launch.py` starts Nav2 `controller_server`, `planner_server`, and lifecycle manager.
- Velocity output is remapped to `/xyp/nav_cmd_vel_unconnected`.

Real chassis test:

- `navigation_chassis.launch.py` starts `omni_chassis_control_node` with low limits.
- Chassis command topic is set to `/xyp/nav_cmd_vel_unconnected`.
- Raw chassis outputs are remapped from `/odom` to `/xyp/raw_odom` and `/tf` to `/xyp/raw_tf`.
- Starts `xyp_odom_handedness_adapter`.

Odometry adapter:

- Node: `xyp_odom_handedness_adapter`
- Subscribes: `/xyp/raw_odom`, `/xyp/raw_tf`, `/livox/imu`.
- Publishes: `/odom`, `/tf`.
- Reflects Y/yaw to ROS REP-103 style coordinates and uses IMU angular Z for yaw integration.

Waypoint helper:

- Node: `xyp_plan_follow_waypoints`
- Uses actions `/compute_path_to_pose` and `/follow_path`.
- Default frame is `odom`.

