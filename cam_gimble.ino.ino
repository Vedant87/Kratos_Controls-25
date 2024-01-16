#include<ros.h>
#include<geometry_msgs/Point.h>
#include<Servo.h>
Servo s1;
Servo s2;
ros::NodeHandle nh;

geometry_msgs::Point feed;
ros::Publisher pub("cam_feedback",&feed);
int x,y,z;
void callback(const geometry_msgs::Point &msg){
  x=msg.x;
  y=msg.y;
  if(x!=0){
    s1.write(90+x*65);
    delay(200);
    s1.write(90);
  }
  if(y!=0){
    s2.write(90+y*65);
    delay(90);
    s2.write(105);
    
    }
   feed.x=x;
  feed.y=y;

   pub.publish(&feed);
  
}
ros::Subscriber<geometry_msgs::Point> sub("cam_gimble",&callback);

void setup(){
  nh.initNode();
  s1.attach(9);
  s2.attach(10);
  s1.write(90);
  s2.write(90);
  nh.subscribe(sub);
  nh.advertise(pub);
  }
 void loop(){
  nh.spinOnce();
  

  
  }
