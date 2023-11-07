#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;

const int leftMotorPin1 = 2;  
const int leftMotorPin2 = 3;  
const int leftMotorPWM = 9;  

const int rightMotorPin1 = 4;
const int rightMotorPin2 = 5;  
const int rightMotorPWM = 10; 

geometry_msgs::Twist twist_msg;

void twistCallback(const geometry_msgs::Twist& msg) {


  float linearVelocity = msg.linear.x;    
  float angularVelocity = msg.angular.z; 

  int leftMotorSpeed = (int)(linearVelocity - angularVelocity);
  int rightMotorSpeed = (int)(linearVelocity + angularVelocity);

  digitalWrite(leftMotorPin1, leftMotorSpeed > 0 ? HIGH : LOW);
  digitalWrite(leftMotorPin2, leftMotorSpeed < 0 ? HIGH : LOW);
  analogWrite(leftMotorPWM, abs(leftMotorSpeed));

  digitalWrite(rightMotorPin1, rightMotorSpeed > 0 ? HIGH : LOW);
  digitalWrite(rightMotorPin2, rightMotorSpeed < 0 ? HIGH : LOW);
  analogWrite(rightMotorPWM, abs(rightMotorSpeed));
}

ros::Subscriber<geometry_msgs::Twist> sub("/rover", &twistCallback);

void setup() {
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(10);
}
