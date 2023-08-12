cmake_minimum_required(VERSION 3.0.2)
project(ir_turtle)

find_package (
    catkin REQUIRED COMPONENTS  
    geometry_msgs
    roscpp
    rospy
    turtlesim
)

catkin_package()

include_directories( ${catkin_INCLUDE_DIRS})

add_executable(
    ir_turtle_node
    src/ir_turtle_node.cpp
)
target_link_libraries(ir_turtle_node ${catkin_LIBRARIES})