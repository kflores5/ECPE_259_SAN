#!/usr/bin/python
import time
import serial
import struct
import math
import signal
import sys
import types

#print('hello')
portName = '/dev/tty.usbserial-A501DGBL'
brate = 9600
par = serial.PARITY_NONE
bsize = serial.EIGHTBITS
stopb = serial.STOPBITS_ONE
terminate = 0


ser = serial.Serial( port=portName,
                     baudrate = brate,
                     parity = par,
                     bytesize = bsize,
                     stopbits = stopb)

def signalHandler( signum, frame ):
    global terminate
    print("Exiting program")
    terminate = 1
    if ser:
        ser.close()
    sys.exit()

def main():
    request()


def request():
    print("requesting")
    while(1):
        ser.write('K'.encode('utf-8'))
        val1=readValue()
        val2=readValue()
        val3=readValue()
        val4=readValue()
        val5=readValue()
        val6=readValue()
        print(val1,val2,val3,val4,val5,val6)

def readValue():
    result = ''
    while(1):
        val = ser.read()
        try:
            if val and len(val):
                data = struct.unpack('B',val)
                if data[0] == 10:
                    break
                else:
                    result = result + chr(data[0])
        except:
            return 99999
            print("Reading value error")
            break
    return int(result)

signal.signal( signal.SIGINT, signalHandler )

if __name__ == "__main__":
    main()
