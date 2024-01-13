import serial
import time

# Define the serial port and baud rate
ser = serial.Serial('/dev/ttyACM0', 115200)  # Update the port accordingly

try:
    while True:
        data = ser.readline().decode('utf-8')
        print(data)
        # if data:
        #     sensor_data = [float(value) for value in data.strip().split(',')]
            
        #     # Print the received sensor data list
        #     print("Received sensor data:", sensor_data)

        # Code for plotting or further processing

        time.sleep(0.01)           

except KeyboardInterrupt:
    ser.close()
    print("Serial connection closed.")
