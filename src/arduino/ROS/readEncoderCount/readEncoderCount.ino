//ROS
#include <ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/UInt16.h>

// Tetrix Prizm
#include <PRIZM.h>
#include <Wire.h>
PRIZM prizm;

// Direction
#define FWD 1
#define BKWD 0

long publisher_timer;
int pub_rate = 50;


ros::NodeHandle nh;


bool set_; 

// Initialize Messages
geometry_msgs::Pose sum_msg;
geometry_msgs::Point point;
std_msgs::UInt16 enc1_msg;
std_msgs::UInt16 enc2_msg;


// Initialize Publishers
ros::Publisher enc1_pub("enc_count_1", &enc1_msg);
ros::Publisher enc2_pub("enc_count_2", &enc2_msg);


// Read Encoder Count
long readEncoderCount (int channel){   // ============================= READ PRIZM ENCODER DATA COUNTS ====================================

  unsigned long eCount;    // return value variable. We have to pass this an unsigned into Arduino.

  byte byte1;
  byte byte2;
  byte byte3;
  byte byte4;
  
  if(channel==1){channel= 0x49;}       // channel 1 encoder FOR count value
  if(channel==2){channel= 0x4A;}       // channel 2 encoder FOR count value
         
  Wire.beginTransmission(5);          
  Wire.write(channel);                    
  Wire.endTransmission();                    
  delay(10);
  
  Wire.requestFrom(5, 4);        
  byte1 = Wire.read();
  byte2 = Wire.read();
  byte3 = Wire.read();
  byte4 = Wire.read();  

  eCount = byte1;
  eCount = (eCount*256)+byte2;
  eCount = (eCount*256)+byte3;
  eCount = (eCount*256)+byte4;
  delay(10);
  return eCount;
}


//Set Motor Power Manually
void setMotorPower(int channel, int power)       // set Motor Channel power on PRIZM
{

        if(channel==1){channel = 0x40;}   // DC channel 1
        if(channel==2){channel = 0x41;}   // DC channel 2

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
  nh.advertise(enc1_pub);
  nh.advertise(enc2_pub);

  //PRIZM
  prizm.PrizmBegin();
}

void loop()
{ 
  if (millis() > publisher_timer) {
    
    enc1_msg.data = readEncoderCount(1);
    enc2_msg.data = readEncoderCount(2);
    enc1_pub.publish(&enc1_msg);
    enc2_pub.publish(&enc2_msg);
  
    publisher_timer = millis() + pub_rate;
  }

  nh.spinOnce();
  delay(1);
}
