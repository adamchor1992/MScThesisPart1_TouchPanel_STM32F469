import InitSerial
import time

init = InitSerial.Init

#############################SENDING###############################

#constant header assuming source, module and parameter is all 1
header = '111'

#define inital payload in form of int or string
i = 0.1

while True:
    print("Number: " + str(i))
    
    #define payload to send
    payload = str(i)
    
    #determine payload's actual length
    length = str(len(payload))

    print("Length: " + str(length))

    #create string of 8-length trailing null characters
    trailing_zeroes = '\x00' * (8 - int(length))

    #build data frame
    data_frame = header + length + payload + trailing_zeroes

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

    i = i + 0.1

    if i >= 100:
        i = 0.0

    i = round(i, 1) #round i so it is exactly %.2f precision

    time.sleep(0.1)