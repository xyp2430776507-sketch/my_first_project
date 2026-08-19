#!/usr/bin/env bash
set -euo pipefail

if [[ ! -f "${PWD}/src/lightning_sim/package.xml" ]]; then
  echo "Run this script from the lightning_lm_ws workspace root." >&2
  exit 2
fi

bag_root="${1:-${PWD}/bags/lightning_sim}"
timestamp="$(date +%Y%m%d-%H%M%S)"
bag_path="${bag_root}/sim-${timestamp}"

mkdir -p "${bag_root}"
if [[ -e "${bag_path}" ]]; then
  echo "Refusing to overwrite existing bag: ${bag_path}" >&2
  exit 3
fi

echo "Recording simulation bag to: ${bag_path}"
echo "Press Ctrl+C once to stop and finalize the bag safely."

exec ros2 bag record \
  --storage sqlite3 \
  --output "${bag_path}" \
  /points_raw \
  /imu \
  /tf \
  /tf_static \
  /odom \
  /clock \
  /cmd_vel
