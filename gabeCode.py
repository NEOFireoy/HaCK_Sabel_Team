import numpy as np
import serial
import time
import sys
import signal

def signal_handler(signal, frame):
    print("closing program")
    SerialPort.close()
    sys.exit(0)

print('attempting to connect')

COM = '/dev/tty.HC-05-DevB'
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)

turn = 0

print('connected')
while (turn < 4):
    distances = [-1,-1,-1,-1, -1]
    IncomingData = SerialPort.readline() # 4 incoming distances from arduino

    if (IncomingData):
        data = IncomingData.decode('utf-8')
        distances = data.split('s') # processing to give the 4 incoming distances from arduino as an array

    distance1 = float(distances[0]) # right
    distance2 = float(distances[1]) # front right
    distance3 = float(distances[2]) # front left
    distance4 = float(distances[3]) # left
    turn = int(distances[4])

    average_distance = (distance2 + distance3)/2

    if turn == 4:
        try:
            OutgoingData = 'S' # 'S' for stop
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
        except KeyboardInterrupt:
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)
        break

    if average_distance < .175000 and average_distance > 0:
        try:
            OutgoingData = 'R' # 'S' for stop if distance gets too small
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
        except KeyboardInterrupt:
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)


    if average_distance >= .175000 and average_distance < 1.5:
        try:
            OutgoingData = 'F' # 'F' for forward
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
        except KeyboardInterrupt:
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

    time.sleep(0.01)
