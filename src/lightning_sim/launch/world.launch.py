"""Launch the baseline Lightning-LM simulation world in Gazebo Fortress."""

from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node


def generate_launch_description():
    ros_gz_share = Path(get_package_share_directory("ros_gz_sim"))
    sim_share = Path(get_package_share_directory("lightning_sim"))
    world = sim_share / "worlds" / "baseline_world.sdf"
    headless = LaunchConfiguration("headless")
    gz_args = PythonExpression([
        "'-r -s --headless-rendering ",
        str(world),
        "' if '",
        headless,
        "' == 'true' else '-r ",
        str(world),
        "'",
    ])

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(ros_gz_share / "launch" / "gz_sim.launch.py")),
        launch_arguments={
            "gz_args": gz_args,
            "gz_version": "6",
            "on_exit_shutdown": "true",
        }.items(),
    )

    bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        name="lightning_sim_bridge",
        arguments=[
            "/model/lightning_cart/cmd_vel@geometry_msgs/msg/Twist]ignition.msgs.Twist",
            "/clock@rosgraph_msgs/msg/Clock[ignition.msgs.Clock",
            "/imu@sensor_msgs/msg/Imu[ignition.msgs.IMU",
            "/livox/lidar/points@sensor_msgs/msg/PointCloud2[ignition.msgs.PointCloudPacked",
        ],
        remappings=[
            ("/model/lightning_cart/cmd_vel", "/cmd_vel"),
            ("/livox/lidar/points", "/livox/lidar"),
        ],
        output="screen",
    )

    lidar_static_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="livox_static_tf",
        arguments=[
            "--x", "0", "--y", "0", "--z", "0.28",
            "--roll", "0", "--pitch", "0", "--yaw", "0",
            "--frame-id", "lightning_base_link", "--child-frame-id", "livox_frame",
        ],
        output="screen",
    )

    cloud_adapter = Node(
        package="lightning_sim",
        executable="sim_cloud_adapter",
        name="sim_cloud_adapter",
        output="screen",
    )

    isolated_partition = SetEnvironmentVariable(
        "IGN_PARTITION", "lightning_sim_fortress"
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument("headless", default_value="false"),
            isolated_partition,
            gazebo,
            bridge,
            lidar_static_tf,
            cloud_adapter,
        ]
    )
