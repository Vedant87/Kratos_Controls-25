#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32
from geometry_msgs.msg import Twist

def callback(data):
    a = data.buttons[0]
    b=data.buttons[1]
    c=data.buttons[2]
    d1=data.buttons[3]
    d2=data.buttons[4]
    e=data.buttons[5]
    speed=Twist()
    
    speed.linear.x=a
    speed.linear.y=b
    speed.linear.z=c
    speed.angular.x=d1
    speed.angular.y=d2
    speed.angular.z=e
    pub = rospy.Publisher("pump", Twist, queue_size=20)
    pub.publish(speed)

def listener():
    

    rospy.init_node("psjoyld_stick_sub", anonymous=True)
    rospy.Subscriber('joy', Joy, callback)
    rate = rospy.Rate(10)  # Set the loop rate to 10 Hz

    while not rospy.is_shutdown():
        rate.sleep()

if _name_ == '_main_':

    try:
        listener()
    except rospy.ROSInterruptException:
        pass
