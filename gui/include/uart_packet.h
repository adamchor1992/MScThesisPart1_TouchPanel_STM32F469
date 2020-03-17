#pragma once

#include "packet_field_definitions.h"
#include <cstdint>
#include "utilities.h"
#include <cstdio>

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
  void SetModule(uint8_t module);
  void SetFunction(Function function);
  void SetParameter(Parameter parameter);
  void SetParameter(uint8_t parameter);
  void SetSign(Sign sign);
  void SetSign(uint8_t sign);
  void SetLength(Length length);
  void SetLengthAscii(int length);
  uint8_t* SetPayload();
  
  Source GetSource() const;
  ModuleID GetModule() const;
  Function GetFunction() const;
  Parameter GetParameter() const;
  Sign GetSign() const;
  uint8_t GetLengthInt() const;
  const uint8_t* GetPayload() const;
  uint8_t* GetPacketTable() {return m_PacketTable;}
  
  void AppendCrcToPacket();
  
  bool CheckCrc32() const;
  
  void ClearPacket();
  
  void PrintCrc();
  void PrintPacket(bool withCrc = false);
  
  void UpdateFields();
  void UpdatePacketTable();
  
private:
  uint8_t m_Source;
  uint8_t m_Module;
  uint8_t m_Function;
  uint8_t m_Parameter;
  uint8_t m_Sign;
  uint8_t m_Length;
  uint8_t m_Payload[PAYLOAD_SIZE];
  uint8_t m_Crc[CRC_SIZE];
  
  uint8_t m_PacketTable[PACKET_SIZE];
};