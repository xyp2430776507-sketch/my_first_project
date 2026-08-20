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

## Phase 3E: Integrated Localization TF Launch

Status: PASSED

- Added launch entry: `ros2 launch xyp_mid360_navigation lightning_localization_tf.launch.py`
- Default `map_run_dir`: `/home/kepler/lightning_lm_ws/runs/real_mid360/offline-mid360-loop-20260814-180225-20260819-122805`
- The launch runs Lightning from `map_run_dir` so the existing relative config value `system.map_path: ./data/new_map/` resolves to the verified map.
- The launch starts:
  - Lightning online localization with `/tf` remapped to `/lightning_tf`
  - `lightning_map_to_odom_tf.py`
  - fixed `map -> lightning_map` static TF
- `xyp_mid360_navigation` rebuild passed.
- `ros2 launch xyp_mid360_navigation lightning_localization_tf.launch.py --show-args` passed with workspace-local `ROS_HOME` / `ROS_LOG_DIR`.
- Full bag replay through the integrated launch passed with recorded TF topics:

```text
/lightning_tf map->base_link count: 45088
/tf lightning_map->odom count:     45088
/tf odom->base_link count:          7534
/tf_static map->lightning_map:      1
```

- Recorded final chain `map -> lightning_map -> odom -> base_link` kept `map -> base_link` z_range at about `0.134 m` with `z_std` about `0.0289 m`.

## Phase 4A: Nav2 Static Global Map

Status: PASSED

Goal:

```text
Lightning 3D global.pcd
  -> horizontal map frame
  -> Nav2-compatible map.pgm / map.yaml
```

Final map:

```text
/home/kepler/lightning_lm_ws/runs/real_mid360/phase4a-final-20260820-132916/map.yaml
```

Input map:

```text
runs/real_mid360/offline-mid360-loop-20260814-180225-20260819-122805/data/new_map/global.pcd
```

Implemented tool:

```text
src/xyp_mid360_navigation/scripts/pcd_to_nav2_map.py
```

Important decisions:

- Do not enable Lightning `system.with_g2p5` for the final map. Investigation showed g2p5 works in Lightning's native tilted `lightning_map`, and the external `map -> lightning_map` static TF does not affect its internal keyframes.
- Keep Lightning-LM core unchanged.
- Use the verified Phase 3D `map -> lightning_map` rotation to horizontalize `global.pcd`.
- Restore observed free space from the original MID360 bag and the Phase 3E TF bag.
- Clear robot-self trajectory artifacts only inside a shrunken base footprint.
- Do not do inflation in the static map; leave inflation to Nav2.

Final map parameters:

```text
frame semantics: map
resolution:      0.1 m/cell
size:            487 x 680 cells
origin:          [-23.6, -43.4, 0.0]
```

Final PGM / map_server semantics:

```text
OCCUPIED_PIXEL = 0
FREE_PIXEL     = 254
UNKNOWN_PIXEL  = 128

occupied: 10023
free:     23494
unknown: 297643
```

Final free connected-component validation:

```text
free component count:       166
largest free component:     23256 cells
largest / total free:       98.987%
largest component area:     232.56 m^2

trajectory samples:         754
trajectory free:            752
trajectory occupied:        0
trajectory unknown:         0
trajectory out_of_grid:     0
trajectory in largest comp: 752 / 752 = 100%
```

Key pitfalls resolved:

- The original Lightning map is tilted; final Nav2 map must belong to horizontal `map`, not `lightning_map`.
- `global.pcd` alone has little free-space evidence; LiDAR ray tracing is needed to recover observed free.
- Robot-self points produced trajectory-shaped occupied artifacts; these were removed with a shrunken trajectory footprint.
- PGM unknown pixel `205` was semantically wrong for `free_thresh=0.25`; unknown is now `128` and write-time semantic validation prevents threshold/pixel mismatch.

## Current Issues

- Phase 4A is complete, but Phase 4B has not started.
- Nav2 planner/controller integration has not yet been validated with the existing `map -> lightning_map -> odom -> base_link` TF chain.
- AMCL should not be used as the primary localization source in Phase 4B; localization should come from the completed Lightning TF chain.
- Real-time MID360 obstacle input for Nav2 local costmap is still future Phase 4C work.

## Next Steps

1. Begin Phase 4B: start only the Nav2 basic chain needed to validate map/TF/planning, without AMCL as the main localization source.
2. Validate that Nav2 has no `map` / `odom` / `base_link` TF errors and that a 2D Goal can produce a global path.
3. Do not start real robot motion in Phase 4B. If controller output is tested later, remap `/cmd_vel` to a test topic such as `/nav_test_cmd_vel`.
