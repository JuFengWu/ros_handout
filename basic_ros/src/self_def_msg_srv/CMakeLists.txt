cmake_minimum_required(VERSION 3.5)
project(self_def_msg_srv)

#Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(action_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(action_msgs REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ErrorCode.msg"
  "srv/AddMany.srv"
  "action/MyAction.action"
  DEPENDENCIES
  std_msgs
)


ament_export_dependencies(rosidl_default_runtime)

ament_package()
