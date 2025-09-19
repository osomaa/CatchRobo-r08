source /opt/ros/humble/setup.bash
source install/local_setup.bash
colcon build --packages-select motor_control
ros2 launch motor_control bringup.launch.py
ros2 topic pub --once /motor/observe/done std_msgs/msg/Bool "{data: true}"
ros2 topic echo /motor/observe/done
ros2 topic echo /motor/state