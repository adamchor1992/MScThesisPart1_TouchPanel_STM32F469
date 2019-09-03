import InitSerial
import time
from math import sin
from math import pi
from math import radians
import math

init = InitSerial.Init

#############################SENDING###############################

# constant header assuming source, module and parameter is all 1

source = '1'
module = '1'
frame_type = '2'      # data frame
parameter = '1'

header = source + module + frame_type + parameter

# define initial payload in form of int or string
x = list(range(0, 360, 1))
y = []

for i in x:
    y.append(int((round(math.sin(math.radians(i)), 3))*999))  # int scaled by 999

index = 0

while True:
    for value in y:
        print("Number: " + str(index))

        print("sin(" + str(index) + ") = " + str(value))

        # define payload to send
        payload = str(abs(value))

        if value >= 0:
            sign = '1'
        else:
            sign = '2'

        # determine payload's actual length
        length = str(len(payload))

        print("Length: " + str(length))

        # create string of 8-length trailing null characters
        trailing_zeroes = '\x00' * (10 - int(length))

        # build data frame
        data_frame = header + sign + length + payload + trailing_zeroes

        # calculate crc for built data frame
        calculated_crc32 = init.crc32_func(data_frame.encode('utf-8'))

        # print crc in hex form
        # print(hex(calculated_crc32))

        # convert 32 bit int crc to 4 bytes
        crc_bytes = calculated_crc32.to_bytes(4, byteorder='big')

        print("CRC bytes: " + str(crc_bytes))

        # convert data frame string to bytes
        data_frame_bytes = data_frame.encode('utf-8')

        # print(data_frame_bytes)

        full_frame = data_frame_bytes + crc_bytes
        print("Full frame: " + str(full_frame))
        print("Full frame length: " + str(len(full_frame)))

        init.ser.write(full_frame)

        print("------------------------------------------------------------------------")

        index = index + 1

        time.sleep(0.05)

    index = 0
