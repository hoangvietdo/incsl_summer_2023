cmake_minimum_required(VERSION 3.5)
project(summer_camp)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(circle_trajectory src/circle_main.cpp)
add_executable(eight_trajectory src/eight_main.cpp)
add_executable(feedback_controller src/feedback_main.cpp)
add_executable(robot_controller src/robot_main.cpp)

ament_target_dependencies(circle_trajectory rclcpp geometry_msgs std_srvs std_msgs turtlesim)
ament_target_dependencies(eight_trajectory rclcpp geometry_msgs std_srvs std_msgs turtlesim)
ament_target_dependencies(feedback_controller rclcpp geometry_msgs std_srvs std_msgs turtlesim)
ament_target_dependencies(robot_controller rclcpp geometry_msgs nav_msgs std_msgs)

install(TARGETS
  circle_trajectory
  eight_trajectory
  feedback_controller
  robot_controller
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
