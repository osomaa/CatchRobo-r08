from setuptools import find_packages
from setuptools import setup

setup(
    name='robstride_core',
    version='0.0.1',
    packages=find_packages(
        include=('robstride_core', 'robstride_core.*')),
)
