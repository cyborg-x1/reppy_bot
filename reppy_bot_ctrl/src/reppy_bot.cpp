#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "serial/serial.h"
#include "sersyncproto.h"
#include "protocol_definition.h"
#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

serial::Serial serial_interface;
double base_width=0.44;
int max_speed=4000;
payload_t payloads;
boost::mutex mutex;
nav_msgs::Odometry odom_msg;
bool debug;


//SerSyncProto
sersyncproto_data_t *proto_data;

void sendbyte(uint8_t byte)
{
	serial_interface.write(&byte, 1);
}
payload_t outputbuf;

void workerReceiver()
{
    boost::posix_time::microseconds sleepTime(10);
    uint8_t cmds[]=CMD_ARRAY_INIT;
    uint8_t payload_lens[]=PAYLOAD_LEN_ARRAY_INIT;
    uint8_t header[]=HEADER_ARRAY_INIT;
    INIT_SERSYNCPROTO_DATA(serial_setup,cmds,payload_lens,header,&payloads);

    while(ros::ok())
    {
    	uint8_t cur_byte;
    	serial_interface.read(&cur_byte,1);

    	//if( sersyncproto_rec(&serial_setup, cur_byte) )
    	{
//    		switch(serial_setup.cmd)
//    		{
//
//
//    		default:
//				break;
//    		}
    	}

    	boost::this_thread::sleep(sleepTime);
    }

}

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg)
{

}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "roboyagi_motorctrl");
  ros::NodeHandle n;



  std::string port;
  int baudrate, rate, wheel_distance, wheel_diameter, wheel_width;

  n.param<std::string>("interface",port,"/dev/ttyACM0");
  n.param<bool>  ("debug_output", debug, false);
  n.param<int>   ("baudrate", baudrate, BAUD);
  n.param<double>("base_width", base_width, 0.44);
  n.param<int>   ("maxmotorspeed", max_speed, 4000);
  n.param<int> ("loop_rate", rate, 1);
  n.param<int> ("wheel_distance", wheel_distance, 0.40);
  n.param<int> ("wheel_diameter", wheel_diameter, 0.24);
  n.param<int> ("wheel_width", wheel_width, 0.025);

  ros::Subscriber sub_twist = n.subscribe("cmd_vel", 1000, twistCallback);
  ros::Publisher pub_Odom = n.advertise<nav_msgs::Odometry>("odom", 1000, 1);
  ros::Rate loop_rate(rate);

  //SerSyncProto Setup

  uint8_t cmds[]=CMD_ARRAY_INIT;
  uint8_t payload_lens[]=PAYLOAD_LEN_ARRAY_INIT;
  uint8_t header[]=HEADER_ARRAY_INIT;
  payload_t payloads;
  INIT_SERSYNCPROTO_DATA(serial_setup,cmds,payload_lens,header,&payloads);
  proto_data=&serial_setup;



  serial::Timeout timeout=serial::Timeout::simpleTimeout(1000);

  serial_interface.setBaudrate(baudrate);
  serial_interface.setPort(port);
  serial_interface.setTimeout(timeout);
  serial_interface.open();

  if(serial_interface.isOpen())
  {
	  ROS_INFO("Serial opened!");
  }
  else
  {
	  ROS_INFO("Serial could not be opened!");
	  exit(1);
  }



  boost::thread receive(workerReceiver);
  uint8_t d=0;

  while(ros::ok())
  {

	  mutex.lock();
//	  	  pub_Odom.publish(odom_msg);
	  mutex.unlock();
	  if(serial_interface.isOpen())
	  {
		  payloads.cam_pan=d;
		  sersyncproto_send(proto_data, CAM_TRANSMIT_TILT, (uint8_t*)&payloads, sendbyte);
		  d+=10;
		  if(d>180)d=0;
		 // payloads.cam_tilt=80;
		 // sersyncproto_send(proto_data, CAM_TRANSMIT_TILT, (uint8_t*)&payloads, sendbyte);
	  }
	  ros::spinOnce();
      loop_rate.sleep();
  }

  ROS_INFO("Waiting for receive thread...");
  receive.join();
}
