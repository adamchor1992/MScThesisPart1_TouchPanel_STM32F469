#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/Utils.hpp>
#include "UART_Frame_Struct.h"

#ifndef SIMULATOR
#include <stm32f4xx_hal_uart.h>
#endif

#define PAYLOAD_SIZE 10

class ModelListener;

/**
* The Model class defines the data model in the model-view-presenter paradigm.
* The Model is a singular object used across all presenters. The currently active
* presenter will have a pointer to the Model through deriving from ModelListener.
*
* The Model will typically contain UI state information that must be kept alive
* through screen transitions. It also usually provides the interface to the rest
* of the system (the backend). As such, the Model can receive events and data from
* the backend and inform the current presenter of such events through the modelListener
* pointer, which is automatically configured to point to the current presenter.
* Conversely, the current presenter can trigger events in the backend through the Model.
*/
class Model
{
public:
  Model();
  
  /**
  * Sets the modelListener to point to the currently active presenter. Called automatically
  * when switching screen.
  */
  void bind(ModelListener* listener)
  {
    modelListener = listener;
  }
  
  /**
  * This function will be called automatically every frame. Can be used to e.g. sample hardware
  * peripherals or read events from the surrounding system and inject events to the GUI through
  * the ModelListener interface.
  */
  void tick();
  void setNewValueToSet(UARTFrameStruct_t & s_UARTFrame);
  
  /*Data needed to initialize Info screen specifications*/
  static uint8_t m_vendor[PAYLOAD_SIZE];
  static uint8_t m_type[PAYLOAD_SIZE];
  static uint8_t m_model[PAYLOAD_SIZE];
  static uint8_t m_speed[PAYLOAD_SIZE];
  static uint8_t m_version[PAYLOAD_SIZE];
  
  static uint8_t m_vendorStringLength;
  static uint8_t m_typeStringLength;
  static uint8_t m_modelStringLength;
  static uint8_t m_speedStringLength;
  static uint8_t m_versionStringLength;
  
  /*Parameter names*/
  static uint8_t m_parameter1Name[PAYLOAD_SIZE];
  static uint8_t m_parameter2Name[PAYLOAD_SIZE];
  static uint8_t m_parameter3Name[PAYLOAD_SIZE];
  static uint8_t m_parameter4Name[PAYLOAD_SIZE];
  
  static uint8_t m_parameter1NameLength;
  static uint8_t m_parameter2NameLength;
  static uint8_t m_parameter3NameLength;
  static uint8_t m_parameter4NameLength;
  
protected:
  /**
  * Pointer to the currently active presenter.
  */
  ModelListener* modelListener;
private:
#ifndef SIMULATOR
  UART_HandleTypeDef m_huart6;
  uint8_t *receivedUART_TXValue;
  uint8_t initFrameCount;
#endif
};

#endif /* MODEL_HPP */
