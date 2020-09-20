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
#print(map)

print('attempting to connect')

COM = '/dev/tty.HC-05-DevB'
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)




start_time = time.time()
# map is divided into 30cmx30cm submaps
el_time = 0.000
print('connected')
while (el_time < 10.000):

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
    IncomingData = SerialPort.readline()
    distances = [0,0, 0, 0]
    if (IncomingData):
        print('good read')
        data = IncomingData.decode('utf-8')
        distances = data.split('s')
        time.sleep(0.01)
    distances[0] = float(distances[0])
    distances[1] = float(distances[1])
    distances[2] = float(distances[2])
    distances[3] = float(distances[3])

    average_distance = (distances[1] + distances[2])/2
    print(average_distance)

    if average_distance > .3000:
        ### Moving above or below
        print('good data')
        try:
            OutgoingData = 'F'
            print('good send after data')
            SerialPort.write(bytes(OutgoingData, 'utf-8'))
            time.sleep(0.001)
        except KeyboardInterrupt:
            print('bad send after data')
            print("Closing and exiting the program")
            SerialPort.close()
            sys.exit(0)

        dist_travel = SerialPort.readline()
        dist_travel = dist_travel.decode('utf-8')
        print('good dist read')
        while float(dist_travel) < .3000:
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