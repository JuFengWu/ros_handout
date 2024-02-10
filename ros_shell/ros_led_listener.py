import rclpy
from rclpy.node import Node

from std_msgs.msg import Bool
import lgpio

class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            Bool,
            'topic',
            self.listener_callback,
            10)
        self.h = lgpio.gpiochip_open(0)
        self.LED = 5
        self.bee = 16
        lgpio.gpio_claim_output(self.h, self.LED)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('listen')
        light = msg.data
        if light:
            lgpio.gpio_write(self.h, self.LED, 1)
        else:
            lgpio.gpio_write(self.h, self.LED, 0)


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()