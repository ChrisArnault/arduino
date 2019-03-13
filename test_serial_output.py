
import serial

with serial.Serial('COM5', 9600) as ser:
    loop = 0
    while(True):
        c = '1'.encode("utf-8")
        t = ser.write(c)

