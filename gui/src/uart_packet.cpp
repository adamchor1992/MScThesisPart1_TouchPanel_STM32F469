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
    return Source::ERROR;
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
    return ModuleID::ERROR;
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
  else
  {
    return Function::ERROR;
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
    return Parameter::ERROR;
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
    return Sign::ERROR;
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

void UartPacket::convertToUartPacketTable(uint8_t uartPacketTable[]) const
{
  uartPacketTable[0] = m_Source;
  uartPacketTable[1] = m_Module;
  uartPacketTable[2] = m_Function;
  uartPacketTable[3] = m_Parameter;
  uartPacketTable[4] = m_Sign;
  uartPacketTable[5] = m_Length;
  
  uint8_t lengthInt = m_Length - '0';
  
  for(uint8_t i=0; i < lengthInt; i++)
  {
    uartPacketTable[6 + i] = m_Payload[i]; //payload starts from 6th element up to [6 + length] element
  }
}