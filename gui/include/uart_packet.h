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
  
  void AddressAssignment();
  
  void SetSource(Source source);
  void SetModule(ModuleID module);
  void SetFunction(Function function);
  void SetParameter(Parameter parameter);
  void SetSign(Sign sign);
  void SetLength(Length length);
  void SetLength(int length);
  uint8_t* SetPayload();
  
  Source GetSource() const;
  ModuleID GetModule() const;
  Function GetFunction() const;
  Parameter GetParameter() const;
  Sign GetSign() const;
  uint8_t GetLength() const;
  const uint8_t* GetPayload() const;
  uint8_t* GetPacketTable() {return m_PacketTable;}
  
  void AppendCrcToPacket();
  bool CheckCrc32() const;
    
  void PrintCrc();
  void PrintPacket(bool withCrc = false);
  
private:
  uint8_t m_PacketTable[PACKET_SIZE] = {0};
  
  uint8_t* m_pSource = nullptr;
  uint8_t* m_pModule = nullptr;
  uint8_t* m_pFunction = nullptr;
  uint8_t* m_pParameter = nullptr;
  uint8_t* m_pSign = nullptr;
  uint8_t* m_pLength = nullptr;
  uint8_t* m_Payload[PAYLOAD_SIZE] = {nullptr};
  uint8_t* m_Crc[CRC_SIZE] = {nullptr};
};