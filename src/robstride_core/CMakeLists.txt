cmake_minimum_required(VERSION 3.16)
project(robstride_core)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# ---------- interfaces ----------
set(IDL_FILES
  "msg/MitCmd.msg"
  "msg/GoalEvent.msg"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${IDL_FILES}
  DEPENDENCIES builtin_interfaces
)
ament_export_dependencies(rosidl_default_runtime)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
# ---------- headers ----------
include_directories(include)

# ---------- nodes ----------
add_executable(at_bridge_cmd2at src/at_bridge_cmd2at.cpp)
ament_target_dependencies(at_bridge_cmd2at rclcpp std_msgs)
rosidl_target_interfaces(at_bridge_cmd2at ${cpp_typesupport_target})

add_executable(control_node src/control.cpp)
ament_target_dependencies(control_node rclcpp std_msgs)
rosidl_target_interfaces(control_node ${cpp_typesupport_target})

add_executable(csv_sequencer_node src/csv_sequencer_node.cpp)
ament_target_dependencies(csv_sequencer_node rclcpp std_msgs geometry_msgs)

install(TARGETS at_bridge_cmd2at control_node csv_sequencer_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY include/
  DESTINATION include)

ament_package()
