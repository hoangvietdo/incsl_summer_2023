// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class RobotController: public rclcpp::Node{
  
public:
  RobotController(): Node("feed_forward_circle_node")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",5);
    timer_ = this->create_wall_timer(0.05s, std::bind(&RobotController::feed_forward_controller, this));
  }

private:
  void feed_forward_controller()
  {
    auto msg = geometry_msgs::msg::Twist();
    x_d = -a * b * sin(b * t);
    y_d = a * b * cos(b * t);
    x_dd = -a * b * b * cos(b * t);
    y_dd = -a * b * b * sin(b * t);

  // keyboard using stop start
  //char c;
  //c = getch();


  //
  if (t >= 10.0){
      msg.linear.x = sqrt(pow(x_d, 2) + pow(y_d, 2));
      msg.angular.z = (y_dd * x_d - y_d * x_dd) / msg.linear.x;
      publisher_->publish(msg);
      t += 0.05;}

    else{
      msg.linear.x = 0.0;
      msg.angular.z = 0.0;
      publisher_->publish(msg);
      t += 0.05;}

  }
  float t = 0.0;
  float a = 5.0;
  float b = 0.7;
  float x_d, y_d, x_dd, y_dd;

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
 
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotController>());
  rclcpp::shutdown();
  return 0;
}
