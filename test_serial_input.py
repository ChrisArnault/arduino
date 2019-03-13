
import serial

with serial.Serial('COM5', 9600) as ser:
    while(True):
        t = ser.read(100).decode("utf-8")
        line = t.split("\r\n")
        for w in line:
            print(w)

