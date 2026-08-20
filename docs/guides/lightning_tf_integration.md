# Lightning-LM TF Integration Guide

## Goal

Final localization TF chain:

```text
map -> lightning_map -> odom -> base_link
```

## Inputs

Lightning native localization:

```text
map -> base_link
```

Chassis odometry:

```text
odom -> base_link
```

## Start Lightning with TF isolated

Use the same `ROS_DOMAIN_ID` in every terminal involved in the test.

For normal integrated localization startup, use:

```bash
cd /home/kepler/lightning_lm_ws
source install/setup.bash
export ROS_DOMAIN_ID=0

ros2 launch xyp_mid360_navigation lightning_localization_tf.launch.py
```

The launch starts Lightning localization, the TF wrapper, and the fixed horizontal `map -> lightning_map` static TF together. The default `map_run_dir` points to:

```text
/home/kepler/lightning_lm_ws/runs/real_mid360/offline-mid360-loop-20260814-180225-20260819-122805
```

The commands below are the manual equivalent and are useful for debugging.

```bash
cd /home/kepler/lightning_lm_ws/runs/real_mid360/offline-mid360-loop-20260814-180225-20260819-122805
source /home/kepler/lightning_lm_ws/install/setup.bash
export ROS_DOMAIN_ID=0

ros2 run lightning run_loc_online   --config /home/kepler/lightning_lm_ws/src/lightning_real/config/mid360_real.yaml   --ros-args --remap /tf:=/lightning_tf
```

Expected:

```text
/lightning_tf: map -> base_link
```

## Start wrapper

```bash
cd /home/kepler/lightning_lm_ws
source install/setup.bash
export ROS_DOMAIN_ID=0

ros2 run xyp_mid360_navigation lightning_map_to_odom_tf.py
```

The wrapper computes:

```text
T_lightning_map_odom = T_lightning_map_base * inverse(T_odom_base)
```

Expected output in `/tf`:

```text
lightning_map -> odom
```

## Add horizontal map frame

Validated static transform:

```bash
cd /home/kepler/lightning_lm_ws
source install/setup.bash
export ROS_DOMAIN_ID=0

ros2 run tf2_ros static_transform_publisher   --x 0 --y 0 --z 0   --qx 0.008708 --qy 0.042288 --qz 0.0 --qw 0.999068   --frame-id map --child-frame-id lightning_map
```

Expected final TF:

```text
map -> lightning_map -> odom -> base_link
```

## Validate

Check isolated Lightning TF:

```bash
ros2 topic echo /lightning_tf --once
```

Check wrapper output:

```bash
ros2 run tf2_ros tf2_echo lightning_map odom
```

Check final chain:

```bash
ros2 run tf2_ros tf2_echo map base_link
```

During bag replay, all commands should continuously output transforms.

## Common Problems

If `/lightning_tf` is unknown or subscribers are missing, verify all terminals use the same `ROS_DOMAIN_ID`.

If wrapper logs `Waiting for odom->base_link`, verify the bag or chassis is publishing `/tf` with:

```text
odom -> base_link
```

If `map -> base_link` z drift grows after adding `map -> lightning_map`, the static TF direction is likely reversed.
