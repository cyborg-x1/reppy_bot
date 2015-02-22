 
#include <protocol_definition.h>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/UInt8.h"


void velocityCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "reppy_bot_node");
  ros::NodeHandle n;

  ros::Subscriber vel_sub = n.subscribe("~/cmd_vel", 1000, velocityCallback);
  ros::Publisher sensor_pub = n.advertise<std_msgs::UInt8>("~/sensorDist", 1000);

  ros::Rate loop_rate(10);
  
  
  while (ros::ok())
  {
    
    std_msgs::UInt8 msg;
    msg.data = 0xef;

    sensor_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
