#!/usr/bin/env python3
"""Plan and execute each leg of a short obstacle-loop validation route."""

import sys

import rclpy
from action_msgs.msg import GoalStatus
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import ComputePathToPose, FollowPath
from rclpy.action import ActionClient
from rclpy.node import Node


class PlanFollowWaypoints(Node):
    def __init__(self):
        super().__init__("xyp_plan_follow_waypoints")
        self.declare_parameter(
            "waypoints",
            [0.0, -1.0, 2.0, -1.0, 2.0, 1.0, 0.0, 1.0, 0.0, 0.0],
        )
        self.declare_parameter("frame_id", "odom")
        self.declare_parameter("planner_id", "GridBased")
        self.declare_parameter("controller_id", "FollowPath")
        self.declare_parameter("goal_checker_id", "general_goal_checker")
        self.declare_parameter("progress_checker_id", "progress_checker")

        values = list(self.get_parameter("waypoints").value)
        if len(values) < 2 or len(values) % 2:
            raise ValueError("waypoints must contain x,y pairs")
        self._waypoints = list(zip(values[0::2], values[1::2]))
        self._frame_id = self.get_parameter("frame_id").value
        self._planner_id = self.get_parameter("planner_id").value
        self._controller_id = self.get_parameter("controller_id").value
        self._goal_checker_id = self.get_parameter("goal_checker_id").value
        self._progress_checker_id = self.get_parameter("progress_checker_id").value

        self._planner = ActionClient(self, ComputePathToPose, "/compute_path_to_pose")
        self._controller = ActionClient(self, FollowPath, "/follow_path")

    def _wait(self, future):
        rclpy.spin_until_future_complete(self, future)
        return future.result()

    def run(self):
        self.get_logger().info("Waiting for Nav2 planner and controller...")
        if not self._planner.wait_for_server(timeout_sec=10.0):
            raise RuntimeError("/compute_path_to_pose is unavailable")
        if not self._controller.wait_for_server(timeout_sec=10.0):
            raise RuntimeError("/follow_path is unavailable")

        for index, (x, y) in enumerate(self._waypoints, start=1):
            target = PoseStamped()
            target.header.frame_id = self._frame_id
            target.header.stamp = self.get_clock().now().to_msg()
            target.pose.position.x = float(x)
            target.pose.position.y = float(y)
            target.pose.orientation.w = 1.0

            plan_goal = ComputePathToPose.Goal()
            plan_goal.goal = target
            plan_goal.planner_id = self._planner_id
            plan_goal.use_start = False

            self.get_logger().info(
                f"Leg {index}/{len(self._waypoints)}: planning to ({x:.2f}, {y:.2f})"
            )
            plan_handle = self._wait(self._planner.send_goal_async(plan_goal))
            if plan_handle is None or not plan_handle.accepted:
                raise RuntimeError(f"planner rejected leg {index}")
            plan_result = self._wait(plan_handle.get_result_async())
            if (
                plan_result.status != GoalStatus.STATUS_SUCCEEDED
                or not plan_result.result.path.poses
            ):
                raise RuntimeError(f"planning failed on leg {index}")

            follow_goal = FollowPath.Goal()
            follow_goal.path = plan_result.result.path
            follow_goal.controller_id = self._controller_id
            follow_goal.goal_checker_id = self._goal_checker_id
            follow_goal.progress_checker_id = self._progress_checker_id

            self.get_logger().info(
                f"Leg {index}: following {len(follow_goal.path.poses)} planned poses"
            )
            follow_handle = self._wait(self._controller.send_goal_async(follow_goal))
            if follow_handle is None or not follow_handle.accepted:
                raise RuntimeError(f"controller rejected leg {index}")
            follow_result = self._wait(follow_handle.get_result_async())
            if follow_result.status != GoalStatus.STATUS_SUCCEEDED:
                raise RuntimeError(f"control failed on leg {index}")
            self.get_logger().info(f"Leg {index} completed")

        self.get_logger().info("Obstacle loop completed successfully")


def main(args=None):
    rclpy.init(args=args)
    node = PlanFollowWaypoints()
    exit_code = 0
    try:
        node.run()
    except (KeyboardInterrupt, RuntimeError, ValueError) as error:
        node.get_logger().error(str(error))
        exit_code = 1
    finally:
        node.destroy_node()
        rclpy.shutdown()
    sys.exit(exit_code)


if __name__ == "__main__":
    main()
