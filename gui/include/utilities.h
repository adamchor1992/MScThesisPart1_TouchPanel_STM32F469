#pragma once

#include "packet_field_definitions.h"
#include "crc32.h"

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

int const CRC_BYTE1_POSITION = 19;
int const CRC_BYTE2_POSITION = 18;
int const CRC_BYTE3_POSITION = 17;
int const CRC_BYTE4_POSITION = 16;

int const NO_WAITING = 0;

uint32_t CalculateCrc32 (uint8_t const* uartPacketTable, int length);