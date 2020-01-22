#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/Utils.hpp>
#include "uart_packet.h"

#ifndef SIMULATOR
#include <stm32f4xx_hal_uart.h>
#endif

#define PAYLOAD_SIZE 10
#define INIT_PACKET_COUNT 28
#define INIT_PARAMETER_NAME_COUNT 5
#define INIT_PARAMETER_NAME_OFFSET 0
#define INIT_PARAMETER_VALUE_COUNT 5
#define INIT_PARAMETER_VALUE_OFFSET 5
#define CUSTOM_PARAMETER_NAME_COUNT 4
#define CUSTOM_PARAMETER_NAME_OFFSET 10
#define CUSTOM_PARAMETER_VALUE_COUNT 4
#define CUSTOM_PARAMETER_VALUE_OFFSET 14
#define SETTABLE_PARAMETER_NAME_COUNT 10
#define SETTABLE_PARAMETER_NAME_OFFSET 18

class ModelListener;

class Model
{
public:
  Model();
  
  void bind(ModelListener* listener)
  {
    m_ModelListener = listener;
  }
  
  void tick();
  
  void setNewValueToSet(const UartPacket & uartPacket);
  
  /*Module 1 initialization parameters*/  
  static uint8_t m_InitParametersModule1[INIT_PACKET_COUNT][PAYLOAD_SIZE];
  
  /*Module 2 initialization parameters*/
  static uint8_t m_InitParametersModule2[INIT_PACKET_COUNT][PAYLOAD_SIZE];
  
  /*Module 3 initialization parameters*/
  static uint8_t m_InitParametersModule3[INIT_PACKET_COUNT][PAYLOAD_SIZE];
  
  static void activateModule(ModuleID module);
  static void deactivateModule(ModuleID module);
  static bool isModuleActive(ModuleID module);
  
#ifndef SIMULATOR
  static UART_HandleTypeDef* m_pHuart6;
#endif
  
protected:
  /*Pointer to the currently active presenter*/
  ModelListener* m_ModelListener;
  
private:
  void processPacket(UartPacket& uartPacket, ModuleID module);
  
  uint8_t m_ReceivedInitPacketCount;
  static bool module1Connected;
  static bool module2Connected;
  static bool module3Connected;
};
#endif