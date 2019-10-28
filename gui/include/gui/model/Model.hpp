#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/Utils.hpp>
#include "UART_Frame_Struct.h"

#ifndef SIMULATOR
#include <stm32f4xx_hal_uart.h>
#endif

#define PAYLOAD_SIZE 10
#define INIT_FRAME_COUNT 24
#define INIT_PARAMETER_NAME_COUNT 5
#define INIT_PARAMETER_NAME_OFFSET 0
#define INIT_PARAMETER_VALUE_COUNT 5
#define INIT_PARAMETER_VALUE_OFFSET 5
#define CUSTOM_PARAMETER_NAME_COUNT 4
#define CUSTOM_PARAMETER_NAME_OFFSET 10
#define SETTABLE_PARAMETER_NAME_COUNT 10
#define SETTABLE_PARAMETER_NAME_OFFSET 14

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
  void setNewValueToSet(const UARTFrameStruct_t & frameStructure);
    
  /*Module 1 initialization parameters*/  
  static uint8_t m_InitParametersModule1[INIT_FRAME_COUNT][PAYLOAD_SIZE];
  
  /*Module 2 initialization parameters*/
  static uint8_t m_InitParametersModule2[INIT_FRAME_COUNT][PAYLOAD_SIZE];
  
  /*Module 3 initialization parameters*/
  static uint8_t m_InitParametersModule3[INIT_FRAME_COUNT][PAYLOAD_SIZE];

  static void activateModule(int module);
  static void deactivateModule(int module);
  static bool isModuleActive(int module);
  
#ifndef SIMULATOR
  static UART_HandleTypeDef* m_pHuart6;
#endif
  
protected:
  /**
  * Pointer to the currently active presenter.
  */
  ModelListener* m_ModelListener;
private:
#ifndef SIMULATOR
  uint8_t* mp_ReceivedUART_TXValue;
  uint8_t m_ReceivedInitFrameCount;
  static bool module1Connected;
  static bool module2Connected;
  static bool module3Connected;
#endif
};

#endif /* MODEL_HPP */
