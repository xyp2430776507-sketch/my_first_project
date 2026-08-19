# AI Change Log

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
