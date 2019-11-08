#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "UART_Frame_Struct.h"

class ModelListener
{
public:
  ModelListener() : model(0) {}
  
  virtual void notifyAllInitFrameReceived(UARTFrameStruct_t & s_UARTFrame) {}
  virtual void notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame) {}
  virtual void notifyNewGraphRange(UARTFrameStruct_t & s_UARTFrame) {}
  virtual void notifyNewUART_TX_Value(uint8_t* newValue) {}
  virtual void notifyNewCpuUsageValue(uint8_t value) {}
  
  virtual ~ModelListener() {}
  
  void bind(Model* m)
  {
    model = m;
  }
  
protected:
  Model* model;
};

#endif /* MODELLISTENER_HPP */
