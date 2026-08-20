"""Start Lightning localization with the verified standard TF chain."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    real_share = Path(get_package_share_directory("lightning_real"))
    lightning_prefix = Path(get_package_share_directory("lightning")).parent.parent

    config = LaunchConfiguration("config")
    map_run_dir = LaunchConfiguration("map_run_dir")
    loc_executable = lightning_prefix / "lib" / "lightning" / "run_loc_online"

    lightning_loc = ExecuteProcess(
        cmd=[
            str(loc_executable),
            "--config",
            config,
            "--ros-args",
            "--remap",
            "/tf:=/lightning_tf",
        ],
        cwd=map_run_dir,
        output="screen",
    )

    map_to_odom = Node(
        package="xyp_mid360_navigation",
        executable="lightning_map_to_odom_tf.py",
        name="lightning_map_to_odom_tf",
        output="screen",
        parameters=[
            {
                "lightning_tf_topic": "/lightning_tf",
                "odom_tf_topic": "/tf",
                "lightning_parent_frame": "map",
                "lightning_child_frame": "base_link",
                "output_parent_frame": "lightning_map",
                "odom_frame": "odom",
                "base_frame": "base_link",
                "max_time_delta_sec": 0.1,
            }
        ],
    )

    horizontal_map = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="map_to_lightning_map_static_tf",
        arguments=[
            "--x", "0",
            "--y", "0",
            "--z", "0",
            "--qx", "0.008708",
            "--qy", "0.042288",
            "--qz", "0.0",
            "--qw", "0.999068",
            "--frame-id", "map",
            "--child-frame-id", "lightning_map",
        ],
        output="screen",
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            "config",
            default_value=str(real_share / "config" / "mid360_real.yaml"),
            description="Lightning localization YAML config.",
        ),
        DeclareLaunchArgument(
            "map_run_dir",
            default_value=(
                "/home/kepler/lightning_lm_ws/runs/real_mid360/"
                "offline-mid360-loop-20260814-180225-20260819-122805"
            ),
            description="Run directory containing data/new_map for the relative map_path in the config.",
        ),
        lightning_loc,
        map_to_odom,
        horizontal_map,
    ])
