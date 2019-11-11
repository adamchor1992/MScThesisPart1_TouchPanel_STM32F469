#pragma once

const int PACKET_SIZE = 20;
const int PAYLOAD_SIZE = 10;
const int CRC_SIZE = 4;
const int INIT_PACKETS_COUNT = 24;

/*Source/target field*/
enum class Source 
{
  SOURCE_TARGET1 = '1',
  SOURCE_ERROR = 0
};

/*Module field*/
enum class ModuleID 
{
  MODULE1 = '1', 
  MODULE2 = '2', 
  MODULE3 = '3', 
  MODULEID_ERROR = 0
};

/*Function field*/
enum class Function 
{
  DATA_PACKET = '1',
  INIT_PACKET = '2',
  DEINIT_PACKET = '3',
  ENABLE_PARAMETER_PACKET = '4',
  DISABLE_PARAMETER_PACKET = '5',
  SET_PARAMETER_PACKET = '6',
  SET_GRAPH_RANGE_MIN = '7',
  SET_GRAPH_RANGE_MAX = '8',
  SET_GRAPH_TIME_RANGE = '9',
  FUNCTION_ERROR = 0
};

/*Parameter field*/
enum class Parameter 
{ 
  NULL_PARAMETER = '0',
  VOLTAGE_PARAMETER = 'v',
  CURRENT_PARAMETER = 'c',
  FREQUENCY_PARAMETER = 'f',
  POWER_PARAMETER = 'p',
  PARAMETER1 = '1',
  PARAMETER2 = '2',
  PARAMETER3 = '3',
  PARAMETER4 = '4',
  PARAMETER5 = '5',
  PARAMETER6 = '6',
  PARAMETER7 = '7',
  PARAMETER8 = '8',
  PARAMETER9 = '9',
  PARAMETER10 = 'a',
  PARAMETER_ERROR = 0
};

/*Sign field*/
enum class Sign 
{
  POSITIVE_SIGN = '1',
  NEGATIVE_SIGN = '2',
  SIGN_ERROR = 0
};

/*Length field*/
enum class Length 
{
  NO_PAYLOAD = '0',
  LENGTH_ERROR = 0
};