#ifndef UART_FRAME_STRUCT_H
#define UART_FRAME_STRUCT_H

struct UARTFrameStruct_t
{
  uint8_t source; 
  uint8_t module; 
  uint8_t parameter;
  uint8_t length; 
  uint8_t payload[8];
  uint8_t crc[4];
};

#endif // UART_FRAME_STRUCT_H
