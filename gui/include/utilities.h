#ifndef UTILITIES_H
#define UTILITIES_H

#include "uart_packet.h"
#include "crc32.h"
#include <cmath>

uint32_t calculateCrc32 (char* data, int len);
bool checkCrc32(const uint8_t uartPacketTable[]);
void appendCrcToPacketTable(uint8_t uartPacketTable[]);
void clearPacketTable(uint8_t uartPacketTable[]);
#endif
