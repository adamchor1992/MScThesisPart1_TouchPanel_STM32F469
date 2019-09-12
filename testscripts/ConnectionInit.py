import InitSerial
import time

init = InitSerial.Init

#############################SENDING###############################

source = '1'
module = '2'
frame_type = '2'      # init frame
parameter = '1'
sign = '1'

header = source + module + frame_type + parameter + sign

print("INIT FRAME")

# define payload in form of int or string
i = 0

# define payload to send
payload = str(i)

# determine payload's actual length
length = str(len(payload))

# create string of 8-length trailing null characters
trailing_zeroes = '\x00' * (10 - int(length))

# build data frame
data_frame = header + length + payload + trailing_zeroes

# calculate crc for built data frame
calculated_crc32 = init.crc32_func(data_frame.encode('utf-8'))

# convert 32 bit int crc to 4 bytes
crc_bytes = calculated_crc32.to_bytes(4, byteorder='big')

# convert data frame string to bytes
data_frame_bytes = data_frame.encode('utf-8')

full_frame = data_frame_bytes + crc_bytes

print("Payload: " + payload)
print("Full frame: " + str(full_frame))
print("Length of frame: " + str(len(full_frame)))

init.ser.write(full_frame)
