#include <chrono>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class Robotcontroller : public rclcpp::Node{

    public:
        Robotcontroller()
        : Node("ff_8"){
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 5);
            timer_ = this->create_wall_timer(
                0.05s, std::bind(&Robotcontroller::ff_8, this));
        }

    private:
        float t = 0.0;
        float a = 3.0;
        float b = 0.5;
        float x_d, x_dd, y_d, y_dd;
        
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    void ff_8(){
        auto msg = geometry_msgs::msg::Twist();
        x_d = a*b*cos(b*t);
        x_dd = -a*b*b*sin(b*t);
        y_d = a*b*(cos(b*t)*cos(b*t)-sin(b*t)*sin(b*t));
        y_dd = -4*a*b*b*cos(b*t)*sin(b*t);

        if (t>= 1.0)
        {
            msg.linear.x = sqrt(pow(x_d, 2.0) + pow(y_d,2.0));
            msg.angular.z = (y_dd*x_d - y_d*x_dd)/pow(msg.linear.x, 2.0);
            publisher_->publish(msg);
            t = t+0.05;
        }
        else
        {
            msg.linear.x = 0.0;
            msg.linear.z = 0.0;
            publisher_->publish(msg);
            t = t+0.05;
        }
    }
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Robotcontroller>());
    rclcpp::shutdown();
    return 0;
}
