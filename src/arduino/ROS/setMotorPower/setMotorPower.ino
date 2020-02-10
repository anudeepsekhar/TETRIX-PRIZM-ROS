//ROS
#include <ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Point.h>

// Tetrix Prizm
#include <PRIZM.h>
#include <Wire.h>
PRIZM prizm;

// Direction
#define FWD 1
#define BKWD 0


ros::NodeHandle nh;


bool set_; 


geometry_msgs::Pose sum_msg;
geometry_msgs::Point point;
ros::Publisher p("sum", &sum_msg);

//Set Motor Power Manually
void setMotorPower(int channel, int power)       // set Motor Channel power on PRIZM
{

        if(channel==1){channel = 0x40;}   // DC channel 1
        if(channel==2){channel = 0x4
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        1;}   // DC channel 2

        Wire.beginTransmission(5);
        Wire.write(channel);
        Wire.write(power);
        Wire.endTransmission();
}

// Callback function for the message
void motorCB(const geometry_msgs::Point& point_msg)
{
    setMotorPower((int)point_msg.x,  (int)point_msg.y);
}

ros::Subscriber<geometry_msgs::Point> mc_sub("motor_cmd", motorCB);


void setup()
{ 
  nh.initNode();
  nh.subscribe(mc_sub);
  nh.advertise(p);

  //PRIZM
  prizm.PrizmBegin();
}

void loop()
{  
  p.publish(&sum_msg);
  nh.spinOnce();
  delay(1);
}
