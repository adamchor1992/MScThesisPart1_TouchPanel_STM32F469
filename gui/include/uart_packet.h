#ifndef UART_PACKET_H
#define UART_PACKET_H

#include "packet_field_definitions.h"
#include <cstdint>
#include "utilities.h"
#include <stdio.h>

class UartPacket
{
public:
  /*Default constructor initializing object to all zeroes*/
  UartPacket();
  /*Constructor initializing object to values from table*/
  explicit UartPacket(const uint8_t uartPacketTable[]);
  
  explicit operator uint8_t*();
  
  void setSource(Source source);
  void setModule(ModuleID module);
  void setModule(uint8_t module);
  void setFunction(Function function);
  void setParameter(Parameter parameter);
  void setParameter(uint8_t parameter);
  void setSign(Sign sign);
  void setSign(uint8_t sign);
  void setLength(Length length);
  void setLengthAscii(int length);
  uint8_t* setPayload();
  
  Source getSource() const;
  ModuleID getModule() const;
  Function getFunction() const;
  Parameter getParameter() const;
  Sign getSign() const;
  uint8_t getLength() const;
  const uint8_t* getPayload() const;
  uint8_t* getPacketTable() {return m_PacketTable;}
  
  void appendCrcToPacket();
  
  bool checkCrc32() const;
  
  void clearPacket();
  
  void printCrc();
  void printPacket();
  
  void updateFields();
  void updatePacketTable();
  
private:
  uint8_t m_Source;           //source/target ID
  uint8_t m_Module;           //module ID
  uint8_t m_Function;         //packet type
  uint8_t m_Parameter;        //parameter ID
  uint8_t m_Sign;             //sign of payload value, '1' - positive, '2' - negative
  uint8_t m_Length;           //length of payload
  uint8_t m_Payload[10];      //payload
  uint8_t m_Crc[4];           //32 bit CRC
  
  uint8_t m_PacketTable[PACKET_SIZE]; //table containing all fields data
};
#endif
