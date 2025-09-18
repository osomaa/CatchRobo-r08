from setuptools import find_packages
from setuptools import setup

setup(
    name='motor_control',
    version='0.0.1',
    packages=find_packages(
        include=('motor_control', 'motor_control.*')),
)
