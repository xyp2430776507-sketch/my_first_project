#!/usr/bin/env python3
"""Bridge Lightning localization TF into the standard map->odom chain."""

import math

import rclpy
from geometry_msgs.msg import TransformStamped
from rclpy.node import Node
from tf2_msgs.msg import TFMessage
from tf2_ros import TransformBroadcaster


def _quat_conjugate(q):
    return (-q[0], -q[1], -q[2], q[3])


def _quat_multiply(a, b):
    ax, ay, az, aw = a
    bx, by, bz, bw = b
    return (
        aw * bx + ax * bw + ay * bz - az * by,
        aw * by - ax * bz + ay * bw + az * bx,
        aw * bz + ax * by - ay * bx + az * bw,
        aw * bw - ax * bx - ay * by - az * bz,
    )


def _quat_normalize(q):
    norm = math.sqrt(sum(v * v for v in q))
    if norm <= 0.0:
        return (0.0, 0.0, 0.0, 1.0)
    return tuple(v / norm for v in q)


def _rotate_vector(q, v):
    rotated = _quat_multiply(_quat_multiply(q, (v[0], v[1], v[2], 0.0)), _quat_conjugate(q))
    return rotated[:3]


def _transform_to_tuple(transform):
    t = transform.translation
    r = transform.rotation
    return (t.x, t.y, t.z), _quat_normalize((r.x, r.y, r.z, r.w))


def _compose(a, b):
    at, aq = a
    bt, bq = b
    rb = _rotate_vector(aq, bt)
    return (
        (at[0] + rb[0], at[1] + rb[1], at[2] + rb[2]),
        _quat_normalize(_quat_multiply(aq, bq)),
    )


def _inverse(transform):
    t, q = transform
    qi = _quat_conjugate(q)
    ti = _rotate_vector(qi, (-t[0], -t[1], -t[2]))
    return ti, _quat_normalize(qi)


def _stamp_to_sec(stamp):
    return float(stamp.sec) + float(stamp.nanosec) * 1e-9


class LightningMapToOdomTf(Node):
    def __init__(self):
        super().__init__("lightning_map_to_odom_tf")

        self.declare_parameter("lightning_tf_topic", "/lightning_tf")
        self.declare_parameter("odom_tf_topic", "/tf")
        self.declare_parameter("lightning_parent_frame", "map")
        self.declare_parameter("lightning_child_frame", "base_link")
        self.declare_parameter("output_parent_frame", "lightning_map")
        self.declare_parameter("odom_frame", "odom")
        self.declare_parameter("base_frame", "base_link")
        self.declare_parameter("max_time_delta_sec", 0.1)

        lightning_topic = self.get_parameter("lightning_tf_topic").value
        odom_topic = self.get_parameter("odom_tf_topic").value
        self._lightning_parent = self.get_parameter("lightning_parent_frame").value
        self._lightning_child = self.get_parameter("lightning_child_frame").value
        self._output_parent = self.get_parameter("output_parent_frame").value
        self._odom_frame = self.get_parameter("odom_frame").value
        self._base_frame = self.get_parameter("base_frame").value
        self._max_time_delta = float(self.get_parameter("max_time_delta_sec").value)

        self._latest_odom_base = None
        self._tf_broadcaster = TransformBroadcaster(self)
        self.create_subscription(TFMessage, lightning_topic, self._on_lightning_tf, 100)
        self.create_subscription(TFMessage, odom_topic, self._on_odom_tf, 100)

        self.get_logger().info(
            f"Bridging {self._lightning_parent}->{self._lightning_child} from {lightning_topic} "
            f"with {self._odom_frame}->{self._base_frame} from {odom_topic} "
            f"to {self._output_parent}->{self._odom_frame}"
        )

    def _on_odom_tf(self, message):
        for transform in message.transforms:
            parent = transform.header.frame_id.lstrip("/")
            child = transform.child_frame_id.lstrip("/")
            if parent == self._odom_frame and child == self._base_frame:
                self._latest_odom_base = transform

    def _on_lightning_tf(self, message):
        for transform in message.transforms:
            if not self._is_lightning_pose(transform):
                continue
            self._publish_map_to_odom(transform)

    def _is_lightning_pose(self, transform):
        parent = transform.header.frame_id.lstrip("/")
        child = transform.child_frame_id.lstrip("/")
        return parent == self._lightning_parent and child == self._lightning_child

    def _publish_map_to_odom(self, lightning_map_base):
        if self._latest_odom_base is None:
            self.get_logger().warn(
                f"Waiting for {self._odom_frame}->{self._base_frame}",
                throttle_duration_sec=2.0,
            )
            return

        stamp = lightning_map_base.header.stamp
        delta = abs(_stamp_to_sec(stamp) - _stamp_to_sec(self._latest_odom_base.header.stamp))
        if delta > self._max_time_delta:
            self.get_logger().warn(
                f"TF time delta too large: {delta:.3f}s",
                throttle_duration_sec=2.0,
            )
            return

        map_base = _transform_to_tuple(lightning_map_base.transform)
        odom_base_tuple = _transform_to_tuple(self._latest_odom_base.transform)
        map_odom = _compose(map_base, _inverse(odom_base_tuple))

        output = TransformStamped()
        output.header.stamp = stamp
        output.header.frame_id = self._output_parent
        output.child_frame_id = self._odom_frame
        output.transform.translation.x = map_odom[0][0]
        output.transform.translation.y = map_odom[0][1]
        output.transform.translation.z = map_odom[0][2]
        output.transform.rotation.x = map_odom[1][0]
        output.transform.rotation.y = map_odom[1][1]
        output.transform.rotation.z = map_odom[1][2]
        output.transform.rotation.w = map_odom[1][3]
        self._tf_broadcaster.sendTransform(output)


def main(args=None):
    rclpy.init(args=args)
    node = LightningMapToOdomTf()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
