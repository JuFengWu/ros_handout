cmake_minimum_required(VERSION 3.5)
project(turtlebot_test)

#Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(sub src/sub.cpp)
ament_target_dependencies(sub rclcpp std_msgs sensor_msgs)

install(TARGETS
  
  sub
  DESTINATION lib/${PROJECT_NAME})

ament_package()
