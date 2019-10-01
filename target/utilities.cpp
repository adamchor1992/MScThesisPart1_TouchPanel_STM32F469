#include "utilities.h"

/*This function merely copies table elements to structure fields, no additional logic included*/
void convertFrameTableToUARTstruct(const uint8_t frameTable[],UARTFrameStruct_t & frameStructure)
{
    frameStructure.source = frameTable[0];
    frameStructure.module = frameTable[1];
    frameStructure.function = frameTable[2];
    frameStructure.parameter = frameTable[3];
    frameStructure.sign = frameTable[4];
    frameStructure.length = frameTable[5];

    uint8_t length_int = frameStructure.length - '0';

    for(uint8_t i=0; i < length_int; i++)
    {
        frameStructure.payload[i] = frameTable[6 + i];
    }
}

/*This function merely copies structure fields to table elements, no additional logic included*/
void convertUARTstructToFrameTable(const UARTFrameStruct_t & frameStructure, uint8_t frameTable[])
{
    frameTable[0] = frameStructure.source;
    frameTable[1] = frameStructure.module;
    frameTable[2] = frameStructure.function;
    frameTable[3] = frameStructure.parameter;
    frameTable[4] = frameStructure.sign;
    frameTable[5] = frameStructure.length;

    uint8_t length_int = frameStructure.length - '0';

    for(uint8_t i=0; i < length_int; i++)
    {
        frameTable[6 + i] = frameStructure.payload[i]; //payload starts from 6th element up to [6 + length] element
    }
}

uint32_t Calculate_CRC32 (char *data, int len)
{
  uint32_t crc = 0xffffffff;
  while (len--)
    crc = (crc << 8) ^ crc_table[((crc >> 24) ^ *data++) & 0xff];
  return crc;
}

bool checkCRC(const uint8_t frameTable[])
{
  uint8_t CRC_Value_Received_Raw_8Bit[4];
  uint32_t CRC_Value_Calculated;
  uint32_t CRC_Value_Received;
  
  CRC_Value_Calculated = Calculate_CRC32((char*)frameTable, 16);
  
  CRC_Value_Received_Raw_8Bit[0] = frameTable[16];
  CRC_Value_Received_Raw_8Bit[1] = frameTable[17];
  CRC_Value_Received_Raw_8Bit[2] = frameTable[18];
  CRC_Value_Received_Raw_8Bit[3] = frameTable[19];
  
  CRC_Value_Received = CRC_Value_Received_Raw_8Bit[3] | CRC_Value_Received_Raw_8Bit[2] << 8 | CRC_Value_Received_Raw_8Bit[1] << 16 | CRC_Value_Received_Raw_8Bit[0] << 24;
  
  if(CRC_Value_Calculated == CRC_Value_Received)
    return true;
  else
    return false;
}

void appendCRCtoFrame(uint8_t frame[])
{
    uint32_t CRC_Value_Calculated = Calculate_CRC32((char*)frame, 16);
    uint32_t* CRC_Address = &CRC_Value_Calculated;
    uint8_t *p1, *p2, *p3, *p4;

    p1 = ((uint8_t*)CRC_Address);
    p2 = ((uint8_t*)CRC_Address + 1);
    p3 = ((uint8_t*)CRC_Address + 2);
    p4 = ((uint8_t*)CRC_Address + 3);

    frame[19] = *p1;
    frame[18] = *p2;
    frame[17] = *p3;
    frame[16] = *p4;
}
