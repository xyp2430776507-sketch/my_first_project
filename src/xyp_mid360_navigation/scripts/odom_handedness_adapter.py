#!/usr/bin/env python3
"""Convert the chassis' reflected Y/yaw odometry to ROS REP-103 coordinates."""

from copy import deepcopy
from math import cos, pi, sin

import rclpy
from nav_msgs.msg import Odometry
from rclpy.node import Node
from sensor_msgs.msg import Imu
from tf2_msgs.msg import TFMessage


# Signs for [x, y, z, rotation-x, rotation-y, rotation-z].
_COVARIANCE_SIGNS = (1.0, -1.0, 1.0, -1.0, 1.0, -1.0)


def _reflect_quaternion_y(quaternion):
    """Apply R_ros = diag(1,-1,1) R_raw diag(1,-1,1)."""
    quaternion.x = -quaternion.x
    quaternion.z = -quaternion.z


def _reflect_covariance(covariance):
    original = list(covariance)
    for row in range(6):
        for column in range(6):
            index = row * 6 + column
            covariance[index] = (
                original[index]
                * _COVARIANCE_SIGNS[row]
                * _COVARIANCE_SIGNS[column]
            )


def _set_planar_yaw(quaternion, yaw):
    quaternion.x = 0.0
    quaternion.y = 0.0
    quaternion.z = sin(yaw * 0.5)
    quaternion.w = cos(yaw * 0.5)


class OdomHandednessAdapter(Node):
    def __init__(self):
        super().__init__("xyp_odom_handedness_adapter")

        self.declare_parameter("raw_odom_topic", "/xyp/raw_odom")
        self.declare_parameter("corrected_odom_topic", "/odom")
        self.declare_parameter("raw_tf_topic", "/xyp/raw_tf")
        self.declare_parameter("corrected_tf_topic", "/tf")
        self.declare_parameter("imu_topic", "/livox/imu")
        self.declare_parameter("imu_yaw_sign", 1.0)
        self.declare_parameter("gyro_deadband", 0.02)

        raw_odom = self.get_parameter("raw_odom_topic").value
        corrected_odom = self.get_parameter("corrected_odom_topic").value
        raw_tf = self.get_parameter("raw_tf_topic").value
        corrected_tf = self.get_parameter("corrected_tf_topic").value
        imu_topic = self.get_parameter("imu_topic").value
        self._imu_yaw_sign = float(self.get_parameter("imu_yaw_sign").value)
        self._gyro_deadband = float(self.get_parameter("gyro_deadband").value)

        self._yaw = 0.0
        self._imu_angular_z = 0.0
        self._last_imu_stamp = None

        self._odom_publisher = self.create_publisher(Odometry, corrected_odom, 10)
        self._tf_publisher = self.create_publisher(TFMessage, corrected_tf, 100)
        self.create_subscription(Odometry, raw_odom, self._on_odom, 10)
        self.create_subscription(TFMessage, raw_tf, self._on_tf, 100)
        self.create_subscription(Imu, imu_topic, self._on_imu, 100)

        self.get_logger().info(
            f"Correcting chassis odometry: {raw_odom} -> {corrected_odom}, "
            f"{raw_tf} -> {corrected_tf}; yaw source: {imu_topic}"
        )

    def _on_imu(self, message):
        stamp = message.header.stamp.sec + message.header.stamp.nanosec * 1e-9
        angular_z = self._imu_yaw_sign * float(message.angular_velocity.z)
        if abs(angular_z) < self._gyro_deadband:
            angular_z = 0.0

        if self._last_imu_stamp is not None:
            delta_time = stamp - self._last_imu_stamp
            if 0.0 < delta_time <= 0.1:
                self._yaw += angular_z * delta_time
                self._yaw = (self._yaw + pi) % (2.0 * pi) - pi

        self._last_imu_stamp = stamp
        self._imu_angular_z = angular_z

    def _on_odom(self, raw_message):
        message = deepcopy(raw_message)
        message.pose.pose.position.y = -message.pose.pose.position.y
        _set_planar_yaw(message.pose.pose.orientation, self._yaw)

        message.twist.twist.linear.y = -message.twist.twist.linear.y
        message.twist.twist.angular.x = 0.0
        message.twist.twist.angular.y = 0.0
        message.twist.twist.angular.z = self._imu_angular_z

        _reflect_covariance(message.pose.covariance)
        _reflect_covariance(message.twist.covariance)
        self._odom_publisher.publish(message)

    def _on_tf(self, raw_message):
        message = deepcopy(raw_message)
        for transform in message.transforms:
            if (
                transform.header.frame_id.lstrip("/") == "odom"
                and transform.child_frame_id.lstrip("/") == "base_link"
            ):
                transform.transform.translation.y = -transform.transform.translation.y
                _set_planar_yaw(transform.transform.rotation, self._yaw)
        self._tf_publisher.publish(message)


def main(args=None):
    rclpy.init(args=args)
    node = OdomHandednessAdapter()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
