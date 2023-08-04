#!/usr/bin/env python3

import rclpy
import math

from rclpy.node import Node
from geometry_msgs.msg import Twist
from std_srvs.srv import Empty


class RobotController(Node):
    def __init__(self):
        super().__init__("feed_back_circle")

        self.t = 0.0
        self.reset = 0.0

        self.cmd_vel_pub_ = self.create_publisher(Twist, "/turtle1/cmd_vel", 5);
        self.reset_client_ = self.create_client(Empty, "/reset")
        self.clear_client_ = self.create_client(Empty, "/clear")

        self.request_ = Empty.Request()
        
        self.timer_ = self.create_timer(0.01, self.send_command)
        self.get_logger().info("Controlling the robot to draw a circle using a feedforward controller")
    
    def send_command(self):
    	a=4.0
    	b=0.7
    	msg = Twist()
    	x_d=-a*b*math.sin(b*self.t)
    	y_d=a*b*math.cos(b*self.t)
    	x_d2=-a*b*b*math.cos(b*self.t)
    	y_d2=-a*b*b*math.sin(b*self.t)
    	
    	#x_d = a * b * math.cos(b*self.t)
    	#y_d = a * b * (pow(math.cos(b*self.t), 2.0) - pow(math.sin(b*self.t), 2.0))
    	#x_d2 = -a * b * b * math.sin(b*self.t)
    	#y_d2 = -4.0 * a * b * b * (math.cos(b*self.t) * math.sin(b*self.t))
    	
    	# v_r
    	msg.linear.x = math.sqrt(x_d*x_d+y_d*y_d)
    	
    	# w_r
    	msg.angular.z = (-x_d2*y_d+y_d2*x_d)/(x_d*x_d+y_d*y_d)
    	self.cmd_vel_pub_.publish(msg)
    	self.t = self.t + 0.01
    	
def main():
    rclpy.init()
    robot_controller = RobotController()
    rclpy.spin(robot_controller)
    robot_controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
