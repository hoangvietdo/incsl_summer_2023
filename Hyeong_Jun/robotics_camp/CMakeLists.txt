cmake_minimum_required(VERSION 3.5)
project(robotics_camp)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(geometry_msgs REQUIRED)


# what is add_executable
add_executable(feed_forward_circle_node src/feed_forward_circle.cpp)
add_executable(feed_forward_eight_node src/feed_forward_eight.cpp)
# what is ament_target_dependencies
ament_target_dependencies(feed_forward_circle_node rclcpp geometry_msgs turtlesim)
ament_target_dependencies(feed_forward_eight_node rclcpp geometry_msgs turtlesim)

install(TARGETS
    feed_forward_circle_node
    feed_forward_eight_node
    DESTINATION lib/${PROJECT_NAME})

ament_package()
