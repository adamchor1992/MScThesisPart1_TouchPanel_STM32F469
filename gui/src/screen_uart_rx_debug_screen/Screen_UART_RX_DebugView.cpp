#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugView.hpp>

Screen_UART_RX_DebugView::Screen_UART_RX_DebugView()
{
  
}

void Screen_UART_RX_DebugView::setupScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern uint8_t uartReceivedPacket[PACKET_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, uartReceivedPacket, PACKET_SIZE);
#endif
}

void Screen_UART_RX_DebugView::tearDownScreen()
{
  
}

void Screen_UART_RX_DebugView::updateGuiPacketData(UartPacket & uartPacket)
{
  Unicode::snprintf(textArea_SourceIDBuffer, TEXTAREA_SOURCEID_SIZE, "%c", uartPacket.source);
  textArea_SourceID.invalidate();
  
  Unicode::snprintf(textArea_ModuleIDBuffer, TEXTAREA_MODULEID_SIZE, "%c", uartPacket.module);
  textArea_ModuleID.invalidate();
  
  Unicode::snprintf(textArea_TypeIDBuffer, TEXTAREA_TYPEID_SIZE, "%c", uartPacket.function);
  textArea_TypeID.invalidate();
  
  Unicode::snprintf(textArea_ParameterIDBuffer, TEXTAREA_PARAMETERID_SIZE, "%c", uartPacket.parameter);
  textArea_ParameterID.invalidate();
  
  Unicode::snprintf(textArea_SignIDBuffer, TEXTAREA_SIGNID_SIZE, "%c", uartPacket.sign);
  textArea_SignID.invalidate();
  
  //value displaying
  uint16_t stringToDisplay[10] = { 0 };
  
  uartPacket.length = uartPacket.length - '0'; //convert char to int length
  
  for (int i = 0; i < uartPacket.length; i++)
  {
    stringToDisplay[i] = uartPacket.payload[i];
  }
  
  Unicode::snprintf(textArea_ValueBuffer, uartPacket.length + 1, "%s", stringToDisplay); //length + 1 because it is null-terminated string
  textArea_Value.invalidate();
}

void Screen_UART_RX_DebugView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}