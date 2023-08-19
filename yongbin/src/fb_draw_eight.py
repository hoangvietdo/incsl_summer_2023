import rclpy
from rclpy.node import Node
from math import sin, cos, pow, sqrt, atan2

from geometry_msgs.msg import Twist
from turtlesim.msg import Pose

feed_x = 0.0
feed_y = 0.0
feed_th = 0.0

init_x = 5.54445
init_y = 5.54445
init_th = 0.0


x = 0.0
y = 0.0
th = 0.0
v = 0.0
w = 0.0
xdot = 0.0
ydot = 0.0

k1 = 10.0
k2 = 10.0
k3 = 10.0

a = 5.0
b = 0.5
dt = 0.01

xdot = 0.0
xddot = 0.0
ydot = 0.0
yddot = 0.0

start_msg = '''----------------------------------'''

class Fb_DrawEight(Node):

    def __init__(self):
        super().__init__('fb_draw_eight')
        self.pub_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.sub_ = self.create_subscription(Pose, "turtle1/pose", self.fn_callback, 5)
        self.t = 0

    def fn_callback(self, pose_msg):
        twist_msg = Twist()

        # turtlesim pose data
        x_data = pose_msg.x
        y_data = pose_msg.y
        th_data = pose_msg.theta
        v_data = pose_msg.linear_velocity
        w_data = pose_msg.angular_velocity

        xdot = a * b * cos(b * self.t)
        ydot = a * b * pow(cos(b * self.t), 2) - a * b * sin(b * self.t)

        v_r = sqrt(pow(xdot, 2) + pow(ydot, 2))
        w_r = (xdot * yddot - xddot * ydot) / (pow(xdot, 2) + pow(ydot, 2))

        x = init_x + a * sin(b * self.t)
        y = init_y + a * sin(b * self.t) * cos(b * self.t)
        th = atan2(ydot, xdot)


        e1 = cos(th_data) * (x - x_data) + sin(th_data) * (y - y_data)
        e2 = -sin(th_data) * (x - x_data) + cos(th_data) * (y - y_data)
        e3 = th - th_data

        v_c = v_r * cos(e3) + k1 * e1
        w_c = w_r + k2 * v_r * e2 + k3 * sin(e3)

        twist_msg.linear.x = v_c
        twist_msg.angular.z = w_c

        self.pub_.publish(twist_msg)
        self.t += dt
    
    def feedback(self):
        pass

    def forward(self):
        pass

def main(args=None):
    rclpy.init(args=args)
    node = Fb_DrawEight()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
        