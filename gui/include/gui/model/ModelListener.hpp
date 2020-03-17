#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "uart_packet.h"

class ModelListener
{
public:
  ModelListener() : model(0) {}
  
  virtual void NotifyAllInitPacketsReceived(UartPacket& uartPacket) {}
  virtual void NotifyNewUartRxParsedPacket(UartPacket& uartPacket) {}
  virtual void NotifyNewGraphRange(UartPacket& uartPacket) {}
  virtual void NotifyNewUartTxValue(uint8_t* newValue) {}
  virtual void NotifyNewCpuUsageValue(uint8_t value) {}
  
  virtual ~ModelListener() {}
  
  void bind(Model* m)
  {
    model = m;
  }
  
protected:
  Model* model;
};

#endif
