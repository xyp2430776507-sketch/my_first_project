#!/usr/bin/env bash
set -euo pipefail

workspace="${PWD}"
if [[ ! -f "${workspace}/src/lightning_real/package.xml" ]] ||
   [[ ! -x "${workspace}/src/lightning-lm/bin/run_slam_offline" ]]; then
  echo "Run this script from the lightning_lm_ws workspace root." >&2
  exit 2
fi

if [[ $# -ge 1 ]]; then
  bag_path="$1"
else
  bag_path="$(ls -1dt "${workspace}"/bags/real_mid360/dynamic/mid360-dynamic-* 2>/dev/null | head -n 1 || true)"
fi

if [[ -z "${bag_path}" ]] || [[ ! -f "${bag_path}/metadata.yaml" ]]; then
  echo "No valid real Mid360 ROS 2 bag directory was found." >&2
  exit 3
fi

bag_path="$(realpath "${bag_path}")"
config_path="$(realpath "${workspace}/src/lightning_real/config/mid360_real.yaml")"
binary_path="$(realpath "${workspace}/src/lightning-lm/bin/run_slam_offline")"
bag_name="$(basename "${bag_path}")"
timestamp="$(date +%Y%m%d-%H%M%S)"
run_path="${workspace}/runs/real_mid360/offline-${bag_name}-${timestamp}"

if [[ -e "${run_path}" ]]; then
  echo "Refusing to overwrite existing run: ${run_path}" >&2
  exit 4
fi

mkdir -p "${run_path}"
{
  echo "bag=${bag_path}"
  echo "config=${config_path}"
  echo "binary=${binary_path}"
  echo "started=$(date --iso-8601=seconds)"
} > "${run_path}/run-info.txt"

echo "Offline result directory: ${run_path}"
echo "Input bag: ${bag_path}"
echo "Configuration: ${config_path}"

cd "${run_path}"
set +e
"${binary_path}" \
  "--input_bag=${bag_path}" \
  "--config=${config_path}" 2>&1 | tee lightning.log
status=${PIPESTATUS[0]}
set -e

echo "finished=$(date --iso-8601=seconds)" >> run-info.txt
echo "exit_status=${status}" >> run-info.txt
exit "${status}"
