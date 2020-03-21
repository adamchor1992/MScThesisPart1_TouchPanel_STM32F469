#pragma once

#include "packet_field_definitions.h"
#include <cstdint>
#include "utilities.h"
#include <cstdio>
#include <array>

class UartPacket
{
public:
  /*Default constructor initializing object to all zeroes*/
  UartPacket();
  /*Constructor initializing object to values from table*/
  explicit UartPacket(const uint8_t uartPacketTable[]);
  
  explicit operator uint8_t*();
    
  void SetSource(Source source);
  void SetModule(ModuleID module);
  void SetFunction(Function function);
  void SetParameter(Parameter parameter);
  void SetSign(Sign sign);
  void SetLength(Length length);
  void SetLength(int length);
  void SetPayload(uint8_t* payload);
  
  Source GetSource() const;
  ModuleID GetModule() const;
  Function GetFunction() const;
  Parameter GetParameter() const;
  Sign GetSign() const;
  uint8_t GetLength() const;
  uint8_t const* GetPayload() const {return m_Payload;}
  
  void AppendCrcToPacket();
  bool CheckCrc32() const;
  void PrintPacket(bool withCrc = false) const;
  
private:
  
  std::array<uint8_t, PACKET_SIZE> m_PacketTable = {0};
  
  uint8_t& m_Source = m_PacketTable[0];
  uint8_t& m_Module = m_PacketTable[1];
  uint8_t& m_Function = m_PacketTable[2];
  uint8_t& m_Parameter = m_PacketTable[3];
  uint8_t& m_Sign = m_PacketTable[4];
  uint8_t& m_Length = m_PacketTable[5];
  uint8_t* m_Payload = &m_PacketTable[6];
};