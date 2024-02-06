cmake_minimum_required(VERSION 3.5)
project(cpp_service)

#Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(service src/service.cpp)
ament_target_dependencies(service rclcpp example_interfaces)

add_executable(client src/client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)

install(TARGETS
  service
  client
  DESTINATION lib/${PROJECT_NAME})

ament_package()
