from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='atcan_bridge',
            executable='atcan_bridge_node',
            name='atcan_bridge',
            output='screen',
            parameters=[{
                'port': '/dev/ttyUSB0',
                'baud': 921600,
                'dtr':  True,
                'rts':  False,
                'queue_size': 100,
            }],
        )
    ])