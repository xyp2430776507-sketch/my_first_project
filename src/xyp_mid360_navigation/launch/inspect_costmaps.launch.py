"""Start isolated Nav2 costmaps without connecting velocity to the chassis."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    share = Path(get_package_share_directory("xyp_mid360_navigation"))
    params = str(share / "config" / "nav2_odom_mid360.yaml")

    controller = Node(
        package="nav2_controller",
        executable="controller_server",
        name="controller_server",
        output="screen",
        parameters=[params],
        remappings=[
            ("nav_cmd_vel", "/xyp/nav_cmd_vel_unconnected"),
            ("cmd_vel", "/xyp/nav_cmd_vel_unconnected"),
        ],
    )

    planner = Node(
        package="nav2_planner",
        executable="planner_server",
        name="planner_server",
        output="screen",
        parameters=[params],
    )

    lifecycle = Node(
        package="nav2_lifecycle_manager",
        executable="lifecycle_manager",
        name="lifecycle_manager_xyp_costmaps",
        output="screen",
        parameters=[
            {"use_sim_time": False},
            {"autostart": True},
            {"node_names": ["controller_server", "planner_server"]},
        ],
    )

    return LaunchDescription([controller, planner, lifecycle])
