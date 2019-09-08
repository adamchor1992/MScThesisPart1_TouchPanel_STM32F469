import InitSerial
import time

init = InitSerial.Init

#############################SENDING###############################

source = '1'
module = '1'
frame_type = '2'      # data frame
parameter = '1'

header = source + module + frame_type + parameter

#define initial payload in form of int or string
i = -999.9

while True:
    print("Number: " + str(i))

    # define payload to send
    payload = str(i)

    if i >= 0:
        sign = '1'
    else:
        sign = '2'
        payload = payload[1:]     #remove minus sign

    #determine payload's actual length
    length = str(len(payload))

    print("Length: " + str(length))

    #create string of 8-length trailing null characters
    trailing_zeroes = '\x00' * (10 - int(length))

    # build data frame
    data_frame = header + sign + length + payload + trailing_zeroes

    #calculate crc for built data frame
    calculated_crc32 = init.crc32_func(data_frame.encode('utf-8'))
    
    #print crc in hex form
    #print(hex(calculated_crc32))

    #convert 32 bit int crc to 4 bytes
    crc_bytes = (calculated_crc32).to_bytes(4, byteorder='big')
	
    print("CRC bytes: " + str(crc_bytes))
	
    #convert data frame string to bytes
    data_frame_bytes = data_frame.encode('utf-8')
	
    #print(data_frame_bytes)

    full_frame = data_frame_bytes + crc_bytes
    print("Full frame: " + str(full_frame))

    init.ser.write(full_frame)

    print("------------------------------------------------------------------------")

    i = i + 0.5

    if i >= 999:
        i = -999.9

    i = round(i, 1) #round i so it is exactly %.2f precision

    time.sleep(0.01)