#include "uart_packet.h"

UartPacket::UartPacket() : m_PacketTable {0}
{
  AddressAssignment();
}

UartPacket::UartPacket(const uint8_t uartPacketTable[]) : m_PacketTable {0}
{
  AddressAssignment();
  
  *m_pSource = uartPacketTable[0];
  *m_pModule = uartPacketTable[1];
  *m_pFunction = uartPacketTable[2];
  *m_pParameter = uartPacketTable[3];
  *m_pSign = uartPacketTable[4];
  *m_pLength = uartPacketTable[5];
  
  uint8_t length_int = (*m_pLength) - '0';
  
  for(uint8_t i=0; i < length_int; i++)
  {
    *m_Payload[i] = uartPacketTable[6 + i];
  }
  
  *m_Crc[0] = uartPacketTable[16];
  *m_Crc[1] = uartPacketTable[17];
  *m_Crc[2] = uartPacketTable[18];
  *m_Crc[3] = uartPacketTable[19];
}

void UartPacket::AddressAssignment()
{
  m_pSource = &m_PacketTable[0];
  m_pModule = &m_PacketTable[1];
  m_pFunction = &m_PacketTable[2];
  m_pParameter = &m_PacketTable[3];
  m_pSign = &m_PacketTable[4];
  m_pLength = &m_PacketTable[5];
  
  m_Payload[0] = &m_PacketTable[6];
  m_Payload[1] = &m_PacketTable[7];
  m_Payload[2] = &m_PacketTable[8];
  m_Payload[3] = &m_PacketTable[9];
  m_Payload[4] = &m_PacketTable[10];
  m_Payload[5] = &m_PacketTable[11];
  m_Payload[6] = &m_PacketTable[12];
  m_Payload[7] = &m_PacketTable[13];
  m_Payload[8] = &m_PacketTable[14];
  m_Payload[9] = &m_PacketTable[15];
  
  m_Crc[0] = &m_PacketTable[16];
  m_Crc[1] = &m_PacketTable[17];
  m_Crc[2] = &m_PacketTable[18];
  m_Crc[3] = &m_PacketTable[19];
}

void UartPacket::SetSource(Source source)
{
  if(source == Source::SOURCE_TARGET1)
  {
    *m_pSource = static_cast<uint8_t>(Source::SOURCE_TARGET1);
  }
}

void UartPacket::SetModule(ModuleID module)
{
  if(module == ModuleID::MODULE1)
  {
    *m_pModule = static_cast<uint8_t>(ModuleID::MODULE1);
  }
  else if(module == ModuleID::MODULE2)
  {
    *m_pModule = static_cast<uint8_t>(ModuleID::MODULE2);
  }
  else if(module == ModuleID::MODULE3)
  {
    *m_pModule = static_cast<uint8_t>(ModuleID::MODULE3);
  }
}

void UartPacket::SetFunction(Function function)
{
  if(function == Function::DATA_PACKET)
  {
    *m_pFunction = static_cast<uint8_t>(Function::DATA_PACKET);
  }
  else if(function == Function::INIT_PACKET)
  {
    *m_pFunction = static_cast<uint8_t>(Function::INIT_PACKET);
  }
  else if(function == Function::DEINIT_PACKET)
  {
    *m_pFunction = static_cast<uint8_t>(Function::DEINIT_PACKET);
  }
  else if(function == Function::ENABLE_PARAMETER_PACKET)
  {
    *m_pFunction = static_cast<uint8_t>(Function::ENABLE_PARAMETER_PACKET);
  }
  else if(function == Function::DISABLE_PARAMETER_PACKET)
  {
    *m_pFunction = static_cast<uint8_t>(Function::DISABLE_PARAMETER_PACKET);
  }
  else if(function == Function::SET_PARAMETER_PACKET)
  {
    *m_pFunction = static_cast<uint8_t>(Function::SET_PARAMETER_PACKET);
  }
  else if(function == Function::SET_GRAPH_RANGE_MIN)
  {
    *m_pFunction = static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MIN);
  }
  else if(function == Function::SET_GRAPH_RANGE_MAX)
  {
    *m_pFunction = static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MAX);
  }
}

void UartPacket::SetParameter(Parameter parameter)
{
  if(parameter == Parameter::NULL_PARAMETER)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::NULL_PARAMETER);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER1)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER1);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER2)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER2);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER3)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER3);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER4)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER4);
  }
  else if(parameter == Parameter::PARAMETER1)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER1);
  }
  else if(parameter == Parameter::PARAMETER2)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER2);
  }
  else if(parameter == Parameter::PARAMETER3)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER3);
  }
  else if(parameter == Parameter::PARAMETER4)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER4);
  }
  else if(parameter == Parameter::PARAMETER5)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER5);
  }
  else if(parameter == Parameter::PARAMETER6)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER6);
  }
  else if(parameter == Parameter::PARAMETER7)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER7);
  }
  else if(parameter == Parameter::PARAMETER8)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER8);
  }
  else if(parameter == Parameter::PARAMETER9)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER9);
  }
  else if(parameter == Parameter::PARAMETER10)
  {
    *m_pParameter = static_cast<uint8_t>(Parameter::PARAMETER10);
  }
}

void UartPacket::SetSign(Sign sign)
{
  if(sign == Sign::POSITIVE_SIGN)
  {
    *m_pSign = static_cast<uint8_t>(Sign::POSITIVE_SIGN);
  }
  else if(sign == Sign::NEGATIVE_SIGN)
  {
    *m_pSign = static_cast<uint8_t>(Sign::NEGATIVE_SIGN);
  }
}

void UartPacket::SetLength(Length length)
{
  if(length == Length::NO_PAYLOAD)
  {
    *m_pLength = static_cast<uint8_t>(Length::NO_PAYLOAD);
  }
}

void UartPacket::SetLength(int length)
{
  *m_pLength = static_cast<uint8_t>(length + '0');
}

uint8_t* UartPacket::SetPayload()
{
  return *m_Payload;
}

Source UartPacket::GetSource() const
{
  if(*m_pSource == static_cast<uint8_t>(Source::SOURCE_TARGET1))
  {
    return Source::SOURCE_TARGET1;
  }
  else
  {
    return Source::SOURCE_ERROR;
  }
}

ModuleID UartPacket::GetModule() const
{
  if(*m_pModule == static_cast<uint8_t>(ModuleID::MODULE1))
  {
    return ModuleID::MODULE1;
  }
  else if(*m_pModule == static_cast<uint8_t>(ModuleID::MODULE2))
  {
    return ModuleID::MODULE2;
  }
  else if(*m_pModule == static_cast<uint8_t>(ModuleID::MODULE3))
  {
    return ModuleID::MODULE3;
  }
  else
  {
    return ModuleID::MODULEID_ERROR;
  }
}

Function UartPacket::GetFunction() const
{
  if(*m_pFunction == static_cast<uint8_t>(Function::DATA_PACKET))
  {
    return Function::DATA_PACKET;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::INIT_PACKET))
  {
    return Function::INIT_PACKET;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::DEINIT_PACKET))
  {
    return Function::DEINIT_PACKET;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::ENABLE_PARAMETER_PACKET))
  {
    return Function::ENABLE_PARAMETER_PACKET;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::DISABLE_PARAMETER_PACKET))
  {
    return Function::DISABLE_PARAMETER_PACKET;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::SET_PARAMETER_PACKET))
  {
    return Function::SET_PARAMETER_PACKET;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MIN))
  {
    return Function::SET_GRAPH_RANGE_MIN;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MAX))
  {
    return Function::SET_GRAPH_RANGE_MAX;
  }
  else if(*m_pFunction == static_cast<uint8_t>(Function::SET_GRAPH_TIME_RANGE))
  {
    return Function::SET_GRAPH_TIME_RANGE;
  }
  else
  {
    return Function::FUNCTION_ERROR;
  }
}

Parameter UartPacket::GetParameter() const
{
  if(*m_pParameter == static_cast<uint8_t>(Parameter::NULL_PARAMETER))
  {
    return Parameter::NULL_PARAMETER;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER1))
  {
    return Parameter::GRAPH_PARAMETER1;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER2))
  {
    return Parameter::GRAPH_PARAMETER2;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER3))
  {
    return Parameter::GRAPH_PARAMETER3;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER4))
  {
    return Parameter::GRAPH_PARAMETER4;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER1))
  {
    return Parameter::PARAMETER1;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER2))
  {
    return Parameter::PARAMETER2;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER3))
  {
    return Parameter::PARAMETER3;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER4))
  {
    return Parameter::PARAMETER4;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER5))
  {
    return Parameter::PARAMETER5;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER6))
  {
    return Parameter::PARAMETER6;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER7))
  {
    return Parameter::PARAMETER7;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER8))
  {
    return Parameter::PARAMETER8;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER9))
  {
    return Parameter::PARAMETER9;
  }
  else if(*m_pParameter == static_cast<uint8_t>(Parameter::PARAMETER10))
  {
    return Parameter::PARAMETER10;
  }
  else
  {
    return Parameter::PARAMETER_ERROR;
  }
}

Sign UartPacket::GetSign() const
{
  if(*m_pSign == static_cast<uint8_t>(Sign::POSITIVE_SIGN))
  {
    return Sign::POSITIVE_SIGN;
  }
  else if(*m_pSign == static_cast<uint8_t>(Sign::NEGATIVE_SIGN))
  {
    return Sign::NEGATIVE_SIGN;
  }
  else
  {
    return Sign::SIGN_ERROR;
  }
}

uint8_t UartPacket::GetLength() const
{
  return *m_pLength - '0';
}

const uint8_t* UartPacket::GetPayload() const
{
  return *m_Payload;
}

void UartPacket::AppendCrcToPacket()
{
  uint32_t crcValueCalculated = CalculateCrc32((char*)m_PacketTable, 16);
  uint32_t* crcAddress = &crcValueCalculated;
  uint8_t *p1, *p2, *p3, *p4;
  
  p1 = ((uint8_t*)crcAddress);
  p2 = ((uint8_t*)crcAddress + 1);
  p3 = ((uint8_t*)crcAddress + 2);
  p4 = ((uint8_t*)crcAddress + 3);
  
  *m_Crc[3] = *p1;
  *m_Crc[2] = *p2;
  *m_Crc[1] = *p3;
  *m_Crc[0] = *p4;
}

UartPacket::operator uint8_t*()
{
  return m_PacketTable;
}

void UartPacket::PrintCrc()
{
  printf("CRC1: %d\n", *m_Crc[0]);
  printf("CRC2: %d\n", *m_Crc[1]);
  printf("CRC3: %d\n", *m_Crc[2]);
  printf("CRC4: %d\n", *m_Crc[3]);
}

bool UartPacket::CheckCrc32() const
{
  uint8_t crcValueReceivedRaw8Bit[4];
  uint32_t crcValueCalculated;
  uint32_t crcValueReceived;
  
  crcValueCalculated = CalculateCrc32((char*)m_PacketTable, 16);
  
  crcValueReceivedRaw8Bit[0] = m_PacketTable[16];
  crcValueReceivedRaw8Bit[1] = m_PacketTable[17];
  crcValueReceivedRaw8Bit[2] = m_PacketTable[18];
  crcValueReceivedRaw8Bit[3] = m_PacketTable[19];
  
  crcValueReceived = crcValueReceivedRaw8Bit[3] | crcValueReceivedRaw8Bit[2] << 8 | crcValueReceivedRaw8Bit[1] << 16 | crcValueReceivedRaw8Bit[0] << 24;
  
  if(crcValueCalculated == crcValueReceived)
    return true;
  else
    return false;
}

void UartPacket::PrintPacket(bool withCrc)
{
  if(withCrc)
  {
    printf("S %c M %c F %c P %c Sign %c L %c Payload %.10s CRC1 %d CRC2 %d CRC3 %d CRC4 %d\n", *m_pSource, *m_pModule, *m_pFunction, *m_pParameter, *m_pSign, *m_pLength, *m_Payload, *m_Crc[0], *m_Crc[1], *m_Crc[2], *m_Crc[3]);
  }
  else
  {
    printf("S %c M %c F %c P %c Sign %c L %c Payload %.10s\n", *m_pSource, *m_pModule, *m_pFunction, *m_pParameter, *m_pSign, *m_pLength, *m_Payload);
  }
}