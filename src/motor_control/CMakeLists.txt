cmake_minimum_required(VERSION 3.16)
project(motor_control)

# --------- packages ----------
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# --------- interfaces ----------
set(IDL_FILES
  "msg/MitAt.msg"
  "msg/ReturnAt.msg"
  "msg/SendAt.msg"
  "msg/SendArray.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${IDL_FILES}
  DEPENDENCIES builtin_interfaces std_msgs geometry_msgs
)

ament_export_dependencies(rosidl_default_runtime)

rosidl_get_typesupport_target(
  cpp_typesupport_target
  ${PROJECT_NAME}
  "rosidl_typesupport_cpp"
)

# --------- headers ----------
include_directories(include)

# --------- nodes ----------
add_executable(communication_node src/communication_node.cpp)
ament_target_dependencies(communication_node rclcpp std_msgs geometry_msgs)
add_dependencies(communication_node ${cpp_typesupport_target})
target_link_libraries(communication_node ${cpp_typesupport_target})

add_executable(control_node src/control_node.cpp)
ament_target_dependencies(control_node rclcpp std_msgs geometry_msgs)
add_dependencies(control_node ${cpp_typesupport_target})
target_link_libraries(control_node ${cpp_typesupport_target})

add_executable(observe_node src/observe_node.cpp)
ament_target_dependencies(observe_node rclcpp std_msgs geometry_msgs)
add_dependencies(observe_node ${cpp_typesupport_target})
target_link_libraries(observe_node ${cpp_typesupport_target})

# --------- install ----------
install(TARGETS
  communication_node
  control_node
  observe_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

ament_package()
