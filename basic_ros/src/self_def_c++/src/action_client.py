import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node

from self_def_msg_srv.action import MyAction


class MyActionClient(Node):

    def __init__(self):
        super().__init__('my_action_client')
        self._action_client = ActionClient(self, MyAction, 'my_action')

    def send_goal(self):
        goal_msg = MyAction.Goal()
        goal_msg.start_selection = 1

        self._action_client.wait_for_server()

        self._send_goal_future = self._action_client.send_goal_async(goal_msg, feedback_callback=self.feedback_callback)

        self._send_goal_future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')

        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info('Result is '+ str(result.success_or_not))
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        self._action_client.cancel_goal_async()# cancel goal
        feedback = feedback_msg.feedback
        self.get_logger().info('Received feedback: '+ str(feedback.value))


def main(args=None):
    rclpy.init(args=args)

    action_client = MyActionClient()

    action_client.send_goal()

    rclpy.spin(action_client)


if __name__ == '__main__':
    main()
