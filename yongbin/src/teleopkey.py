# from rclpy.node import Node
# import rclpy

# import sys, select, termios, tty

# class TeleopKey(Node):
#     def __init__(self):
#         super().__init__('teleop_key')
#         self.publishers_ = self.create_publisher()

# def getKey():
#     tty.setraw(sys.stdin.fileno())
#     select.select([sys.stdin], [], [], 0)
#     key = sys.stdin.read(1)

#     termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
#     return key

# def printKdy():
#     self.get_logger()
#     self.get_logger().info('Publishing: "%s"' % msg.data)

# if __name__ == '__main__':
#     settings = termios.tcgetattr(sys.stdin)

#     rclpy.init(args=None)
    
