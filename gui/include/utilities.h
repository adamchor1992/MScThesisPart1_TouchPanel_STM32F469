#ifndef UTILITIES_H
#define UTILITIES_H

#include "uart_packet.h"
#include "crc32.h"
#include <cmath>

void convertUartPacketTableToUartStructure(const uint8_t uartPacketTable[],UartPacket & uartPacket);
void convertUartStructureToUartPacketTable(const UartPacket & uartPacket, uint8_t uartPacketTable[]);
uint32_t calculateCrc32 (char* data, int len);
bool checkCrc32(const uint8_t uartPacketTable[]);
void appendCrcToPacket(uint8_t uartPacketTable[]);
void clearPacketTable(uint8_t uartPacketTable[]);
void clearPacket(UartPacket & uartPacket);

#endif
