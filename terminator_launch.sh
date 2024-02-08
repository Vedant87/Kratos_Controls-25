#!/bin/bash

ssh_login() {
    xdotool type "ssh kratos@192.168.1.10"
    xdotool key Return
    sleep 1
    xdotool type "kratos123"
    xdotool key Return
    sleep 1
    xdotool type "clear"
    xdotool key Return
    sleep 1
}

simulate_input() {
    xdotool type "$1"
    xdotool key Return
    sleep 1
}

split_vertical() {
    xdotool key Ctrl+Shift+E
    sleep 1
}

split_horizontal() {
    xdotool key Ctrl+Shift+O
    sleep 1
}
python3 sample.py
# sleep 4
# pkill -f 'python3 sample.py'

terminator_width=$(xdpyinfo | awk '/dimensions:/ {print $2}' | cut -d'x' -f1)
terminator_height=$(expr $(xdpyinfo | awk '/dimensions:/ {print $2}' | cut -d'x' -f2) / 2)


# First window
terminator --geometry=${terminator_width}x${terminator_height}+0+0 &
sleep 1
ssh_login
simulate_input "roscore"                                                                                         # roscore command
split_horizontal
ssh_login
simulate_input "sudo chmod a+rw /dev/ttyACM*"                                                                    # permissions command for serial port 
simulate_input "kratos123"
split_vertical
simulate_input "roslaunch irc2024 multiple-arduino-serial.launch"
split_horizontal
simulate_input "roslaunch irc2024 manual_control.launch"							     # base station control established

# Second Window
terminator --geometry=${terminator_width}x${terminator_height}+0+${terminator_height} &
sleep 1
simulate_input "rostopic list"
split_vertical
simulate_input "rostopic echo /feedback"
split_horizontal
simulate_input "rostopic echo /control2"

# Third Window
terminator --geometry=${terminator_width}x${terminator_height}+0+${terminator_height} &
sleep 1
simulate_input "rostopic echo /control1"
split_vertical
simulate_input "rostopic echo /cam_gimble"
