cmake_minimum_required(VERSION 3.8)
project(atcan_bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

include_directories(include)


add_executable(atcan_bridge_node src/atcan_bridge.cpp)
ament_target_dependencies(atcan_bridge_node rclcpp std_msgs)

install(TARGETS atcan_bridge_node
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})
  
ament_package()
