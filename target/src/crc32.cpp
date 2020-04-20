#include <cstring>
#include "crc32.h"
#include "packet_field_definitions.h"

uint32_t CalculateCrc32 (uint8_t const* uartPacketTable, int length)
{
  uint32_t crcValue = 0xFFFFFFFF;
  
  uint8_t dataTable[PACKET_SIZE] = {0};
  
  memcpy(dataTable, uartPacketTable, PACKET_SIZE);
  
  uint8_t* dataTablePointer = dataTable;
  
  while (length > 0)
  {
    crcValue = (crcValue << 8) ^ crcLookupTable[((crcValue >> 24) ^ *dataTablePointer++) & 0xFF];
    --length;
  }
  
  return crcValue;
}