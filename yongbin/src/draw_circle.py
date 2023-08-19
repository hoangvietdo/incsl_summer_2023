import rclpy
from rclpy.node import Node
from math import sin, cos, pow


from geometry_msgs.msg import Twist

class DrawCircleNode(Node):

    def __init__(self):
        super().__init__('draw_circle_node')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.timer_ = self.create_timer(0.1, self.timer_callback)
        self.a = 1
        self.b = 1
        self.t = 0

    def timer_callback(self):
        twist_msg = Twist()

        twist_msg.linear.x = -self.a * self.b * sin(self.b * self.t)
        twist_msg.linear.y = -self.a * self.b * cos(self.b * self.t)

        twist_msg.angular.x = -self.a * pow(self.b, 2) * cos(self.b * self.t)
        twist_msg.angular.y = -self.a * pow(self.b, 2) * sin(self.b * self.t)


        self.publisher_.publish(twist_msg)
        self.t += 0.1

def main(args=None):
    rclpy.init(args=args)
    node = DrawCircleNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
        