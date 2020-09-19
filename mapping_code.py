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
posx = 1
posy = 0
print(map)

COM = 'COM4'
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)



distances = np.array((0,0,0,0,), dtype='float')
start_time = time.time()
# map is divided into 30cmx30cm submaps
el_time = 0.000
while (el_time < 20.000):

    try:
        OutgoingData = '1'
        SerialPort.write(bytes(OutgoingData, 'utf-8'))
        time.sleep(0.001)
    except KeyboardInterrupt:
        print("Closing and exiting the program")
        SerialPort.close()
        sys.exit(0)
    num = 0
    while (num < 4):
        IncomingData = SerialPort.readline()
        if (IncomingData):
            data = IncomingData.decode('utf-8')
            distances[num] = data
            num = num + 1
            time.sleep(0.01)
    print(distances)
    el_time = time.time() - start_time

final_time = time.time() - start_time
print(final_time)


'''
while (1):
  try:
     OutgoingData=input('> ')
     SerialPort.write(bytes(OutgoingData,'utf-8'))
  except KeyboardInterrupt:
     print("Closing and exiting the program")
     SerialPort.close()
     sys.exit(0)
  IncomingData=SerialPort.readline()
  if(IncomingData):
     print((IncomingData).decode('utf-8'))
  time.sleep(0.01)
'''