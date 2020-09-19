import numpy
import serial
import time
import sys
import signal

def signal_handler(signal, frame):
  print("closing program")
  SerialPort.close()
  sys.exit(0)

COM = input("Enter the COM Port\n")
BAUD = input("Enter the Baudrate\n")
SerialPort = serial.Serial(COM,BAUD,timeout=1)