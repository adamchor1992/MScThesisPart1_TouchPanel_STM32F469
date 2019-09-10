import serial
import crcmod.predefined  # for CRC calculation

class Init:
    port = 'COM8'
    baud_rate = 115200
    crc32_func = crcmod.predefined.mkCrcFun('crc-32-mpeg')  # crc init
    ser = serial.Serial(port,baud_rate)  # open serial port