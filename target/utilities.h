#ifndef UTILITIES_H
#define UTILITIES_H

#include "uart_frame_struct.h"
#include "crc32.h"
#include <cmath>
#include "crc32.h"

void convertFrameTableToUARTstruct(const uint8_t frameTable[],UARTFrameStruct_t & frameStructure);
void convertUARTstructToFrameTable(const UARTFrameStruct_t & frameStructure, uint8_t frameTable[]);
uint32_t calculate_CRC32 (char *data, int len);
bool checkCRC(const uint8_t frameTable[]);
void appendCRCtoFrame(uint8_t frame[]);
void clearFrameTable(uint8_t frameTable[]);
void clearFrameStructure(UARTFrameStruct_t & frameStructure);

#endif // UTILITIES_H
