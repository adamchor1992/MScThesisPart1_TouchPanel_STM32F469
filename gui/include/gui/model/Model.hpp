#pragma once

#include <touchgfx/Utils.hpp>
#include "uart_packet.h"

#ifndef SIMULATOR
#include <stm32f4xx_hal_uart.h>
#endif

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
  
  void SetNewValueToSet(UartPacket const& uartPacket);
  
  /*Module 1 initialization parameters*/  
  static uint8_t m_InitParametersModule1[INIT_PACKETS_COUNT][PAYLOAD_SIZE];
  
  /*Module 2 initialization parameters*/
  static uint8_t m_InitParametersModule2[INIT_PACKETS_COUNT][PAYLOAD_SIZE];
  
  /*Module 3 initialization parameters*/
  static uint8_t m_InitParametersModule3[INIT_PACKETS_COUNT][PAYLOAD_SIZE];
  
  static void ActivateModule(ModuleID module);
  static void DeactivateModule(ModuleID module);
  static bool IsModuleActive(ModuleID module);
  
#ifndef SIMULATOR
  static UART_HandleTypeDef* m_pHuart6;
#endif
  
protected:
  /*Pointer to the currently active presenter*/
  ModelListener* m_ModelListener;
  
private:
  void ProcessPacket(UartPacket& uartPacket, ModuleID module);
  
  uint8_t m_ReceivedInitPacketCount;
  
  static bool module1Connected;
  static bool module2Connected;
  static bool module3Connected;
};