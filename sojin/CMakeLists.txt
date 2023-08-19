cmake_minimum_required(VERSION 3.5)
project(sj_proj)


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
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(sj_controller src/ff_circle.cpp)
add_executable(sj_controller_8 src/ff_8.cpp)
ament_target_dependencies(sj_controller rclcpp std_msgs geometry_msgs)
ament_target_dependencies(sj_controller_8 rclcpp std_msgs geometry_msgs)

install(TARGETS
sj_controller
sj_controller_8
DESTINATION lib/${PROJECT_NAME})

ament_package()
