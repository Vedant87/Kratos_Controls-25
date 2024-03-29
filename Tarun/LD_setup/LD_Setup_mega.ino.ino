#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#define DIR2 6//pump2
#define PWM2 5

#define DIR3 10//pump3
#define PWM3 11

#define DIRAS 12//augur spin 
#define PWMAS 1
std_msgs::Int16MultiArray msg;
ros::NodeHandle nh;
int msg_data[3] = {0,0,0};

void messageCb( const std_msgs::Int16MultiArray& msg){
  msg_data[0] = msg.data[0];
  msg_data[1]= msg.data[1];
  msg_data[2] =msg.data[2];
  
}



void excecute_command(){
  if(msg_data[0]==1){
    digitalWrite(PWM2,HIGH);//use peristaltic pump 1
  }
  else analogWrite(PWM2,0);
  if(msg_data[1]==1){
    digitalWrite(PWM3,HIGH);//use peristaltic pump 1
  }
  else analogWrite(PWM3,0);
  if(msg_data[2]==1){
    digitalWrite(DIRAS,HIGH);
    digitalWrite(PWMAS,HIGH);//rotate mixing auger clock
  }
  else if(msg_data[2]==-1){
    digitalWrite(DIRAS,LOW);
    digitalWrite(PWMAS, HIGH);//rotate mixing auger anti clock
  }
  else if(msg_data[2]==0){
    digitalWrite(DIRAS, LOW);
    digitalWrite(PWMAS, LOW);
  }
  else{
    analogWrite(PWMAS,0);//make sure everything is switched off 
  }
}
ros::Subscriber<std_msgs::Int16MultiArray> sub("/mega", &messageCb );
void setup() {
  nh.initNode();
  nh.subscribe(sub);

  // put your setup code here, to run once:
  pinMode(DIR2,OUTPUT);
  pinMode(PWM2,OUTPUT);

  pinMode(DIRAS,OUTPUT);
  pinMode(PWMAS,OUTPUT);//Motor used to make auger go up or down.

  pinMode(DIR3,OUTPUT);
  pinMode(PWM3,OUTPUT);//motor used for mixing chamber.

}

void loop() {
  nh.spinOnce();
  excecute_command(); 
  delay(1);
  
  
} 
