cmake_minimum_required(VERSION 3.16)
project(motor_control)

# ---- build options ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

# ---- packages ----
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)

# ---- interfaces ----
set(IDL_FILES
  "msg/ReturnAt.msg"
  "msg/SendAt.msg"
  "msg/SendArray.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${IDL_FILES}
  DEPENDENCIES builtin_interfaces std_msgs  # geometry_msgs不要なら外せる
)

ament_export_dependencies(rosidl_default_runtime)

# typesupport名は保持
rosidl_get_typesupport_target(
  cpp_typesupport_target
  ${PROJECT_NAME}
  "rosidl_typesupport_cpp"
)

# ---- headers ----
# パッケージ内ヘッダを公開（例: include/motor_control/xxx.hpp）
ament_export_include_directories(include)

# ---- nodes ----
# ★ ソースファイル名を実体に合わせる（control.cpp or control_node.cpp）
add_executable(communication_node src/communication_node.cpp)
target_include_directories(communication_node PUBLIC include)
ament_target_dependencies(communication_node rclcpp std_msgs)
target_link_libraries(communication_node ${cpp_typesupport_target})

add_executable(control_node src/control_node.cpp)   # ←必要に応じて control_node.cpp に戻す
target_include_directories(control_node PUBLIC include)
ament_target_dependencies(control_node rclcpp std_msgs ament_index_cpp)
target_link_libraries(control_node ${cpp_typesupport_target})

add_executable(observe_node src/observe_node.cpp)
target_include_directories(observe_node PUBLIC include)
ament_target_dependencies(observe_node rclcpp std_msgs)
target_link_libraries(observe_node ${cpp_typesupport_target})

# ---- install ----
install(TARGETS
  communication_node
  control_node
  observe_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
install(DIRECTORY config DESTINATION share/${PROJECT_NAME})
ament_package()
