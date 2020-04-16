#include "uart_packet.h"
#include "crc32.h"

int const CRC_BYTE1_POSITION = 19;
int const CRC_BYTE2_POSITION = 18;
int const CRC_BYTE3_POSITION = 17;
int const CRC_BYTE4_POSITION = 16;

UartPacket::UartPacket()
{
  m_PacketTable.fill(0);
}

UartPacket::UartPacket(const uint8_t uartPacketTable[])
{  
  memcpy(m_PacketTable.data(), uartPacketTable, PACKET_SIZE);
}

UartPacket::operator uint8_t*()
{
  return m_PacketTable.data();
}

void UartPacket::SetSource(Source source)
{
  if(source == Source::SOURCE_TARGET1)
  {
    m_Source = static_cast<uint8_t>(Source::SOURCE_TARGET1);
  }
}

void UartPacket::SetModule(ModuleID module)
{
  if(module == ModuleID::MODULE1)
  {
    m_Module = static_cast<uint8_t>(ModuleID::MODULE1);
  }
  else if(module == ModuleID::MODULE2)
  {
    m_Module = static_cast<uint8_t>(ModuleID::MODULE2);
  }
  else if(module == ModuleID::MODULE3)
  {
    m_Module = static_cast<uint8_t>(ModuleID::MODULE3);
  }
}

void UartPacket::SetFunction(Function function)
{
  if(function == Function::DATA_PACKET)
  {
    m_Function = static_cast<uint8_t>(Function::DATA_PACKET);
  }
  else if(function == Function::INIT_PACKET)
  {
    m_Function = static_cast<uint8_t>(Function::INIT_PACKET);
  }
  else if(function == Function::DEINIT_PACKET)
  {
    m_Function = static_cast<uint8_t>(Function::DEINIT_PACKET);
  }
  else if(function == Function::ENABLE_PARAMETER_PACKET)
  {
    m_Function = static_cast<uint8_t>(Function::ENABLE_PARAMETER_PACKET);
  }
  else if(function == Function::DISABLE_PARAMETER_PACKET)
  {
    m_Function = static_cast<uint8_t>(Function::DISABLE_PARAMETER_PACKET);
  }
  else if(function == Function::SET_PARAMETER_PACKET)
  {
    m_Function = static_cast<uint8_t>(Function::SET_PARAMETER_PACKET);
  }
  else if(function == Function::SET_GRAPH_RANGE_MIN)
  {
    m_Function = static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MIN);
  }
  else if(function == Function::SET_GRAPH_RANGE_MAX)
  {
    m_Function = static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MAX);
  }
}

void UartPacket::SetParameter(Parameter parameter)
{
  if(parameter == Parameter::NULL_PARAMETER)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::NULL_PARAMETER);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER1)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER1);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER2)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER2);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER3)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER3);
  }
  else if(parameter == Parameter::GRAPH_PARAMETER4)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::GRAPH_PARAMETER4);
  }
  else if(parameter == Parameter::PARAMETER1)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER1);
  }
  else if(parameter == Parameter::PARAMETER2)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER2);
  }
  else if(parameter == Parameter::PARAMETER3)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER3);
  }
  else if(parameter == Parameter::PARAMETER4)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER4);
  }
  else if(parameter == Parameter::PARAMETER5)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER5);
  }
  else if(parameter == Parameter::PARAMETER6)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER6);
  }
  else if(parameter == Parameter::PARAMETER7)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER7);
  }
  else if(parameter == Parameter::PARAMETER8)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER8);
  }
  else if(parameter == Parameter::PARAMETER9)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER9);
  }
  else if(parameter == Parameter::PARAMETER10)
  {
    m_Parameter = static_cast<uint8_t>(Parameter::PARAMETER10);
  }
}

void UartPacket::SetSign(Sign sign)
{
  if(sign == Sign::POSITIVE_SIGN)
  {
    m_Sign = static_cast<uint8_t>(Sign::POSITIVE_SIGN);
  }
  else if(sign == Sign::NEGATIVE_SIGN)
  {
    m_Sign = static_cast<uint8_t>(Sign::NEGATIVE_SIGN);
  }
}

void UartPacket::SetLength(Length length)
{
  if(length == Length::NO_PAYLOAD)
  {
    m_Length = static_cast<uint8_t>(Length::NO_PAYLOAD);
  }
}

void UartPacket::SetLength(int length)
{
  m_Length = static_cast<uint8_t>(length + '0');
}

void UartPacket::SetPayload(uint8_t* payload)
{
  memcpy(m_Payload, payload, PAYLOAD_SIZE);
}

Source UartPacket::GetSource() const
{
  if(m_Source == static_cast<uint8_t>(Source::SOURCE_TARGET1))
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
  if(m_Module == static_cast<uint8_t>(ModuleID::MODULE1))
  {
    return ModuleID::MODULE1;
  }
  else if(m_Module == static_cast<uint8_t>(ModuleID::MODULE2))
  {
    return ModuleID::MODULE2;
  }
  else if(m_Module == static_cast<uint8_t>(ModuleID::MODULE3))
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
  if(m_Function == static_cast<uint8_t>(Function::DATA_PACKET))
  {
    return Function::DATA_PACKET;
  }
  else if(m_Function == static_cast<uint8_t>(Function::INIT_PACKET))
  {
    return Function::INIT_PACKET;
  }
  else if(m_Function == static_cast<uint8_t>(Function::DEINIT_PACKET))
  {
    return Function::DEINIT_PACKET;
  }
  else if(m_Function == static_cast<uint8_t>(Function::ENABLE_PARAMETER_PACKET))
  {
    return Function::ENABLE_PARAMETER_PACKET;
  }
  else if(m_Function == static_cast<uint8_t>(Function::DISABLE_PARAMETER_PACKET))
  {
    return Function::DISABLE_PARAMETER_PACKET;
  }
  else if(m_Function == static_cast<uint8_t>(Function::SET_PARAMETER_PACKET))
  {
    return Function::SET_PARAMETER_PACKET;
  }
  else if(m_Function == static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MIN))
  {
    return Function::SET_GRAPH_RANGE_MIN;
  }
  else if(m_Function == static_cast<uint8_t>(Function::SET_GRAPH_RANGE_MAX))
  {
    return Function::SET_GRAPH_RANGE_MAX;
  }
  else if(m_Function == static_cast<uint8_t>(Function::SET_GRAPH_TIME_RANGE))
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
  if(m_Parameter == static_cast<uint8_t>(Parameter::NULL_PARAMETER))
  {
    return Parameter::NULL_PARAMETER;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER1))
  {
    return Parameter::GRAPH_PARAMETER1;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER2))
  {
    return Parameter::GRAPH_PARAMETER2;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER3))
  {
    return Parameter::GRAPH_PARAMETER3;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::GRAPH_PARAMETER4))
  {
    return Parameter::GRAPH_PARAMETER4;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER1))
  {
    return Parameter::PARAMETER1;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER2))
  {
    return Parameter::PARAMETER2;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER3))
  {
    return Parameter::PARAMETER3;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER4))
  {
    return Parameter::PARAMETER4;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER5))
  {
    return Parameter::PARAMETER5;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER6))
  {
    return Parameter::PARAMETER6;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER7))
  {
    return Parameter::PARAMETER7;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER8))
  {
    return Parameter::PARAMETER8;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER9))
  {
    return Parameter::PARAMETER9;
  }
  else if(m_Parameter == static_cast<uint8_t>(Parameter::PARAMETER10))
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
  if(m_Sign == static_cast<uint8_t>(Sign::POSITIVE_SIGN))
  {
    return Sign::POSITIVE_SIGN;
  }
  else if(m_Sign == static_cast<uint8_t>(Sign::NEGATIVE_SIGN))
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
  return m_Length - '0';
}

void UartPacket::AppendCrcToPacket()
{
  uint32_t crcValueCalculated = CalculateCrc32(m_PacketTable.data(), PACKET_SIZE_WITHOUT_CRC);
  uint32_t* crcAddress = &crcValueCalculated;
  
  uint8_t* p1 = reinterpret_cast<uint8_t*>(crcAddress);
  uint8_t* p2 = reinterpret_cast<uint8_t*>(crcAddress) + 1;
  uint8_t* p3 = reinterpret_cast<uint8_t*>(crcAddress) + 2;
  uint8_t* p4 = reinterpret_cast<uint8_t*>(crcAddress) + 3;
  
  m_PacketTable[CRC_BYTE1_POSITION] = *p1;
  m_PacketTable[CRC_BYTE2_POSITION] = *p2;
  m_PacketTable[CRC_BYTE3_POSITION] = *p3;
  m_PacketTable[CRC_BYTE4_POSITION] = *p4;
}

bool UartPacket::CheckCrc32() const
{
  uint8_t crcValueReceivedRaw8Bit[4] = {0};
  uint32_t crcValueCalculated = CalculateCrc32(m_PacketTable.data(), PACKET_SIZE_WITHOUT_CRC);
  
  crcValueReceivedRaw8Bit[0] = m_PacketTable[CRC_BYTE4_POSITION];
  crcValueReceivedRaw8Bit[1] = m_PacketTable[CRC_BYTE3_POSITION];
  crcValueReceivedRaw8Bit[2] = m_PacketTable[CRC_BYTE2_POSITION];
  crcValueReceivedRaw8Bit[3] = m_PacketTable[CRC_BYTE1_POSITION];
  
  uint32_t crcValueReceived = crcValueReceivedRaw8Bit[3] | crcValueReceivedRaw8Bit[2] << 8 | crcValueReceivedRaw8Bit[1] << 16 | crcValueReceivedRaw8Bit[0] << 24;
  
  return crcValueCalculated == crcValueReceived;
}

void UartPacket::PrintPacket(bool withCrc) const
{
  if(withCrc)
  {
    printf("S %c M %c F %c P %c Sign %c L %c Payload %.10s CRC1 %d CRC2 %d CRC3 %d CRC4 %d\n", 
           m_Source, 
           m_Module, 
           m_Function, 
           m_Parameter, 
           m_Sign, 
           m_Length, 
           m_Payload, 
           m_PacketTable[CRC_BYTE4_POSITION], 
           m_PacketTable[CRC_BYTE3_POSITION], 
           m_PacketTable[CRC_BYTE2_POSITION], 
           m_PacketTable[CRC_BYTE1_POSITION]);
  }
  else
  {
    printf("S %c M %c F %c P %c Sign %c L %c Payload %.10s\n", 
           m_Source, 
           m_Module, 
           m_Function, 
           m_Parameter, 
           m_Sign, 
           m_Length, 
           m_Payload);
  }
}