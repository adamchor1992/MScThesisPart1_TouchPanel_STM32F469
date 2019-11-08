#include "utilities.h"

/*This function merely copies table elements to structure fields, no additional logic included*/
void convertUartPacketTableToUartStructure(const uint8_t uartPacketTable[],UartPacket & uartPacket)
{
  uartPacket.source = uartPacketTable[0];
  uartPacket.module = uartPacketTable[1];
  uartPacket.function = uartPacketTable[2];
  uartPacket.parameter = uartPacketTable[3];
  uartPacket.sign = uartPacketTable[4];
  uartPacket.length = uartPacketTable[5];
  
  uint8_t length_int = uartPacket.length - '0'; //convert char to int length
  
  for(uint8_t i=0; i < length_int; i++)
  {
    uartPacket.payload[i] = uartPacketTable[6 + i];
  }
}

/*This function merely copies structure fields to table elements, no additional logic included*/
void convertUartStructureToUartPacketTable(const UartPacket & uartPacket, uint8_t uartPacketTable[])
{
  uartPacketTable[0] = uartPacket.source;
  uartPacketTable[1] = uartPacket.module;
  uartPacketTable[2] = uartPacket.function;
  uartPacketTable[3] = uartPacket.parameter;
  uartPacketTable[4] = uartPacket.sign;
  uartPacketTable[5] = uartPacket.length;
  
  uint8_t length_int = uartPacket.length - '0'; //convert char to int length
  
  for(uint8_t i=0; i < length_int; i++)
  {
    uartPacketTable[6 + i] = uartPacket.payload[i]; //payload starts from 6th element up to [6 + length] element
  }
}

uint32_t calculateCrc32 (char* data, int len)
{
  uint32_t crc = 0xffffffff;
  
  while (len--)
  {
    crc = (crc << 8) ^ crcTable[((crc >> 24) ^ *data++) & 0xff];
  }
  
  return crc;
}

bool checkCrc32(const uint8_t uartPacketTable[])
{
  uint8_t crcValueReceivedRaw8Bit[4];
  uint32_t crcValueCalculated;
  uint32_t crcValueReceived;

  crcValueCalculated = calculateCrc32((char*)uartPacketTable, 16);

  crcValueReceivedRaw8Bit[0] = uartPacketTable[16];
  crcValueReceivedRaw8Bit[1] = uartPacketTable[17];
  crcValueReceivedRaw8Bit[2] = uartPacketTable[18];
  crcValueReceivedRaw8Bit[3] = uartPacketTable[19];

  crcValueReceived = crcValueReceivedRaw8Bit[3] | crcValueReceivedRaw8Bit[2] << 8 | crcValueReceivedRaw8Bit[1] << 16 | crcValueReceivedRaw8Bit[0] << 24;

  if(crcValueCalculated == crcValueReceived)
    return true;
  else
    return false;
}

void appendCrcToPacket(uint8_t uartPacketTable[])
{
    uint32_t crcValueCalculated = calculateCrc32((char*)uartPacketTable, 16);
    uint32_t* crcAddress = &crcValueCalculated;
    uint8_t *p1, *p2, *p3, *p4;

    p1 = ((uint8_t*)crcAddress);
    p2 = ((uint8_t*)crcAddress + 1);
    p3 = ((uint8_t*)crcAddress + 2);
    p4 = ((uint8_t*)crcAddress + 3);

    uartPacketTable[19] = *p1;
    uartPacketTable[18] = *p2;
    uartPacketTable[17] = *p3;
    uartPacketTable[16] = *p4;
}

void clearPacketTable(uint8_t uartPacketTable[])
{
  for(uint8_t i=0; i < PACKET_SIZE; i++)
  {
    uartPacketTable[i] = 0;
  }
}

void clearPacket(UartPacket & uartPacket)
{
  uartPacket.source = 0;
  uartPacket.module = 0;
  uartPacket.function = 0;
  uartPacket.parameter = 0;
  uartPacket.sign = 0;
  uartPacket.length = 0;
  
  for(uint8_t i=0; i < PAYLOAD_SIZE; i++)
  {
    uartPacket.payload[i] = 0;
  }
  
  for(uint8_t i=0; i < CRC_SIZE; i++)
  {
    uartPacket.crc[i] = 0;
  }
}
