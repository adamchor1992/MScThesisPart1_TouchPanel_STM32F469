import InitSerial
import time

init = InitSerial.Init

#############################SENDING###############################
header = '111'
payload = str(50)

length = str(len(payload))

trailing_zeroes = '\x00' * (8 - int(length))

frame = header + length + payload + trailing_zeroes

value_crc32 = init.crc32_func(frame.encode('utf-8'))
print("Hex CRC:")
print(hex(value_crc32))

crc_bytes = (value_crc32).to_bytes(4, byteorder='big')
print("Bytes CRC:")
print(crc_bytes)

data_frame_bytes = frame.encode('utf-8')
#print(data_frame_bytes)

full_frame = data_frame_bytes + crc_bytes
print("Full frame:")
print(full_frame)

init.ser.write(full_frame)

time.sleep(0.05)

init.ser.close()

