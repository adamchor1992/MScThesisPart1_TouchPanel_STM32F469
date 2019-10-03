#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/Utils.hpp>
#include "UART_Frame_Struct.h"

#ifndef SIMULATOR
#include <stm32f4xx_hal_uart.h>
#endif

#define PAYLOAD_SIZE 10
#define INIT_FRAME_COUNT 24

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
  
  /*Module initialization parameter names*/
  static uint8_t m_initParameter1Name[PAYLOAD_SIZE];
  static uint8_t m_initParameter2Name[PAYLOAD_SIZE];
  static uint8_t m_initParameter3Name[PAYLOAD_SIZE];
  static uint8_t m_initParameter4Name[PAYLOAD_SIZE];
  static uint8_t m_initParameter5Name[PAYLOAD_SIZE];
  
  static uint8_t m_initParameter1NameStringLength;
  static uint8_t m_initParameter2NameStringLength;
  static uint8_t m_initParameter3NameStringLength;
  static uint8_t m_initParameter4NameStringLength;
  static uint8_t m_initParameter5NameStringLength;
  
  /*Module initialization parameter values*/
  static uint8_t m_initParameter1Value[PAYLOAD_SIZE];
  static uint8_t m_initParameter2Value[PAYLOAD_SIZE];
  static uint8_t m_initParameter3Value[PAYLOAD_SIZE];
  static uint8_t m_initParameter4Value[PAYLOAD_SIZE];
  static uint8_t m_initParameter5Value[PAYLOAD_SIZE];
  
  static uint8_t m_initParameter1ValueStringLength;
  static uint8_t m_initParameter2ValueStringLength;
  static uint8_t m_initParameter3ValueStringLength;
  static uint8_t m_initParameter4ValueStringLength;
  static uint8_t m_initParameter5ValueStringLength;
  
  /*Custom parameter names*/
  static uint8_t m_parameter1Name[PAYLOAD_SIZE];
  static uint8_t m_parameter2Name[PAYLOAD_SIZE];
  static uint8_t m_parameter3Name[PAYLOAD_SIZE];
  static uint8_t m_parameter4Name[PAYLOAD_SIZE];
  
  static uint8_t m_parameter1NameLength;
  static uint8_t m_parameter2NameLength;
  static uint8_t m_parameter3NameLength;
  static uint8_t m_parameter4NameLength;
  
  /*Settable parameter names*/
  static uint8_t m_settableParameter1Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter2Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter3Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter4Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter5Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter6Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter7Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter8Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter9Name[PAYLOAD_SIZE];
  static uint8_t m_settableParameter10Name[PAYLOAD_SIZE];
  
  static uint8_t m_settableParameter1NameLength;
  static uint8_t m_settableParameter2NameLength;
  static uint8_t m_settableParameter3NameLength;
  static uint8_t m_settableParameter4NameLength;
  static uint8_t m_settableParameter5NameLength;
  static uint8_t m_settableParameter6NameLength;
  static uint8_t m_settableParameter7NameLength;
  static uint8_t m_settableParameter8NameLength;
  static uint8_t m_settableParameter9NameLength;
  static uint8_t m_settableParameter10NameLength;
  
protected:
  /**
  * Pointer to the currently active presenter.
  */
  ModelListener* modelListener;
private:
#ifndef SIMULATOR
  UART_HandleTypeDef m_huart6;
  uint8_t* mp_receivedUART_TXValue;
  uint8_t m_receivedInitFrameCount;
  uint8_t m_connectionState;
  enum m_connectionStates {UNCONNECTED, CONNECTED};
  #endif
};

#endif /* MODEL_HPP */
