#!/bin/sh

if [ -e /dev/ttyACM0 ]
then
    bash -c "sudo chmod a+rw /dev/ttyACM0"
    bash -c "source `pwd`/catkin_ws/devel/setup.sh && roslaunch ir_turtle ir_turtle.launch"
else
    echo "Arduino is not connected. Please connect arduino and try again."
fi
exit 0