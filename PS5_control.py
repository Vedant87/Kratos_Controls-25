import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32
from geometry_msgs.msg import Twist

def callback(data):
    x = data.axes[0]
    y = data.axes[1]
    
    ang=0
    spe=0
    speed=Twist()
    if x>0:
        ang=0.1
    elif(x<0):
        ang=-0.1
    else:
        ang=0
    if(y>0):
        spe=0.2
    elif(y<0):
        spe=-0.2
    else:
        spe=0
    speed.linear.x=spe
    speed.angular.z=ang
    pub = rospy.Publisher("rover", Twist, queue_size=20)
    pub.publish(speed)

def listener():
    

    rospy.init_node("psjoy_stick_sub", anonymous=True)
    rospy.Subscriber('joy', Joy, callback)
    rate = rospy.Rate(10)  # Set the loop rate to 10 Hz

    while not rospy.is_shutdown():
        rate.sleep()

if __name__ == '__main__':

    try:
        listener()
    except rospy.ROSInterruptException:
        pass
