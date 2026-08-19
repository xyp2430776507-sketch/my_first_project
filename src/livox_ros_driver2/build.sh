#!/bin/bash

set -e

readonly VERSION_HUMBLE="humble"
readonly VERSION_JAZZY="jazzy"

pushd "$(dirname "$0")" > /dev/null
echo "Working Path: $(pwd)"

ROS_DISTRO_ARG=""
case "$1" in
  ROS2)
    ROS_DISTRO_ARG="${ROS_DISTRO:-}"
    ;;
  humble)
    ROS_DISTRO_ARG="${VERSION_HUMBLE}"
    ;;
  jazzy)
    ROS_DISTRO_ARG="${VERSION_JAZZY}"
    ;;
  *)
    echo "Invalid argument. Use ROS2, humble, or jazzy."
    exit 1
    ;;
esac

echo "ROS version is: ROS2${ROS_DISTRO_ARG:+ ($ROS_DISTRO_ARG)}"

# Clear artifacts from previous builds.
rm -rf ../../build/ ../../devel/ ../../install/

pushd ../../ > /dev/null
colcon build --cmake-args -DDISTRO_ROS="${ROS_DISTRO_ARG}"
popd > /dev/null

popd > /dev/null
