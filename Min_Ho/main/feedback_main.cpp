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
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/empty.hpp"
#include "turtlesim/srv/teleport_absolute.hpp"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;
using namespace std;
using std::placeholders::_1;

double t(0.0);

float feed_x(0.0);
float feed_y(0.0);
float feed_th(0.0);

double init_x(5.54445);
double init_y(5.54445);
double init_th(0.0);

double x(0.0);
double y(0.0);
double th(0.0);
double xdot(0.0);
double ydot(0.0);
double xddot(0.0);
double yddot(0.0);

double k1(10.0);
double k2(10.0);
double k3(10.0);

double a(5.0);
double b(0.5);
double dt(0.001);

const char* msg = R"(
-------------------------------------------------------------------
Algorithm 1 : Feedback Kinematic Controller with 8-shape Trajectory 

1. Open turtlesim simulator.
2. if Press 's'
   Start "Eight-shape Trajectory" tracking
3. else if Press 'Space'
   Stop the turtle at the current position
-------------------------------------------------------------------

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

        feedbackController() : Node("feedback_controller")
        {
            printf("%s", msg);
            // define msg
            geometry_msgs::msg::Twist twist;

            // define publisher 
            pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
            sub_ = this->create_subscription<turtlesim::msg::Pose>
                ("/turtle1/pose", 10, std::bind(&feedbackController::feedback_callback, this, _1));
 
            // define service (Optional)
            rst_ = this->create_client<std_srvs::srv::Empty>("/clear");
            setp_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
            auto pos = std::make_shared<turtlesim::srv::TeleportAbsolute::Request>();

            while(!setp_ -> wait_for_service(1s)){
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
            }

            // Initialize Position to (5.54, 5.54)
            pos->x = init_x;
            pos->y = init_y;
            pos->theta = init_th;

            x = pos->x;
            y = pos->y;
            th = pos->theta;

            setp_->async_send_request(pos);

            while(!rst_ -> wait_for_service(1s)){
                RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
            }

            auto req = std::make_shared<std_srvs::srv::Empty::Request>();
            rst_->async_send_request(req);

            // define timer
            timer_ = this->create_wall_timer(
                1ms, std::bind(&feedbackController::timer_callback, this));
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

                    x = init_x + a*sin(b*t);
                    y = init_y + a*sin(b*t)*cos(b*t);
                    th = atan2(ydot, xdot);

                    double e1 = cos(th)*(x - feed_x) + sin(th)*(y - feed_y);
                    double e2 = -sin(th)*(x - feed_x) + cos(th)*(y - feed_y);
                    double e3 = th - feed_th;

                    xddot = -a * pow(b, 2.0) * sin(b * t);
                    yddot = -4 * a * pow(b, 2.0) * sin(b * t) * cos(b * t);
                    double ang_z = (yddot * xdot - ydot * xddot) / (pow(xdot, 2.0) + pow(ydot, 2.0));

                    command.linear.x = lin_x * cos(e3) + k1 * e1;
                    command.angular.z = ang_z + k2 * lin_x * e2 + k3 * lin_x * sin(e3);

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

            void feedback_callback(const turtlesim::msg::Pose::SharedPtr data) const
            {
                feed_x = data->x;
                feed_y = data->y;
                feed_th = data->theta;
            }

            rclcpp::TimerBase::SharedPtr timer_;
            rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
            rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub_;
            rclcpp::Client<std_srvs::srv::Empty>::SharedPtr rst_;
            rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr setp_;

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
