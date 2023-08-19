# import rclpy.node import Node
# import rclpy

# # ROS2 keybard input function
# from turtle_control.msg import Turtle

# # ROS2 keybard input function
# import sys, select, termios, tty

# # ROS2 keybard input function
# msg = """
# Control Your Turtle!
# ---------------------------
# Moving around:

#         w       
#     a    s    d

# w/s : increase/decrease linear velocity
# a/d : increase/decrease angular velocity
# space key, s : force stop

# CTRL-C to quit
# """

# # ROS2 keybard input function
# moveBindings = {
#         'w':(1,0),
#         'a':(0,1),
#         'd':(0,-1),
#         's':(-1,0),
#         ' ':(0,0)
#     }

# # ROS2 keybard input function
# speedBindings={
#         'q':(1.1,1.1),
#         'z':(.9,.9),
#         ' ':(0,0)
#     }

# # ROS2 keybard input function
# def getKey():
#     tty.setraw(sys.stdin.fileno())
#     select.select([sys.stdin], [], [], 0)
#     key = sys.stdin.read(1)
    
#     termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
#     return key

# # ROS2 keybard input function
# def vels(speed,turn):
#     return "currently:\tspeed %s\tturn %s " % (speed,turn)

# # ROS2 keybard input function
# if __name__=="__main__":
#     settings = termios.tcgetattr(sys.stdin)
    
#     rclpy.init(args=args)
#     node = rclpy.create_node('turtle_teleop')
#     pub = node.create_publisher(Turtle, 'turtle', 10)
    
#     speed = 0.5
#     turn = 1.0
#     x = 0.0
#     th = 0.0
#     status = 0.0
    
#     try:
#         print(msg)
#         print(vels(speed,turn))
#         while(1):
#             key = getKey()
#             if key in moveBindings.keys():
#                 x = moveBindings[key][0]
#                 th = moveBindings[key][1]
#             elif key in speedBindings.keys():
#                 speed = speed * speedBindings[key][0]
#                 turn = turn * speedBindings[key][1]
    
#                 print(vels(speed,turn))
#                 if (status == 14):
#                     print(msg)
#                 status = (status + 1) % 15
#             else:
#                 x = 0.0
#                 th = 0.0
#                 if (key == '\x03'):
#                     break
    
#             twist = Twist()
#             twist.linear.x = x*speed; twist.linear.y = 0; twist.linear.z = 0
#             twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = th*turn
#             pub.publish(twist)
    
#     except Exception as e:
#         print(e)
    
#     finally:
#         twist = Twist()
#         twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
#         twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0
#         pub.publish(twist)
    
#         termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

