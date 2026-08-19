# Current Status

## Completed

- Workspace contains five ROS 2 packages: `lightning`, `lightning_sim`, `lightning_real`, `livox_ros_driver2`, and `xyp_mid360_navigation`.
- Root `.gitignore` is configured to ignore colcon outputs, runtime data, bag/map artifacts, generated logs, and selected large media.
- `lightning` builds online/offline SLAM and localization executables and includes map save service support.
- Real Mid-360 offline SLAM on `bags/real_mid360/dynamic/mid360-loop-20260814-180225` succeeded with `exit_status=0`.
- The saved 3D map is stored under `runs/real_mid360/offline-mid360-loop-20260814-180225-20260819-122805/data/new_map/` as `0.pcd`, `global.pcd`, and `index.txt`.
- `src/lightning_real/config/mid360_real.yaml` keeps `system.with_g2p5: false`, so the current real-hardware run does not emit `map.pgm` / `map.yaml`.
- `lightning_sim` includes Gazebo world/model assets, a cloud adapter, online mapping launch, bag recording, and offline SLAM wrapper.
- `lightning_real` includes Mid-360 CustomMsg display conversion, real online mapping launch, and offline SLAM wrapper.
- `xyp_mid360_navigation` includes isolated Nav2 costmap/chassis launch files, odometry handedness adapter, and waypoint helper.
- Git config records branch `main` tracking `origin/main` at `https://github.com/xyp2430776507-sketch/my_first_project.git`.

## Current Issues

- Generated data and outputs exist locally under ignored directories such as `build/`, `install/`, `log/`, `bags/`, `runs/`, and `work/`.
- Large media/data files are present in source or docs paths, including Lightning-LM GIFs under `src/lightning-lm/doc/` and a vendored `thirdparty/Pangolin-0.9.3.zip`.
- The current real Mid-360 config does not yet produce a Nav2-ready 2D/2.5D map because `with_g2p5` is disabled.
- No test results were produced during this documentation update.

## Next Steps

- Confirm whether Phase 2 should enable `g2p5` for a ROS-compatible grid map or keep the 3D map only for localization.
- Inspect the localization output path and frame convention for the saved 3D map.
- Then move to Phase 3: real Mid-360 localization on the saved map.
