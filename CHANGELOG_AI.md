# AI Change Log

## 2026-08-20 - Phase 3 TF Integration and Horizontalization

- Files: generated `build/`, `install/`, and `log/` directories
  - Purpose: remove old absolute workspace path references after moving the workspace to `/home/kepler/lightning_lm_ws`.
  - Result: old generated directories were preserved as `*.stale-*` backups; the workspace was rebuilt and package prefixes/libraries resolved from the current path.

- Files: `src/lightning-lm/src/app/run_loc_online.cc`
  - Purpose: allow ROS 2 arguments such as `--ros-args -r /tf:=/lightning_tf` to coexist with the application's gflags parsing.
  - Result: `run_loc_online` can be started with ROS 2 TF remapping, allowing Lightning native TF to be isolated on `/lightning_tf`.

- Files: `src/xyp_mid360_navigation/scripts/lightning_map_to_odom_tf.py`
  - Purpose: convert Lightning native localization and chassis odometry into a standard ROS 2 TF chain.
  - Result: wrapper reads `/lightning_tf` `map -> base_link` and `/tf` `odom -> base_link`, computes `T_lightning_map_odom = T_lightning_map_base * inverse(T_odom_base)`, and publishes `lightning_map -> odom`.

- Files: `src/xyp_mid360_navigation/CMakeLists.txt`, `src/xyp_mid360_navigation/package.xml`
  - Purpose: install the TF wrapper and declare runtime TF dependencies.
  - Result: `ros2 run xyp_mid360_navigation lightning_map_to_odom_tf.py` is available after rebuilding `xyp_mid360_navigation`.

- Files: runtime validation bags under `runs/real_mid360/`
  - Purpose: validate full-bag Phase 3C TF continuity.
  - Result: recorded `/tf` and `/lightning_tf` showed `44707` `lightning_map -> odom` samples, `44707` Lightning `map -> base_link` samples, `7457` `odom -> base_link` samples, no TF-chain disappearance, and no meter-scale adjacent jump.

- Files: runtime static TF command, not yet permanent launch file
  - Purpose: validate horizontal `map -> lightning_map` frame from the fitted ground normal.
  - Result: quaternion `qx=0.008708, qy=0.042288, qz=0.0, qw=0.999068` reduced `map -> base_link` z range from about `1.215 m` to about `0.145 m`; Phase 3D passed.

- Files: `src/xyp_mid360_navigation/launch/lightning_localization_tf.launch.py`, `src/xyp_mid360_navigation/package.xml`
  - Purpose: make the verified localization TF chain available from one launch entry.
  - Result: `ros2 launch xyp_mid360_navigation lightning_localization_tf.launch.py` now starts Lightning localization with `/tf` remapped to `/lightning_tf`, the `lightning_map_to_odom_tf.py` wrapper, and the fixed `map -> lightning_map` static TF; the launch sets Lightning's working directory through `map_run_dir` so the relative `./data/new_map/` config resolves to the verified real map. Python syntax check, `colcon build --packages-select xyp_mid360_navigation`, default map-file existence check, and `ros2 launch ... --show-args` passed. Full bag replay through this launch also passed: `/lightning_tf map->base_link` and `/tf lightning_map->odom` both had `45088` samples, `/tf odom->base_link` had `7534` samples, `/tf_static map->lightning_map` had `1` sample, and final-chain z span was about `0.134 m`.

- Files: `src/xyp_mid360_navigation/scripts/lightning_map_to_odom_tf.py`
  - Purpose: avoid noisy traceback during normal launch shutdown.
  - Result: wrapper now handles `ExternalShutdownException` and repeated shutdown calls; short launch shutdown smoke no longer produced wrapper traceback.

- Files: `README.md`, `ARCHITECTURE.md`, `CURRENT_STATUS.md`, `CHANGELOG_AI.md`, `docs/decisions.md`, `docs/daily/2026-08-20.md`, `docs/guides/lightning_tf_integration.md`, `docs/problems/phase3_tf_conflict.md`
  - Purpose: document Phase 1 through Phase 3D validation and record Phase 4 as the next planned stage.
  - Result: handoff documentation now records the validated TF architecture, horizontalization decision, known remaining issues, and next steps without marking Nav2 as complete.

## 2026-08-19

- Files: `CURRENT_STATUS.md`, `docs/daily/2026-08-19.md`
  - Purpose: record Phase 2 map-output findings after a successful real Mid-360 offline SLAM replay.
  - Result: the saved 3D map path and file set were recorded; the current real config was documented as not emitting `map.pgm` / `map.yaml` because `with_g2p5` is disabled.

- Files: `.gitignore`
  - Purpose: ignore ROS 2 colcon outputs, runtime data, bag/map artifacts, generated logs, and selected large media.
  - Result: rules include `build/`, `install/`, `log/`, `bags/`, `runs/`, `work/`, `review_materials/extracted_media/`, `*.db3`, `*.pcd`, `*.zip`, `build*.log`, `frames_*.gv`, `frames_*.pdf`, `build-lightning.pid`, `src/lightning-lm/doc/*.gif`, and `review_materials/*.pptx`; `lightning_lm_ws.code-workspace` is explicitly unignored.

- Files: `AGENTS.md`, `CURRENT_STATUS.md`, `docs/daily/.gitkeep`, `docs/problems/.gitkeep`, `docs/decisions.md`
  - Purpose: add minimal handoff and status documentation.
  - Result: repository-level agent instructions and status skeleton were created.

- Files: `README.md`, `ARCHITECTURE.md`, `CURRENT_STATUS.md`, `CHANGELOG_AI.md`, `AGENTS.md`
  - Purpose: make the workspace understandable to a new AI without chat history.
  - Result: current repository overview, package relationships, confirmed topics/nodes/data flows, status, change log, and agent workflow were documented.
