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

COM = input("Enter the COM Port\n")
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)



distances = []

# map is divided into 30cmx30cm submaps

while (len(distances) < 5):

    try:
        OutgoingData = '1'
        SerialPort.write(bytes(OutgoingData, 'utf-8'))
        time.sleep(0.001)
    except KeyboardInterrupt:
        print("Closing and exiting the program")
        SerialPort.close()
        sys.exit(0)

    IncomingData = SerialPort.readline()
    if (IncomingData):
        data = IncomingData.decode('utf-8')
        distances.append(data)
        time.sleep(0.001)






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