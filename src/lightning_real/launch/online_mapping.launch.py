"""Run Lightning-LM online on recorded Mid360 CustomMsg data."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    real_share = Path(get_package_share_directory("lightning_real"))
    config = real_share / "config" / "mid360_real.yaml"
    rviz_config = real_share / "rviz" / "online_mapping.rviz"

    lightning_prefix = Path(get_package_share_directory("lightning")).parent.parent
    slam_executable = lightning_prefix / "lib" / "lightning" / "run_slam_online"
    slam = ExecuteProcess(
        cmd=[str(slam_executable), f"--config={config}"],
        output="screen",
    )
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        name="lightning_real_rviz",
        arguments=["-d", str(rviz_config)],
        parameters=[{"use_sim_time": True}],
        condition=IfCondition(LaunchConfiguration("rviz")),
        output="screen",
    )

    return LaunchDescription([
        DeclareLaunchArgument("rviz", default_value="true"),
        slam,
        rviz,
    ])
