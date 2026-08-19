"""Convert real Livox CustomMsg data and display the raw scan in RViz."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    share = Path(get_package_share_directory("lightning_real"))
    rviz_config = share / "rviz" / "mid360_raw.rviz"

    converter = Node(
        package="lightning_real",
        executable="livox_custom_to_pointcloud2",
        name="livox_custom_to_pointcloud2",
        parameters=[{
            "input_topic": "/livox/lidar",
            "output_topic": "/livox/points",
            "frame_override": "map",
            "use_current_time": True,
            "min_range": 0.05,
            "max_range": 200.0,
        }],
        output="screen",
    )
    static_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="mid360_view_static_tf",
        arguments=[
            "--x", "0", "--y", "0", "--z", "0",
            "--roll", "0", "--pitch", "0", "--yaw", "0",
            "--frame-id", "map", "--child-frame-id", "livox_frame",
        ],
        output="screen",
    )
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        name="mid360_raw_rviz",
        arguments=["-d", str(rviz_config)],
        condition=IfCondition(LaunchConfiguration("rviz")),
        output="screen",
    )

    return LaunchDescription([
        DeclareLaunchArgument("rviz", default_value="true"),
        converter,
        static_tf,
        rviz,
    ])
