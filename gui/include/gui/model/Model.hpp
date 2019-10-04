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
  * Sets the m_ModelListener to point to the currently active presenter. Called automatically
  * when switching screen.
  */
  void bind(ModelListener* listener)
  {
    m_ModelListener = listener;
  }
  
  /**
  * This function will be called automatically every frame. Can be used to e.g. sample hardware
  * peripherals or read events from the surrounding system and inject events to the GUI through
  * the ModelListener interface.
  */
  void tick();
  void setNewValueToSet(UARTFrameStruct_t & s_UARTFrame);
  
  /*Module initialization parameter names*/
  static uint8_t m_InitParameter1Name[PAYLOAD_SIZE];
  static uint8_t m_InitParameter2Name[PAYLOAD_SIZE];
  static uint8_t m_InitParameter3Name[PAYLOAD_SIZE];
  static uint8_t m_InitParameter4Name[PAYLOAD_SIZE];
  static uint8_t m_InitParameter5Name[PAYLOAD_SIZE];
  
  static uint8_t m_InitParameter1NameStringLength;
  static uint8_t m_InitParameter2NameStringLength;
  static uint8_t m_InitParameter3NameStringLength;
  static uint8_t m_InitParameter4NameStringLength;
  static uint8_t m_InitParameter5NameStringLength;
  
  /*Module initialization parameter values*/
  static uint8_t m_InitParameter1Value[PAYLOAD_SIZE];
  static uint8_t m_InitParameter2Value[PAYLOAD_SIZE];
  static uint8_t m_InitParameter3Value[PAYLOAD_SIZE];
  static uint8_t m_InitParameter4Value[PAYLOAD_SIZE];
  static uint8_t m_InitParameter5Value[PAYLOAD_SIZE];
  
  static uint8_t m_InitParameter1ValueStringLength;
  static uint8_t m_InitParameter2ValueStringLength;
  static uint8_t m_InitParameter3ValueStringLength;
  static uint8_t m_InitParameter4ValueStringLength;
  static uint8_t m_InitParameter5ValueStringLength;
  
  /*Custom parameter names*/
  static uint8_t m_Parameter1Name[PAYLOAD_SIZE];
  static uint8_t m_Parameter2Name[PAYLOAD_SIZE];
  static uint8_t m_Parameter3Name[PAYLOAD_SIZE];
  static uint8_t m_Parameter4Name[PAYLOAD_SIZE];
  
  static uint8_t m_Parameter1NameLength;
  static uint8_t m_Parameter2NameLength;
  static uint8_t m_Parameter3NameLength;
  static uint8_t m_Parameter4NameLength;
  
  /*Settable parameter names*/
  static uint8_t m_SettableParameter1Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter2Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter3Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter4Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter5Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter6Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter7Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter8Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter9Name[PAYLOAD_SIZE];
  static uint8_t m_SettableParameter10Name[PAYLOAD_SIZE];
  
  static uint8_t m_SettableParameter1NameLength;
  static uint8_t m_SettableParameter2NameLength;
  static uint8_t m_SettableParameter3NameLength;
  static uint8_t m_SettableParameter4NameLength;
  static uint8_t m_SettableParameter5NameLength;
  static uint8_t m_SettableParameter6NameLength;
  static uint8_t m_SettableParameter7NameLength;
  static uint8_t m_SettableParameter8NameLength;
  static uint8_t m_SettableParameter9NameLength;
  static uint8_t m_SettableParameter10NameLength;
  
  static uint8_t m_ActiveModule;
  static UART_HandleTypeDef* m_pHuart6;
  
protected:
  /**
  * Pointer to the currently active presenter.
  */
  ModelListener* m_ModelListener;
private:
#ifndef SIMULATOR
  uint8_t* mp_ReceivedUART_TXValue;
  uint8_t m_ReceivedInitFrameCount;
  uint8_t m_ConnectionState;
  enum m_ConnectionStates {UNCONNECTED, CONNECTED};
#endif
};

#endif /* MODEL_HPP */
