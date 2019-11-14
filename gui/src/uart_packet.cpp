#include "uart_packet.h"

UartPacket::UartPacket() : m_Payload {0}, m_Crc{0}
{
  m_Source = 0;           //source/target ID
  m_Module = 0;           //module ID
  m_Function = 0;         //packet type
  m_Parameter = 0;        //parameter ID
  m_Sign = 0;             //sign of payload value, '1' - positive, '2' - negative
  m_Length = 0;           //length of payload
}

UartPacket::UartPacket(const uint8_t uartPacketTable[]) : m_Payload {0}, m_Crc{0}
{  
  m_Source = uartPacketTable[0];
  m_Module = uartPacketTable[1];
  m_Function = uartPacketTable[2];
  m_Parameter = uartPacketTable[3];
  m_Sign = uartPacketTable[4];
  m_Length = uartPacketTable[5];
  
  uint8_t length_int = m_Length - '0';
  
  for(uint8_t i=0; i < length_int; i++)
  {
    m_Payload[i] = uartPacketTable[6 + i];
  }
  
  m_Crc[0] = uartPacketTable[16];
  m_Crc[1] = uartPacketTable[17];
  m_Crc[2] = uartPacketTable[18];
  m_Crc[3] = uartPacketTable[19];
}

void UartPacket::setSource(Source source)
{
  if(source == Source::SOURCE_TARGET1)
  {
    m_Source = '1';
  }
}

void UartPacket::setModule(ModuleID module)
{
  if(module == ModuleID::MODULE1)
  {
    m_Module = '1';
  }
  else if(module == ModuleID::MODULE2)
  {
    m_Module = '2';
  }
  else if(module == ModuleID::MODULE3)
  {
    m_Module = '3';
  }
}

void UartPacket::setModule(uint8_t module)
{
  m_Module = module;
}

void UartPacket::setFunction(Function function)
{
  if(function == Function::DATA_PACKET)
  {
    m_Function = '1';
  }
  else if(function == Function::INIT_PACKET)
  {
    m_Function = '2';
  }
  else if(function == Function::DEINIT_PACKET)
  {
    m_Function = '3';
  }
  else if(function == Function::ENABLE_PARAMETER_PACKET)
  {
    m_Function = '4';
  }
  else if(function == Function::DISABLE_PARAMETER_PACKET)
  {
    m_Function = '5';
  }
  else if(function == Function::SET_PARAMETER_PACKET)
  {
    m_Function = '6';
  }
  else if(function == Function::SET_GRAPH_RANGE_MIN)
  {
    m_Function = '7';
  }
  else if(function == Function::SET_GRAPH_RANGE_MAX)
  {
    m_Function = '8';
  }
}

void UartPacket::setParameter(Parameter parameter)
{
  if(parameter == Parameter::NULL_PARAMETER)
  {
    m_Parameter = '0';
  }
  else if(parameter == Parameter::VOLTAGE_PARAMETER)
  {
    m_Parameter = 'v';
  }
  else if(parameter == Parameter::CURRENT_PARAMETER)
  {
    m_Parameter = 'c';
  }
  else if(parameter == Parameter::FREQUENCY_PARAMETER)
  {
    m_Parameter = 'f';
  }
  else if(parameter == Parameter::POWER_PARAMETER)
  {
    m_Parameter = 'p';
  }
  else if(parameter == Parameter::PARAMETER1)
  {
    m_Parameter = '1';
  }
  else if(parameter == Parameter::PARAMETER2)
  {
    m_Parameter = '2';
  }
  else if(parameter == Parameter::PARAMETER3)
  {
    m_Parameter = '3';
  }
  else if(parameter == Parameter::PARAMETER4)
  {
    m_Parameter = '4';
  }
  else if(parameter == Parameter::PARAMETER5)
  {
    m_Parameter = '5';
  }
  else if(parameter == Parameter::PARAMETER6)
  {
    m_Parameter = '6';
  }
  else if(parameter == Parameter::PARAMETER7)
  {
    m_Parameter = '7';
  }
  else if(parameter == Parameter::PARAMETER8)
  {
    m_Parameter = '8';
  }
  else if(parameter == Parameter::PARAMETER9)
  {
    m_Parameter = '9';
  }
  else if(parameter == Parameter::PARAMETER10)
  {
    m_Parameter = 'a';
  }
}

void UartPacket::setParameter(uint8_t parameter)
{
  m_Parameter = parameter;
}

void UartPacket::setSign(Sign sign)
{
  if(sign == Sign::POSITIVE_SIGN)
  {
    m_Sign = '1';
  }
  else if(sign == Sign::NEGATIVE_SIGN)
  {
    m_Sign = '2';
  }
}

void UartPacket::setSign(uint8_t sign)
{
  m_Sign = sign;
}

void UartPacket::setLength(Length length)
{
  if(length == Length::NO_PAYLOAD)
  {
    m_Length = '0';
  }
}

void UartPacket::setLengthAscii(int length)
{
  m_Length = length + '0';
}

uint8_t* UartPacket::setPayload()
{
  return m_Payload;
}

Source UartPacket::getSource() const
{
  if(m_Source == '1')
  {
    return Source::SOURCE_TARGET1;
  }
  else
  {
    return Source::SOURCE_ERROR;
  }
}

ModuleID UartPacket::getModule() const
{
  if(m_Module == '1')
  {
    return ModuleID::MODULE1;
  }
  else if(m_Module == '2')
  {
    return ModuleID::MODULE2;
  }
  else if(m_Module == '3')
  {
    return ModuleID::MODULE3;
  }
  else
  {
    return ModuleID::MODULEID_ERROR;
  }
}

Function UartPacket::getFunction() const
{
  if(m_Function == '1')
  {
    return Function::DATA_PACKET;
  }
  else if(m_Function == '2')
  {
    return Function::INIT_PACKET;
  }
  else if(m_Function == '3')
  {
    return Function::DEINIT_PACKET;
  }
  else if(m_Function == '4')
  {
    return Function::ENABLE_PARAMETER_PACKET;
  }
  else if(m_Function == '5')
  {
    return Function::DISABLE_PARAMETER_PACKET;
  }
  else if(m_Function == '6')
  {
    return Function::SET_PARAMETER_PACKET;
  }
  else if(m_Function == '7')
  {
    return Function::SET_GRAPH_RANGE_MIN;
  }
  else if(m_Function == '8')
  {
    return Function::SET_GRAPH_RANGE_MAX;
  }
  else if(m_Function == '9')
  {
    return Function::SET_GRAPH_TIME_RANGE;
  }
  else
  {
    return Function::FUNCTION_ERROR;
  }
}

Parameter UartPacket::getParameter() const
{
  if(m_Parameter == '0')
  {
    return Parameter::NULL_PARAMETER;
  }
  else if(m_Parameter == 'v')
  {
    return Parameter::VOLTAGE_PARAMETER;
  }
  else if(m_Parameter == 'c')
  {
    return Parameter::CURRENT_PARAMETER;
  }
  else if(m_Parameter == 'f')
  {
    return Parameter::FREQUENCY_PARAMETER;
  }
  else if(m_Parameter == 'p')
  {
    return Parameter::POWER_PARAMETER;
  }
  else if(m_Parameter == '1')
  {
    return Parameter::PARAMETER1;
  }
  else if(m_Parameter == '2')
  {
    return Parameter::PARAMETER2;
  }
  else if(m_Parameter == '3')
  {
    return Parameter::PARAMETER3;
  }
  else if(m_Parameter == '4')
  {
    return Parameter::PARAMETER4;
  }
  else if(m_Parameter == '5')
  {
    return Parameter::PARAMETER5;
  }
  else if(m_Parameter == '6')
  {
    return Parameter::PARAMETER6;
  }
  else if(m_Parameter == '7')
  {
    return Parameter::PARAMETER7;
  }
  else if(m_Parameter == '8')
  {
    return Parameter::PARAMETER8;
  }
  else if(m_Parameter == '9')
  {
    return Parameter::PARAMETER9;
  }
  else if(m_Parameter == 'a')
  {
    return Parameter::PARAMETER10;
  }
  else
  {
    return Parameter::PARAMETER_ERROR;
  }
}

Sign UartPacket::getSign() const
{
  if(m_Sign == '1')
  {
    return Sign::POSITIVE_SIGN;
  }
  else if(m_Sign == '2')
  {
    return Sign::NEGATIVE_SIGN;
  }
  else
  {
    return Sign::SIGN_ERROR;
  }
}

uint8_t UartPacket::getLength() const
{
  return m_Length - '0';
}

const uint8_t* UartPacket::getPayload() const
{
  return m_Payload;
}

void UartPacket::appendCrcToPacket()
{
  uint32_t crcValueCalculated = calculateCrc32((char*)m_PacketTable, 16);
  uint32_t* crcAddress = &crcValueCalculated;
  uint8_t *p1, *p2, *p3, *p4;
  
  p1 = ((uint8_t*)crcAddress);
  p2 = ((uint8_t*)crcAddress + 1);
  p3 = ((uint8_t*)crcAddress + 2);
  p4 = ((uint8_t*)crcAddress + 3);
  
  m_Crc[3] = *p1;
  m_Crc[2] = *p2;
  m_Crc[1] = *p3;
  m_Crc[0] = *p4;
}

UartPacket::operator uint8_t*()
{
  for(int i=0; i<PACKET_SIZE; i++)
  {
    m_PacketTable[i] = 0;
  }
  
  m_PacketTable[0] = m_Source;
  m_PacketTable[1] = m_Module;
  m_PacketTable[2] = m_Function;
  m_PacketTable[3] = m_Parameter;
  m_PacketTable[4] = m_Sign;
  m_PacketTable[5] = m_Length;
  
  uint8_t lengthInt = m_Length - '0';
  
  for(uint8_t i=0; i < lengthInt; i++)
  {
    m_PacketTable[6 + i] = m_Payload[i]; //payload starts from 6th element up to [6 + length] element
  }
  
  m_PacketTable[16] = m_Crc[0]; 
  m_PacketTable[17] = m_Crc[1] ;
  m_PacketTable[18] = m_Crc[2] ;
  m_PacketTable[19] = m_Crc[3];
  
  return m_PacketTable;
}

void UartPacket::printCrc()
{
  printf("CRC1: %d\n", m_Crc[0]);
  printf("CRC2: %d\n", m_Crc[1]);
  printf("CRC3: %d\n", m_Crc[2]);
  printf("CRC4: %d\n", m_Crc[3]);
}

bool UartPacket::checkCrc32() const
{
  uint8_t crcValueReceivedRaw8Bit[4];
  uint32_t crcValueCalculated;
  uint32_t crcValueReceived;
  
  crcValueCalculated = calculateCrc32((char*)m_PacketTable, 16);
  
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

void UartPacket::printPacket(bool crc)
{
  printf("Source %c\n", m_Source);
  printf("Module %c\n", m_Module);
  printf("Function %c\n", m_Function);
  printf("Parameter %c\n", m_Parameter);
  printf("Sign %c\n", m_Sign);
  printf("Length char %c\n", m_Length);
  printf("Length int %d\n", m_Length);
  printf("Payload %.10s\n", m_Payload);
  if(crc == true)
  {
      printCrc();
  }
}

void UartPacket::updateFields()
{
  m_Source = m_PacketTable[0];
  m_Module = m_PacketTable[1];
  m_Function = m_PacketTable[2];
  m_Parameter = m_PacketTable[3];
  m_Sign = m_PacketTable[4];
  m_Length = m_PacketTable[5];
  
  uint8_t length_int = m_Length - '0';
  
  for(uint8_t i=0; i < length_int; i++)
  {
    m_Payload[i] = m_PacketTable[6 + i];
  }
  
  m_Crc[0] = m_PacketTable[16];
  m_Crc[1] = m_PacketTable[17];
  m_Crc[2] = m_PacketTable[18];
  m_Crc[3] = m_PacketTable[19];
}

void UartPacket::updatePacketTable()
{
  for(int i=0; i<PACKET_SIZE; i++)
  {
    m_PacketTable[i] = 0;
  }
  
  m_PacketTable[0] = m_Source;
  m_PacketTable[1] = m_Module;
  m_PacketTable[2] = m_Function;
  m_PacketTable[3] = m_Parameter;
  m_PacketTable[4] = m_Sign;
  m_PacketTable[5] = m_Length;
  
  uint8_t lengthInt = m_Length - '0';
  
  for(uint8_t i=0; i < lengthInt; i++)
  {
    m_PacketTable[6 + i] = m_Payload[i]; //payload starts from 6th element up to [6 + length] element
  }
  
  m_PacketTable[16] = m_Crc[0]; 
  m_PacketTable[17] = m_Crc[1] ;
  m_PacketTable[18] = m_Crc[2] ;
  m_PacketTable[19] = m_Crc[3];
}

void UartPacket::clearPacket()
{
  m_Source = 0;
  m_Module = 0;
  m_Function = 0;
  m_Parameter = 0;
  m_Sign = 0;
  m_Length = 0;
  
  for(uint8_t i=0; i < PAYLOAD_SIZE; i++)
  {
    m_Payload[i] = 0;
  }
  
  m_Crc[0] = 0;
  m_Crc[1] = 0;
  m_Crc[2] = 0;
  m_Crc[3] = 0;
  
  for(int i=0; i<PACKET_SIZE; i++)
  {
    m_PacketTable[i] = 0;
  }
}