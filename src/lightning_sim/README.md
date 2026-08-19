# lightning_sim

Gazebo Fortress simulation assets used to validate Lightning-LM without changing
the upstream algorithm or Livox driver packages.

## Stage 2: baseline world

Build only this package:

```bash
cd /path/to/lightning_lm_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-select lightning_sim
source install/setup.bash
ros2 launch lightning_sim world.launch.py
```

Expected result: a 24 m x 18 m enclosed test area with asymmetric walls,
pillars, and boxes.

## Stage 3: four-wheel mecanum cart

The world contains a four-wheel mecanum cart at `(0, -6.5)`. The launch file
bridges `/cmd_vel`, `/odom`, `/tf`, and `/clock` between ROS 2 and Gazebo. The
MecanumDrive plugin accepts both `linear.x` and `linear.y` commands, so lateral
motion can be tested in addition to rotation.
No LiDAR or IMU is attached at this stage.

After launching the world, a short ROS 2 command can verify motion:

```bash
ros2 topic pub --once /cmd_vel geometry_msgs/msg/Twist \
  "{linear: {x: 0.4}, angular: {z: 0.0}}"
```

## Stage 4: baseline IMU

An ideal IMU is colocated with the cart's `base_link`, with zero relative
rotation. It publishes `/imu` at 200 Hz. Sensor noise is intentionally disabled
for the baseline test.

## Stage 5: idealized Mid-360 lidar

An idealized GPU lidar is mounted 0.28 m above the IMU with zero relative
rotation. It publishes standard ROS 2 `sensor_msgs/PointCloud2` messages on
`/livox/lidar` at 10 Hz. The regular 720 x 24 scan approximates the Mid-360
field of view, but does not reproduce its non-repetitive scan pattern or Livox
per-point timing fields.

## Stage 6: Lightning-LM cloud adapter

`sim_cloud_adapter` keeps the Gazebo cloud on `/livox/lidar` and publishes an
algorithm-ready `/points_raw` cloud with `x`, `y`, `z`, `intensity`, `time`, and
`ring` fields. `config/lightning_sim.yaml` selects Lightning-LM's Velodyne-style
PointCloud2 preprocessing path and preserves the simulated 0.28 m IMU-to-lidar
translation. The upstream Lightning-LM configuration files remain unchanged.

## Stage 7: simulation bag recording

Run `scripts/record_sim_bag.sh` from the workspace root to record only the
algorithm input and verification topics. Bags are written to timestamped,
non-overwriting directories below `bags/lightning_sim/`.

## Stage 8: isolated offline SLAM run

Run `scripts/run_offline_slam.sh` from the workspace root. It selects the latest
simulation bag by default and creates a new directory below
`runs/lightning_sim/`. This isolates Lightning-LM's map-directory replacement
behavior to that single run and preserves every earlier result.

The simulation configuration uses Lightning-LM's 3D point-cloud map and keeps
the optional G2P5 2D occupancy projection disabled. A ground vehicle still has
an approximately planar trajectory, while walls, pillars, and other geometry
remain three-dimensional in `global.pcd`.

## Stage 9: online RViz mapping

`online_mapping.launch.py` starts the simulation, Lightning-LM online SLAM,
and RViz together. Lightning publishes `/lightning/map`,
`/lightning/current_scan`, `/lightning/path`, `/lightning/odom`, and the
`map -> lightning_base_link` transform. The original Gazebo odometry TF remains
separate, so estimator and simulator ground-truth trees do not conflict.
