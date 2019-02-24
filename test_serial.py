
import serial

with serial.Serial('COM5', 57600) as ser:
    print(ser.read(100))

