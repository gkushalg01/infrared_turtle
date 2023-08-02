# infrared_turtle

## what?
This repository contains a ROS turtle that moves randomly when IR seonsor is not detecting anything and stops when IR sensor detects something.  

## why?
I was asked by my senior to combine arduino, IR sensor and ROS in one project. So, I thought of controlling the ROS' turte_bot using the sensor.  

## details.  

THIS PROGRAM PUBLISHES TO cmd_vel, CAUSING A VIRTUAL TURTLE TO MOVE RANDOMLY IN ANY DIRECTION,  
IT STOPS THE TURTLE (VIRTUALLY ON SCREEN) WHENEVER THE IR SENSOR (PHYSICALLY CONNECTED TO ARDUINO -> PC -> ROS) ENCOUNTERS AN OBSTACLE PHYSICALLY  

PUBLISHING RANDOM TWISTS TO turtle1/cmd_vel  
SUBSCRIBING TO IR SENSOR CONNECTED TO ARDUINO USING rosserial, TOPIC chatter  

ARDUINO CODE IS PRESENT IN :  
#### ir_publisher.ino  

### TESTED ON :  
ROS NOETIC  
UBUNTU 20.04  
ARDUINO 1.8  

## how to run?  

1) Install the above system
2) git clone this repo
3) Perform a `catkin_make` inside the catkin_ws directory
4) Connect IR to arduino UNO and UNO to System. Make sure it is connected by typing `

### STEP TO MAKE THIS PROJECT:  

1) Connect IR to arduino UNO and UNO to System.  
```
ll /dev/ttyACM0  
sudo chmod a+rw /dev/ttyACM0  
```
IR Pin number used in this case is 4.  
(_/) Copy the code in ir_publisher.ino & Feed the code in ir_publisher.ino to Arduino.  
(_/) Install rosserial and make necessary configurations -  
     Just edit the msg.h file located Arduino/libraries/Rosserial_Arduino_Library/src/ros in line 40  
     write #include <string.h> and in line 68 and 182 remove std:: before memcpy  
     Then restart Arudino  


2) Create a catkin_ws  
```
cd catkin_ws/src  
catkin_create_pkg ir_turtle geometry_msgs turtlesim rospy roscpp  
cd ir_turtle/src  
code ir_turtle_node.cpp  
```
3) Paste the code in the cpp file  

4) Add these two lines at the last of CMakeLists.txt  

```
add_executable(pub_turtle_sub_arduino src/pubsub_to_turtlesim_and_arduino.cpp)  
target_link_libraries(pub_turtle_sub_arduino ${catkin_LIBRARIES})  
```

5) Build Package  
```
cd ~/catkin_ws  
catkin_make  
```

6) Finally,  
```
roscore  
rosrun turtlesim turtlesim_node  
rosrun rosserial_python serial_node.py /dev/ttyACM0  
rosrun ir_turtle pub_turtle_sub_arduino  
```

Now you can Play with the IR.  
