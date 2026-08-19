# Lightning real-hardware tools

This package contains isolated utilities for validating real Mid360 data and
feeding recorded data to Lightning-LM. The Livox online path publishes the
same RViz outputs as the standard PointCloud2 path. Recorded bags,
`livox_ros_driver2`, and `lightning_sim` remain unchanged.

The `livox_custom_to_pointcloud2` node converts `/livox/lidar`
(`livox_ros_driver2/msg/CustomMsg`) to `/livox/points`
(`sensor_msgs/msg/PointCloud2`) for raw-scan inspection in RViz.
The RViz launch uses the current wall-clock time only on the converted display
topic so that recorded scans are not rejected as stale. The original bag
timestamps and `/livox/lidar` messages are never modified.

To view a recorded static bag, start the viewer first and then play the bag in a
second terminal:

```bash
ros2 launch lightning_real view_mid360.launch.py
ros2 bag play bags/real_mid360/static/<bag-directory>
```

Run the latest dynamic Mid360 bag through Lightning-LM from the workspace root:

```bash
src/lightning_real/scripts/run_offline_slam.sh
```

The baseline configuration is `config/mid360_real.yaml`. It uses the original
`/livox/lidar` and `/livox/imu` messages, preserves their timestamps, disables
the optional 2.5D map, and writes each run into a new timestamped directory
under `runs/real_mid360/`. The initial integrated lidar/IMU extrinsic is the
identity until a measured or calibrated transform is available.

To replay the loop bag through online Lightning-LM, start the algorithm and
prepared RViz display first, then start the bag in a second terminal. Domain 77
keeps replay traffic isolated from the real robot:

```bash
ROS_DOMAIN_ID=77 ros2 launch lightning_real online_mapping.launch.py
ROS_DOMAIN_ID=77 ros2 bag play \
  bags/real_mid360/dynamic/mid360-loop-20260814-180225 \
  --clock --rate 1.0
```

RViz uses `map` and displays `/lightning/map`,
`/lightning/current_scan`, `/lightning/path`, and `/lightning/odom`.
