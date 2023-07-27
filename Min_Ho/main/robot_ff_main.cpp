#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <map>
#include <functional>
#include <string>
#include <chrono>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;
using namespace std;
using std::placeholders::_1;

double t(0.0);

double x(0.0);
double y(0.0);
double th(0.0);
double xdot(0.0);
double ydot(0.0);
double xddot(0.0);
double yddot(0.0);

double k1(1.0);
double k2(1.0);
double k3(1.0);

double a(4.0);
double b(0.7);
double dt(0.02);

const char* msg = R"(
----------------------------------------------------------------
Algorithm : Feedback Kinematic Controller with real-world robot 

1. Setting the robot.
2. if Press 's'
   Start "Eight-shape Trajectory" tracking 
   or Press 'c' to start "Circle Trajectory" tracking
3. else if Press 'Space'
   Stop the turtle at the current position
----------------------------------------------------------------

)";

char key = ' ';

// For non-blocking keyboard inputs
int getch(void)
{
    int ch;
    struct termios oldt;
    struct termios newt;

    // Store old settings, and copy to new settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Make required changes and apply the settings
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_iflag |= IGNBRK;
    newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
    newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &newt);

    // Get the current character
    ch = getchar();

    // Reapply old settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

class GetKeyNode : public rclcpp::Node{
    public:
        GetKeyNode() : Node("get_Key")
        {
            timer_get = this->create_wall_timer(
                200ms, std::bind(&GetKeyNode::timer_callback_get, this));
        }

    private:
        void timer_callback_get()
        {
            key = getch();
        }
        rclcpp::TimerBase::SharedPtr timer_get;
};

class feedbackController : public rclcpp::Node{
    public:

        feedbackController() : Node("robot_ff_controller")
        {
            printf("%s", msg);
            // define msg
            geometry_msgs::msg::Twist twist;

            // define publisher 
            pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel",5);
        
            // define timer
            timer_ = this->create_wall_timer(
                20ms, std::bind(&feedbackController::timer_callback, this));
        }

        private:
        /* For Timer */
            void timer_callback()
            {
                if(key == 's')
                {
                    auto command = geometry_msgs::msg::Twist();
                    
                    xdot = a * b * cos(b * t);
                    ydot = a * b * cos(b * t) * cos(b * t) - a * b * sin(b*t) * sin(b*t);
                    double lin_x = sqrt(pow(xdot, 2.0) + pow(ydot, 2.0));

                    x = a*sin(b*t);
                    y = a*sin(b*t)*cos(b*t);
                    th = atan2(ydot, xdot);

                    xddot = -a * pow(b, 2.0) * sin(b * t);
                    yddot = -4 * a * pow(b, 2.0) * sin(b * t) * cos(b * t);
                    double ang_z = (yddot * xdot - ydot * xddot) / (pow(xdot, 2.0) + pow(ydot, 2.0));

                    command.linear.x = lin_x;
                    command.angular.z = ang_z;

                    pub_->publish(command);
                    t = t + dt;

                    // if (t > (2 * M_PI / b))
                    // {
                    //     t = 0.0;
                    // }
                }
                else if (key == 'c') // circle
                {
                    auto command = geometry_msgs::msg::Twist();

                    xdot = -a * b * sin(b * t);
                    ydot = a * b * cos(b * t);
                    double lin_x = sqrt(pow(xdot, 2.0) + pow(ydot, 2.0));

                    x = a*cos(b*t);
                    y = a*sin(b*t);
                    th = atan2(ydot, xdot);

                    xddot = -a * pow(b, 2.0) * cos(b * t);
                    yddot = -a * pow(b, 2.0) * sin(b * t);
                    double ang_z = (yddot * xdot - ydot * xddot) / (pow(xdot, 2.0) + pow(ydot, 2.0));

                    command.linear.x = lin_x;
                    command.angular.z = ang_z;

                    pub_->publish(command);
                    t = t + dt;

                    // if (t > (2 * M_PI / b))
                    // {
                    //     t = 0.0;
                    // }
                }
                else if(key == '\x03')
                {
                    auto stop = geometry_msgs::msg::Twist();

                    stop.linear.x = 0.0;
                    stop.angular.z =  0.0;
                    pub_->publish(stop);

                    timer_->cancel();
                    rclcpp::shutdown();
                }
                else if(key == ' ')
                {
                    auto stop = geometry_msgs::msg::Twist();

                    stop.linear.x = 0.0;
                    stop.angular.z =  0.0;
                    pub_->publish(stop);
                }
            }
            rclcpp::TimerBase::SharedPtr timer_;
            rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;   
};

int main(int argc, char** argv){
    
    // node init
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor;

    auto node = std::make_shared<feedbackController>();
    auto get_k = std::make_shared<GetKeyNode>();

    executor.add_node(node);
    executor.add_node(get_k);

    executor.spin();

    // rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}

