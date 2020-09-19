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
'''
Map: 
-------------
| 0 0 0 0 0 |
| 0 0 0 0 0 |
| 0 0 0 0 0 |
| 0 0 0 0 0 |
| 0 * 0 0 0 |
-------------

* : Robot
1 : Object
0 : Empty

'''
posx = 1
posy = 4
# print(map)

print('attempting to connect')

COM = 'COM4'
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)

distances = np.array((0, 0, 0, 0,), dtype='float')
start_time = time.time()
# map is divided into 30cmx30cm submaps
el_time = 0.000
print('connected')
while (el_time < 10.000):
    print('good connect')
    try:
        OutgoingData = '1'
        print('good out')
        SerialPort.write(bytes(OutgoingData, 'utf-8'))
        time.sleep(0.001)
    except KeyboardInterrupt:
        print('bad out')
        print("Closing and exiting the program")
        SerialPort.close()
        sys.exit(0)
    num = 0
    print('good send')
    while (num < 4):
        IncomingData = SerialPort.readline()
        if (IncomingData):
            print('good read')
            data = IncomingData.decode('utf-8')
            distances[num] = float(data)
            num = num + 1
            time.sleep(0.01)

    if distances[1] > 30.00 and distances[2] > 30.00:
        ### Moving above or below
        print('good data')
        try:
            OutgoingData = 'F'
            print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8'))
            time.sleep(0.001)
        except KeyboardInterrupt:
            prin('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

        dist_travel = SerialPort.readline()
        dist_travel = dist_travel.decode('utf-8')
        print('good dist read')
        while float(dist_travel) < 30.00:
            print('good dist usage')
            print(dist_travel)
            dist_travel = SerialPort.readline()
            dist_travel = dist_travel.decode('utf-8')

        try:
            print('stopping')
            OutgoingData = '1'
            SerialPort.write(bytes(OutgoingData, 'utf-8'))
            time.sleep(0.001)
        except KeyboardInterrupt:
            print('bad stop')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

    el_time = time.time() - start_time

final_time = time.time() - start_time


