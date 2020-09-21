import tkinter as tk
import random
import numpy as np
import serial
import time
import sys
import signal

window = tk.Tk()
canvas = tk.Canvas(window, width=750, height=750, bg ='black')
canvas.pack()

def map(canvas, right, left, front, turn):
    rpix = right * 500
    lpix = left * 500
    frpix = front * 500


    if turn == 0:
        canvas.create_oval(lpix, frpix, lpix+5 , frpix+5, fill='white') #car
        if right < .85:
            canvas.create_oval(rpix+lpix+90, frpix,lpix+rpix+5+90, frpix+5, fill='blue')

    if turn == 1:
        canvas.create_oval(750-frpix,lpix,750-frpix-5,lpix-5, fill='white')
        if right < 0.85:
            canvas.create_oval(750-frpix,lpix+rpix,750-frpix+5,lpix+rpix-5,fill='orange')

    if turn == 2:
        canvas.create_oval(750-lpix,750-frpix, 750-lpix+5, 750-frpix+5, fill='white')
        if right < 0.85:
            canvas.create_oval(750-rpix-lpix+30, 750-frpix-135 ,750-rpix-lpix+5+30,750-frpix+5-135,fill="green")

    if turn == 3:
        canvas.create_oval(frpix,750-lpix,frpix+5,750-lpix-5,fill='white')
        if right < 0.85:
            canvas.create_oval(frpix+135, 750-rpix-lpix-105, frpix-5+135 ,750-lpix-rpix-5-105, fill='red')

def signal_handler(signal, frame):
    print("closing program")
    SerialPort.close()
    sys.exit(0)

print('attempting to connect')

COM = '/dev/tty.HC-05-DevB'
BAUD = 9600
SerialPort = serial.Serial(COM, BAUD, timeout=1)

turn = 0
start_time = time.time()
print('connected')
while (turn < 4):
    distances = [-1,-1,-1,-1, -1]
    IncomingData = SerialPort.readline() # 4 incoming distances from arduino

    if (IncomingData):
        data = IncomingData.decode('utf-8')
        distances = data.split('s') # processing to give the 4 incoming distances from arduino as an array

    print(distances)

    distance1 = float(distances[0]) # right
    distance2 = float(distances[1]) # front right
    distance3 = float(distances[2]) # front left
    distance4 = float(distances[3]) # left
    turn = int(distances[4])

    average_distance = (distance2 + distance3)/2
    if average_distance > 0:
        map(canvas, distance4, distance1, average_distance,turn)
        window.update()

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

final_time = time.time()-start_time
print('Course Completed')
print('You took ', final_time, ' to compete the track')

window.mainloop()
