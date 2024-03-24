import time

import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node

from self_def_msg_srv.action import MyAction


class MyActionServer(Node):

    def __init__(self):
        super().__init__('my_action_server')
        self._action_server = ActionServer(
            self,
            MyAction,
            'my_action',
            self.execute_callback)

    def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')
        
        print(goal_handle.request.start_selection)
        feedback = MyAction.Feedback()
        print(feedback.value)
        result = MyAction.Result()
        

        for i in range(10):
            feedback.value=i+0.1;
            print("feedback value is "+str(feedback.value))
            if (goal_handle._cancel_requested):
                result.success_or_not = False;
                goal_handle.canceled(result);
                print("Goal canceled");
                return;
      
            time.sleep(1)

        goal_handle.succeed()

        
        result.success_or_not = True
        return result


def main(args=None):
    rclpy.init(args=args)

    my_action_server = MyActionServer()

    rclpy.spin(my_action_server)


if __name__ == '__main__':
    main()
