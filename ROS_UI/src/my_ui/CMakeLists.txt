cmake_minimum_required(VERSION 3.5)
project(my_ui)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)


# Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

## Specify additional locations of header files

include_directories(
  ${rclcpp_INCLUDE_DIRS}
  ${rclcpp_action_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Quick_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

link_directories(${catkin_LIBRARY_DIRS})

qt5_wrap_ui(UIC_FILES src/my_ui.ui)
set(HEADERS
  src/main_window.hpp
)

set( SRCS
src/main.cpp
src/ros_page.cpp
src/main_window.cpp
)

# Demo executable
add_executable(robot_ui ${SRCS} ${UIC_FILES} ${HEADERS})

ament_target_dependencies(robot_ui
  rclcpp
  std_msgs
)
target_link_libraries(robot_ui
  Qt5::Core
  Qt5::Quick
  Qt5::Widgets
  ${catkin_LIBRARIES}
)


# Install libraries
install(TARGETS
robot_ui
	DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
ament_package()
