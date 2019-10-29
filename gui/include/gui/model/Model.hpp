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

class Model
{
public:
  Model();
  
  /*Sets the m_ModelListener to point to the currently active presenter. Called automatically*/
  void bind(ModelListener* listener)
  {
    m_ModelListener = listener;
  }
  
  /*This function will be called automatically every frame*/
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
  /*Pointer to the currently active presenter*/
  ModelListener* m_ModelListener;
  
private:
  void processPacket(int module);
  
  uint8_t* mp_ReceivedUART_TXValue;
  uint8_t m_ReceivedInitFrameCount;
  static bool module1Connected;
  static bool module2Connected;
  static bool module3Connected;
};

#endif /* MODEL_HPP */
