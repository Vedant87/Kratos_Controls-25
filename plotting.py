#!/usr/bin/env python
import rospy
from matplotlib import pyplot as plt
from sensor_msgs.msg import Joy

x_data = []
y_data = []

def callback(data):
    global x_data, y_data
    axes = data.axes
    x = axes[0]
    y = axes[1]
    x_data.append(x)
    y_data.append(y)

def plotter():
    rospy.init_node('plotter', anonymous=True)

    rospy.Subscriber("joy", Joy, callback)

    fig, ax = plt.subplots()

    while not rospy.is_shutdown():
        ax.clear()
        ax.plot(x_data, y_data)
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        plt.pause(0.000000001)

    plt.show()

    rospy.spin()

if __name__ == '__main__':
    try:
        plotter()
    except rospy.ROSInterruptException:
        pass

