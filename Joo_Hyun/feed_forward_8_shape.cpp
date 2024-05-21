#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class Control : public rclcpp::Node{
    public:
      Control(): Node("feed_forward_8_shape_node"){
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 5);//publish
        timer_ = this->create_wall_timer(0.05s, std::bind(&Control::feed_forward_controller, this));//timer
    }//public
    private:
      void feed_forward_controller(){
        auto msg = geometry_msgs::msg::Twist();
        x_d = a * b * cos(b * t);
        y_d = a * b * (pow(cos(b * t), 2.0) - pow(sin(b * t), 2.0));
        x_dd = -a * b * b * sin(b * t);
        y_dd = -4.0 * a * b * b * sin(b * t) * cos(b * t);
        //Trajectory

        if(t >= 10){
            msg.linear.x = sqrt(pow(x_d, 2) + pow(y_d, 2));//linear_velocity
            msg.angular.z = (y_dd * x_d - y_d * x_dd) / pow(msg.linear.x, 2.0);//angular_velocity
            publisher_->publish(msg);//publish
            t += 0.05;
        }

        else{
            t += 0.05;
        }//else
      }//feed_forward_controller
      float t = 0.0;
      float a = 2.0;
      float b = 0.025;
      float x_d, y_d, x_dd, y_dd;
      rclcpp::TimerBase::SharedPtr timer_;//timer
      rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;//publish
};//class(pubilc + private)

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Control>());
    rclcpp::shutdown();
}