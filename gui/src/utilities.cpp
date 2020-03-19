#include "utilities.h"

uint32_t CalculateCrc32 (char* data, int len)
{
  uint32_t crc = 0xffffffff;
  
  while (len--)
  {
    crc = (crc << 8) ^ crcTable[((crc >> 24) ^ *data++) & 0xff];
  }
  
  return crc;
}

bool CheckCrc32(const uint8_t uartPacketTable[])
{
  uint8_t crcValueReceivedRaw8Bit[4];
  uint32_t crcValueCalculated;
  uint32_t crcValueReceived;

  crcValueCalculated = CalculateCrc32((char*)uartPacketTable, 16);

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

void AppendCrcToPacketTable(uint8_t uartPacketTable[])
{
    uint32_t crcValueCalculated = CalculateCrc32((char*)uartPacketTable, 16);
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

void ClearPacketTable(uint8_t uartPacketTable[])
{
  for(uint8_t i=0; i < PACKET_SIZE; i++)
  {
    uartPacketTable[i] = 0;
  }
}