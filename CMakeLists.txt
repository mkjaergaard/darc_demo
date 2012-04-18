cmake_minimum_required(VERSION 2.8)
project(darc_demo)

set(CMAKE_BUILD_TYPE Debug)

find_package(darc)
find_package(ROS REQUIRED COMPONENTS sensor_msgs)

include_directories(include)

#add_subdirectory(tf_test)
add_subdirectory(opencv_test)

