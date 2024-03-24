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


set(CMAKE_AUTOMOC ON) # 啟用 MOC (Meta-Object Compiler) 的自動化。MOC 是 Qt 對 C++ 程式進行擴充的一個工具,可以讓程式使用 Qt 的信號和插槽機制
set(CMAKE_AUTOUIC ON) # 啟用該選項後,CMake 會自動將 .ui 檔案轉換為相應的 C++ 原始檔。
set(CMAKE_AUTORCC ON) # 啟用資源檔案 (.qrc) 的自動化處理。Qt 應用程式可以通過 .qrc 檔案方便地載入外部資源如圖片、音訊等。啟用該選項後,CMake會自動將 .qrc 檔案編譯為 C++ 原始檔。
set(CMAKE_INCLUDE_CURRENT_DIR ON) # 當前目錄加入到 CMake 的頭文件搜索路徑中,使程式可以方便地 include 當前目錄下的頭文件。

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
