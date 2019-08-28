import InitSerial

init = InitSerial.Init

#custom_frame = b'111800000000'

#############################RECEIVING###############################

while True:

   print("Waiting for input...")
   #flush input to be sure there is nothing left in buffers
   init.ser.flushInput()
   
   #get 16 bytes frame from UART
   full_received_frame = init.ser.read(16)

   #divide frame into data frame part and crc frame part
   data_frame_part = full_received_frame[0:12]
   crc_frame_part = full_received_frame[12:16]

   #decode data frame part to string format for parsing
   data_frame_part = data_frame_part.decode('utf-8') 

   #parse data frame part
   data_frame_part = list(data_frame_part)
   header = data_frame_part[0:3]
   length = int(data_frame_part[3])
   payload = data_frame_part[4:4+length]
   crc = crc_frame_part
   
   #calculate CRC for received frame
   #calculated_crc32 = crc32_func(data_frame_part)
   
   #check if actual received CRC is equal to calculated CRC
   #assert(crc_frame_part == calculated_crc32)
   
   #display parsed frame contents
   print("Full frame: " + str(data_frame_part))
   print("Header: " + str(header))
   print("Length: " + str(length))
   print("Payload: " + str(payload))
   print("CRC: " + str(crc))
    
#############################RECEIVING END###############################
