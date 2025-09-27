# motor_control/launch/bringup.launch.py
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    default_csv = PathJoinSubstitution([
        FindPackageShare("motor_control"), "config", "program.csv"
    ])

    csv_arg = DeclareLaunchArgument(
        "input_csv",
        default_value=default_csv,
        description="Path to CSV for control_node"
    )

    return LaunchDescription([
        csv_arg,

        Node(
            package="motor_control",
            executable="communication_node",
            name="communication_node",
            output="screen",
        ),

        Node(
            package="motor_control",
            executable="observe_node",
            name="observe_node",
            output="screen",
        ),

        Node(
            package="motor_control",
            executable="control_node",
            name="control_node",
            output="screen",
            parameters=[{
                "input_csv": LaunchConfiguration("input_csv")
            }],
        ),
        Node(
            package="motor_control",
            executable="gpio_node",
            name="gpio_node",
            output="screen",
        ),
    ])
