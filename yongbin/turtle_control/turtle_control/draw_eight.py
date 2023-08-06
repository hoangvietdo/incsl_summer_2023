import rclpy
from rclpy.node import Node
from math import sin, cos, pow
import time

from geometry_msgs.msg import Twist

class DrawEightNode(Node):
    def __init__(self):
        super().__init__('draw_eight_node')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.timer_ = self.create_timer(0.1, self.move_callback)
        self.a = 1
        self.b = 1
        self.t = 0
        # self.linear_x = self.a * self.b * sin(self.b * self.timer_)
        # self.linear_y = self.a * self.b * self.b * cos(self.b * self.timer_)
        # self.angular_x = self.a * self.b * (pow(cos(self.b * self.timer_)) - pow(sin(self.b * self.timer_)))
        # self.angular_y = -4 * self.a * self.b * sin(self.b * self.timer_) * cos(self.b * self.timer_)


    def move_callback(self):
        twist_msg = Twist()
        self.t = time.time()
        twist_msg.linear.x = self.a * self.b * self.b * cos(self.b * self.t)
        twist_msg.linear.y = self.a * self.b * (pow(cos(self.b * self.t), 2) - pow(sin(self.b * self.t), 2))
        twist_msg.angular.x = -self.a * self.b * sin(self.b * self.t) 
        twist_msg.angular.y = -4 * self.a * self.b * sin(self.b * self.t) * cos(self.b * self.t)


        # self.get_logger().info(self.t)
        self.publisher_.publish(twist_msg)
        self.t += 0.1

def main(args=None):
    rclpy.init(args=args)
    node = DrawEightNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()