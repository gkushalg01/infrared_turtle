#include <ros/ros.h>                // FOR OBVIOUS REASONS
#include <geometry_msgs/Twist.h>    // FOR Twist MESSAGE
#include <std_msgs/Int32.h>         // FOR Int32 MESSAGE
#include <stdlib.h>                 // FOR GENERATING RANDOM NUMBERS

// A class is efficient when you want to perform Subscribing and Publishing both
class SubscribeAndPublish
{
  
  // linear and angular increment
  double x=0.01, z=0.01;

public:
  // Constructor gets called and pub + sub is initialized
  SubscribeAndPublish()
  {
    //Publishing to Turtlesim's topic cmd_vel
    pub_ = n_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    //Chatter Topic's Subscriber
    sub_ = n_.subscribe("chatter", 1000, &SubscribeAndPublish::callback, this);
    
  }

  void callback(const std_msgs::Int32::ConstPtr& ir_input)
  {
    // When something is in proximity of IR - > Stops Turtle
    if (ir_input->data == 1){
      //Give 0 vel output
        vel_output_.linear.x = 0;
        vel_output_.angular.z = 0;
        ROS_INFO("Obstacle Detected, Stopping.");
    }
    // When nothing is in proximity of IR - > Turtle Crawls
    else{  
      //Give random vel output
        // vel_output_.linear.x = double(rand())/double(RAND_MAX);
        // vel_output_.angular.z = 2*double(rand())/double(RAND_MAX)-1;
        vel_output_.linear.x += x;
        vel_output_.angular.z += z;
        ROS_INFO("Spiraling...");
    }

    //Publishing vel output and logging the output
    pub_.publish(vel_output_);
    ROS_INFO_STREAM("Sending commands\n  linear x: "<<vel_output_.linear.x
        <<"  angular z:  "<<vel_output_.angular.z);
  }

//All the required variables waiting to be initiated
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;
  geometry_msgs::Twist vel_output_;

};//End of class SubscribeAndPublish


// Driver Code
int main(int argc, char** argv){

    // Initializing ROS
    ros::init(argc, argv, "sub_ir_pub_turtle");
    //Seeding Random Number Generator
    srand(time(0));     
    
    //Calling constructor by creating object
    SubscribeAndPublish SAPObject;

    //Loop at 10Hz until node shut down
    ros::Rate rate(10);

    //Wait for callbacks to happen
    ros::spin();
}