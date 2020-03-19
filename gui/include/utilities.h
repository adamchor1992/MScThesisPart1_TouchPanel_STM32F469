#pragma once

#include "packet_field_definitions.h"
#include "crc32.h"
#include <cmath>

int const INIT_PARAMETER_NAME_COUNT = 5;
int const INIT_PARAMETER_NAME_OFFSET = 0;
int const INIT_PARAMETER_VALUE_COUNT = 5;
int const INIT_PARAMETER_VALUE_OFFSET = 5;
int const CUSTOM_PARAMETER_NAME_COUNT = 4;
int const CUSTOM_PARAMETER_NAME_OFFSET = 10;
int const CUSTOM_PARAMETER_VALUE_COUNT = 4;
int const CUSTOM_PARAMETER_VALUE_OFFSET = 14;
int const SETTABLE_PARAMETER_NAME_COUNT = 10;
int const SETTABLE_PARAMETER_NAME_OFFSET = 18;

int const NO_WAITING = 0;

uint32_t CalculateCrc32 (char* data, int len);
bool CheckCrc32(const uint8_t uartPacketTable[]);
void AppendCrcToPacketTable(uint8_t uartPacketTable[]);
void ClearPacketTable(uint8_t uartPacketTable[]);