# CURRENT STATUS

## Workspace

- Workspace: `/home/kepler/lightning_lm_ws`
- Environment: Ubuntu 22.04, ROS 2 Humble
- Main packages: `lightning`, `lightning_real`, `lightning_sim`, `livox_ros_driver2`, `xyp_mid360_navigation`
- Workspace migration old-path issue has been fixed by clean rebuild. Old generated directories remain as `build.stale-*`, `install.stale-*`, and `log.stale-*`; do not delete until the system has stayed stable.

## Phase 1: Real MID360 Offline 3D Mapping

Status: PASSED

- Real bag: `bags/real_mid360/dynamic/mid360-loop-20260814-180225`
- Saved 3D map: `runs/real_mid360/offline-mid360-loop-20260814-180225-20260819-122805/data/new_map/`
- Map files confirmed: `0.pcd`, `global.pcd`, `index.txt`
- Input lidar topic: `/livox/lidar` (`livox_ros_driver2/msg/CustomMsg`)
- Input IMU topic: `/livox/imu` (`sensor_msgs/msg/Imu`)
- Current real config keeps `system.with_g2p5: false`; this run did not generate Nav2-ready `map.pgm` / `map.yaml`.

## Phase 2: 3D Map Quality and Tilt Investigation

Status: PASSED

Ground fitting on `global.pcd`:

```text
normal ~= [-0.0845, 0.0174, 0.9963]
total tilt ~= 4.95 deg
roll ~= 1.00 deg
pitch ~= 4.85 deg
ground RMSE ~= 1.72 cm
P95 ~= 3.30 cm
```

Confirmed conclusions:

- The local ground surface is consistent, but the whole Lightning map frame is tilted by about 5 degrees.
- The MID360 is mechanically mounted about 5 degrees forward relative to the level chassis.
- Do not change LiDAR-IMU `extrinsic_R` for this tilt.
- Do not change Lightning-LM LIO or IMU initialization for this phase.
- Keep the native Lightning map frame as `lightning_map` and add a separate horizontal `map` frame outside Lightning-LM.

## Phase 3A: Native Online Localization

Status: PASSED

- Entry: `ros2 run lightning run_loc_online`
- Config: `src/lightning_real/config/mid360_real.yaml`
- Map: saved `data/new_map/` from Phase 1
- Inputs: `/livox/lidar`, `/livox/imu`
- Native output: `map -> base_link`
- Logs confirmed successful lidar map matching, including `succ: 1` and `PGO received LidarLoc`.

## Phase 3B: Localization Stability Validation

Status: PASSED

Full-bag localization validation:

```text
pose samples: 469
unique poses: 442
start ~= [-0.052, 0.041, 0.051]
end ~= [-0.025, 0.002, 0.034]
loop start/end distance ~= 5 cm
max adjacent translation change ~= 0.411 m
```

No meter-scale localization jump was observed on this bag.

## Phase 3C: Standard ROS2 TF Integration

Status: PASSED

Problem:

```text
Lightning native TF: map -> base_link
Chassis / bag TF:   odom -> base_link
```

This gives `base_link` two TF parents if both are published into `/tf`.

Implemented approach:

- Remap Lightning native TF to `/lightning_tf`, keeping its native `map -> base_link` only as wrapper input.
- Add wrapper `lightning_map_to_odom_tf.py`.
- Wrapper computes `T_lightning_map_odom = T_lightning_map_base * inverse(T_odom_base)`.
- Wrapper publishes `lightning_map -> odom` into `/tf`.

Full-bag TF validation recorded:

```text
/lightning_tf map->base_link count: 44707
/tf lightning_map->odom count:     44707
/tf odom->base_link count:          7457
max lightning_map->odom receive gap: ~0.022 s
max adjacent translation jump:       ~0.741 m
```

Final Phase 3C chain passed:

```text
lightning_map -> odom -> base_link
```

## Phase 3D: Horizontal Map Frame

Status: PASSED

Added external horizontal frame design:

```text
map -> lightning_map -> odom -> base_link
```

The fixed rotation was derived from the fitted ground normal. Validated quaternion for `map -> lightning_map`:

```text
qx=0.008708, qy=0.042288, qz=0.0, qw=0.999068
```

Offline TF validation showed:

```text
before horizontalization: map->base_link z_range ~= 1.215 m
after horizontalization:  map->base_link z_range ~= 0.145 m
z_std after:              ~= 0.024 m
max jump after:           ~= 0.052 m
samples:                  44707
```

The positive quaternion direction is confirmed. The inverse direction made z drift worse.

## Current Issues

- The `map -> lightning_map` static TF is verified but not yet integrated into a permanent launch file.
- Nav2 integration has not started; Phase 4 is still next.
- Current real run did not produce a Nav2-ready 2D/2.5D map because `system.with_g2p5` remains disabled.

## Next Steps

1. Add a dedicated launch entry that starts Lightning localization, `lightning_map_to_odom_tf.py`, and the fixed `map -> lightning_map` static TF together.
2. Re-run the same bag replay through the integrated launch and confirm the full horizontal TF chain.
3. Begin Phase 4: generate/choose the 2D or 2.5D navigation map and connect Nav2 without real robot motion first.
