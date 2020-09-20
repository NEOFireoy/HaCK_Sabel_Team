import numpy as np
import serial
import time
import sys
import signal


def signal_handler(signal, frame):
    print("closing program")
    SerialPort.close()
    sys.exit(0)

map = np.zeros((5, 5))

print('attempting to connect')

COM = '/dev/tty.HC-05-DevB'
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)


start_time = time.time()
# map is divided into 30cmx30cm submaps
el_time = 0.000
# print('connected')
while (el_time < 300.000):
    OutgoingData = ""
    try:
        OutgoingData = 'a'
        # print('good out')
        SerialPort.write(bytes(OutgoingData, 'utf-8')) # sends 'F' to arduino
        # time.sleep(0.001)
    except KeyboardInterrupt:
        # print('bad out')
        print("Closing and exiting the program")
        SerialPort.close()
        sys.exit(0)
    # num = 0
    # print('good send')
    IncomingData = SerialPort.readline() # 4 incoming distances from arduino
    distances = [-1,-1,-1,-1]

    if (IncomingData):
        # print('good read')
        data = IncomingData.decode('utf-8')
        distances = data.split('s') # processing to give the 4 incoming distances from arduino as an array
        print(distances)
        # time.sleep(0.01)
    # print(data)

    distance1 = float(distances[0]) # right
    distance2 = float(distances[1]) # front right
    distance3 = float(distances[2]) # front left
    distance4 = float(distances[3]) # left

    average_distance = (distance2 + distance3)/2
    print("average distance: ", average_distance)
    print("left distance is:", distance4)
    print("right distance is:", distance1, "\n")

    # stop
    print(OutgoingData)
    if average_distance < .3000 and average_distance > 0:
        try:
            OutgoingData = 'R' # 'R' for stop if distance gets too small
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

        try:
            OutgoingData = 'y' # 'S' for stop if distance gets too small
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

    print(OutgoingData)
    if average_distance >= .3000 and average_distance < 1.5:
        try:
            OutgoingData = 'F' # 'S' for stop if distance gets too small
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

        try:
            OutgoingData = 'q' # 'S' for stop if distance gets too small
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

    el_time = time.time() - start_time

    print(OutgoingData)

    # try:
    #     OutgoingData = 'R' # 'R' to turn right at corner
    #     SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
    #     # time.sleep(0.001)
    # except KeyboardInterrupt:
    #     print("Closing and exiting the program")
    #     SerialPort.close()
    #     sys.exit(0)

'''
    # right turn
    if average_distance < .2000 and distance4 < .2000:
        try:
            OutgoingData = 'R' # 'R' to turn right at corner
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

    el_time = time.time() - start_time

    # left turn
    elif average_distance < .2000 and distance1 < .2000:
        try:
            OutgoingData = 'L' # 'L' to turn left at corner
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

    # stop
    if average_distance < .2000:
        try:
            OutgoingData = 'S' # 'S' for stop if distance gets too small
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

        try:
            OutgoingData = 'R' # 'R' to turn right at corner
            # print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8')) # send char to arduino
            # time.sleep(0.001)
        except KeyboardInterrupt:
            # print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)
'''
