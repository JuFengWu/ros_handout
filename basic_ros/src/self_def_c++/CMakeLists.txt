cmake_minimum_required(VERSION 3.5)
project(self_def_cpp)

#Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(self_def_msg_srv REQUIRED)
find_package(rclcpp_action REQUIRED)


add_executable(service src/service.cpp)
ament_target_dependencies(service rclcpp self_def_msg_srv)

add_executable(client src/client.cpp)
ament_target_dependencies(client rclcpp self_def_msg_srv)

add_executable(pub src/pub.cpp)
ament_target_dependencies(pub rclcpp self_def_msg_srv)

add_executable(sub src/sub.cpp)
ament_target_dependencies(sub rclcpp self_def_msg_srv)

add_executable(action_client src/action_client.cpp)
ament_target_dependencies(action_client rclcpp self_def_msg_srv rclcpp_action)

add_executable(action_server src/action_server.cpp)
ament_target_dependencies(action_server rclcpp self_def_msg_srv rclcpp_action)

install(TARGETS
  service
  client
  sub
  pub
  action_client
  action_server
  DESTINATION lib/${PROJECT_NAME})

ament_package()
