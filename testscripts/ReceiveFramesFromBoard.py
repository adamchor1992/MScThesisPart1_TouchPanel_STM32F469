import InitSerial

init = InitSerial.Init

#############################RECEIVING###############################

print("Waiting for input...")

while True:

   #flush input to be sure there is nothing left in buffers
   init.ser.flushInput()
   
   #get 16 bytes frame from UART
   full_received_frame = init.ser.read(20)

   #divide frame into data frame part and crc frame part
   data_frame_part = full_received_frame[0:16]
   crc_frame_part = full_received_frame[16:20]

   #decode data frame part to string format for parsing
   data_frame_part = data_frame_part.decode('utf-8') 

   #parse data frame part
   data_frame_part = list(data_frame_part)

   source = data_frame_part[0]            #source ID
   module = data_frame_part[1];           #module ID
   type = data_frame_part[2];             #frame type (data or control)
   parameter = data_frame_part[3];        #parameter ID
   sign = data_frame_part[4];             #sign of payload value, '1' - positive, '2' - negative, always '1' for control frame
   length = int(data_frame_part[5])       #length of payload

   payload = data_frame_part[6:6+length]
   crc = crc_frame_part
   
   #calculate CRC for received frame
   #calculated_crc32 = crc32_func(data_frame_part)
   
   #check if actual received CRC is equal to calculated CRC
   #assert(crc_frame_part == calculated_crc32)
   
   #display parsed frame contents
   print("Full frame: " + str(data_frame_part))
   print("Source: " + str(source))
   print("Module: " + str(module))
   print("Type: " + str(type))
   print("Parameter: " + str(parameter))
   print("Sign: " + str(sign))
   print("Length: " + str(length))
   print("Payload: " + str(payload))
   print("CRC: " + str(crc))
   print()
    
#############################RECEIVING END###############################
