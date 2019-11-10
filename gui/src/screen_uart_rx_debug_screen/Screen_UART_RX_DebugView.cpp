#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugView.hpp>

Screen_UART_RX_DebugView::Screen_UART_RX_DebugView()
{
  
}

void Screen_UART_RX_DebugView::setupScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern UartPacket uartPacket;
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, uartPacket.getPacketTable(), PACKET_SIZE);
#endif
}

void Screen_UART_RX_DebugView::tearDownScreen()
{
  
}

void Screen_UART_RX_DebugView::updateGuiPacketData(UartPacket & uartPacket)
{
  Unicode::snprintf(textArea_SourceIDBuffer, TEXTAREA_SOURCEID_SIZE, "%c", uartPacket.getSource());
  textArea_SourceID.invalidate();
  
  Unicode::snprintf(textArea_ModuleIDBuffer, TEXTAREA_MODULEID_SIZE, "%c", uartPacket.getModule());
  textArea_ModuleID.invalidate();
  
  Unicode::snprintf(textArea_TypeIDBuffer, TEXTAREA_TYPEID_SIZE, "%c", uartPacket.getFunction());
  textArea_TypeID.invalidate();
  
  Unicode::snprintf(textArea_ParameterIDBuffer, TEXTAREA_PARAMETERID_SIZE, "%c", uartPacket.getParameter());
  textArea_ParameterID.invalidate();
  
  Unicode::snprintf(textArea_SignIDBuffer, TEXTAREA_SIGNID_SIZE, "%c", uartPacket.getSign());
  textArea_SignID.invalidate();
  
  uint16_t stringToDisplay[10] = { 0 };
  
  uint8_t lengthInt = uartPacket.getLength();
  
  for (int i = 0; i < lengthInt; i++)
  {
    stringToDisplay[i] = uartPacket.getPayload()[i];
  }
  
  /*lengthInt + 1 because it is null-terminated string*/
  Unicode::snprintf(textArea_ValueBuffer, lengthInt + 1, "%s", stringToDisplay); 
  textArea_Value.invalidate();
}

void Screen_UART_RX_DebugView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}