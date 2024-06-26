# infrared_turtle
  
## video 
https://www.youtube.com/watch?v=PUyrIXgBTew
  
## what?
This repository contains a ROS turtle that moves randomly when IR sensor is not detecting anything and stops when IR sensor detects something.  

## why?
I was asked by my senior to combine arduino, IR sensor and ROS in one project. So, I thought of controlling the ROS' turte_bot using the sensor.  

## details.  

This program publishes to `cmd_vel`, Causing a virtual turtle to move randomly in any direction,  
It stops the turtle (virtually on screen) whenever the IR sensor (physically connected to Arduino -> PC -> ROS) Encounters an obstacle physically.  

Publishing random twists to `turtle1/cmd_vel`  
Subscribing to IR sensor connected to Arduino using `rosserial`, Topic `chatter`  

Arduino code is present in:  
#### ir_publisher.ino  

### Requirements :  
ROS Noetic  
Ubuntu 20.04  
Arduino 1.8  

## how to run?  

1) Install the above system Requirements
2) Clone this git repo
3) Perform a `catkin_make` inside the catkin_ws directory
4) Connect IR to Arduino UNO to System. Make sure it is connected by typing `ll /dev/ttyACM0(or /dev/ttyS0)`, if its not present there, please look up on the internet.
5) Install the code in .ino file on your Arduino
6) If all the above steps are done correctly, you can simply run the script
   ```bash run_ir_turtle.sh```
   
### Video
https://youtu.be/PUyrIXgBTew

### STEP TO MAKE THIS PROJECT:  

1) Connect IR to arduino UNO and UNO to System.  
```
ll /dev/ttyACM0(or /dev/ttyS0)  
sudo chmod a+rw /dev/ttyACM0(or /dev/ttyS0)  
```
IR pin number used in this case is 4.  
( a ) Copy the code in ir_publisher.ino & Feed the code in ir_publisher.ino to Arduino.  
( b ) Install rosserial and make necessary configurations -  
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
rosrun rosserial_python serial_node.py /dev/ttyACM0(or /dev/ttyS0)  
rosrun ir_turtle pub_turtle_sub_arduino  
```

Now you can Play with the IR.  



### Errors 
#### cstring: No such file or directory
Solution-
(Running on melodic)
code /home/$USER/Arduino/libraries/Rosserial_Arduino_Library/src/ros/msg.h
Replace 'std::memcpy' with 'memcpy'

Or just install 0.7.9 version of the library, it works.

#### An error occurred while uploading the sketch avrdude: ser_open(): can't open device "/dev/ttyS0": Permission denied
sudo chmod a+rw /dev/ttyACM0

#### avrdude: stk500_recv(): programmer is not responding avrdude: stk500_getsync() attempt 1 of 10: not in sync: resp=0x00
https://arduino.stackexchange.com/questions/17/avrdude-stk500-getsync-not-in-sync-resp-0x00-aka-some-dude-named-avr-won
Disconnect and reconnect the USB cable.
Press the reset button on the board.
Restart the Arduino IDE.

Or just reconnect Arduino USB to another port on PC, worked for me.

#### ERROR: cannot launch node of type [rosserial_python/serial_node.py]: rosserial_python
sudo apt-get install ros-melodic-rosserial-arduino ros-melodic-rosserial
