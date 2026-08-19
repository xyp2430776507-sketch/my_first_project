"""Start the existing omni chassis driver in a low-speed Nav2 test mode.

The original kepler_nav package and configuration are not modified.  This
launch file must never run at the same time as the original chassis launch.
"""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    chassis_share = Path(get_package_share_directory("omni_chassis_control"))
    chassis_config = str(chassis_share / "config" / "omni_chassis_control.yaml")

    chassis = Node(
        package="omni_chassis_control",
        executable="omni_chassis_control_node",
        name="omni_chassis_control_node",
        output="screen",
        emulate_tty=True,
        parameters=[
            chassis_config,
            {
                "cmd_vel_topic": "/xyp/nav_cmd_vel_unconnected",
                "max_linear_vel": 0.08,
                "max_angular_vel": 0.20,
                "cmd_timeout": 0.20,
            },
        ],
        remappings=[
            ("/odom", "/xyp/raw_odom"),
            ("/tf", "/xyp/raw_tf"),
        ],
    )

    odom_adapter = Node(
        package="xyp_mid360_navigation",
        executable="odom_handedness_adapter.py",
        name="xyp_odom_handedness_adapter",
        output="screen",
        parameters=[
            {
                "raw_odom_topic": "/xyp/raw_odom",
                "corrected_odom_topic": "/odom",
                "raw_tf_topic": "/xyp/raw_tf",
                "corrected_tf_topic": "/tf",
                "imu_topic": "/livox/imu",
                "imu_yaw_sign": 1.0,
                "gyro_deadband": 0.02,
            }
        ],
    )

    return LaunchDescription([chassis, odom_adapter])
