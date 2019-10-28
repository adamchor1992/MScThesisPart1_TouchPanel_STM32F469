#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "UART_Frame_Struct.h"

/**
* ModelListener is the interface through which the Model can inform the currently
* active presenter of events. All presenters should derive from this class.
* It also provides a model pointer for the presenter to interact with the Model.
*
* The bind function is called automatically.
*
* Add the virtual functions Model should be able to call on the active presenter to this class.
*/
class ModelListener
{
public:
  ModelListener() : model(0) {}
  
  virtual void notifyAllInitFrameReceived(UARTFrameStruct_t & s_UARTFrame) {}
  virtual void notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame) {}
  virtual void notifyNewUART_TX_Value(uint8_t *newValue) {}
  virtual void notifyNewCpuUsageValue(uint8_t value) {}
  
  virtual ~ModelListener() {}
  
  /**
  * Sets the model pointer to point to the Model object. Called automatically
  * when switching screen.
  */
  void bind(Model* m)
  {
    model = m;
  }
protected:
  Model* model;
};

#endif /* MODELLISTENER_HPP */
