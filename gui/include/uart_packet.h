#ifndef UART_PACKET_H
#define UART_PACKET_H

#include <cstdint>

#define PACKET_SIZE 20
#define PAYLOAD_SIZE 10
#define CRC_SIZE 4

/*20-byte packet*/
struct UartPacket
{
  uint8_t source;                       //source/target ID
  uint8_t module;                       //module ID
  uint8_t function;                     //function type (data transfer or others)
  uint8_t parameter;                    //parameter ID
  uint8_t sign;                         //sign of payload value
  uint8_t length;                       //length of payload
  uint8_t payload[PAYLOAD_SIZE];        //payload
  uint8_t crc[CRC_SIZE];                //32 bit CRC
};

#endif
