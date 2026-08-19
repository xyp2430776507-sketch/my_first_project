"""Start Gazebo, Lightning-LM online SLAM, and RViz."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    ExecuteProcess,
)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    sim_share = Path(get_package_share_directory("lightning_sim"))
    config = sim_share / "config" / "lightning_sim.yaml"
    rviz_config = sim_share / "rviz" / "online_mapping.rviz"

    world = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(sim_share / "launch" / "world.launch.py")
        )
    )

    slam = ExecuteProcess(
        cmd=[
            "ros2",
            "run",
            "lightning",
            "run_slam_online",
            f"--config={config}",
        ],
        output="screen",
    )

    rviz = Node(
        package="rviz2",
        executable="rviz2",
        name="lightning_rviz",
        arguments=["-d", str(rviz_config)],
        parameters=[{"use_sim_time": True}],
        condition=IfCondition(LaunchConfiguration("rviz")),
        output="screen",
    )

    return LaunchDescription([
        DeclareLaunchArgument("rviz", default_value="true"),
        world,
        slam,
        rviz,
    ])