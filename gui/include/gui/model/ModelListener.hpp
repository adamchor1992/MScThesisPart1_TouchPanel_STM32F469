#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "uart_packet.h"

class ModelListener
{
public:
  ModelListener() : model(0) {}
  
  virtual void notifyAllInitPacketsReceived(UartPacket& uartPacket) {}
  virtual void notifyNewUartRxParsedPacket(UartPacket& uartPacket) {}
  virtual void notifyNewGraphRange(UartPacket& uartPacket) {}
  virtual void notifyNewUartTxValue(uint8_t* newValue) {}
  virtual void notifyNewCpuUsageValue(uint8_t value) {}
  
  virtual ~ModelListener() {}
  
  void bind(Model* m)
  {
    model = m;
  }
  
protected:
  Model* model;
};

#endif
