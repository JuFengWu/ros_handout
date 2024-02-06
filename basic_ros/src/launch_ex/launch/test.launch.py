import sys
import os
import launch
from ament_index_python.packages import get_package_share_directory,get_package_prefix
from launch import LaunchDescription
from launch.actions.execute_process import ExecuteProcess
from launch_ros.actions import Node


def generate_launch_description():

    ld = LaunchDescription([
        Node(package = 'cpp_pubsub', executable = 'pub', output = 'screen'),
        Node(package = 'cpp_pubsub', executable = 'sub', output = 'screen')
        ])

    return ld
