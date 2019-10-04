#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugView.hpp>

Screen_UART_RX_DebugView::Screen_UART_RX_DebugView()
{
  
}

void Screen_UART_RX_DebugView::setupScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
}

void Screen_UART_RX_DebugView::tearDownScreen()
{
  
}

void Screen_UART_RX_DebugView::updateGUIFrameData(UARTFrameStruct_t & s_UARTFrame)
{
  Unicode::snprintf(textArea_SourceIDBuffer, TEXTAREA_SOURCEID_SIZE, "%c", s_UARTFrame.source);
  textArea_SourceID.invalidate();
  
  Unicode::snprintf(textArea_ModuleIDBuffer, TEXTAREA_MODULEID_SIZE, "%c", s_UARTFrame.module);
  textArea_ModuleID.invalidate();
  
  Unicode::snprintf(textArea_TypeIDBuffer, TEXTAREA_TYPEID_SIZE, "%c", s_UARTFrame.function);
  textArea_TypeID.invalidate();
  
  Unicode::snprintf(textArea_ParameterIDBuffer, TEXTAREA_PARAMETERID_SIZE, "%c", s_UARTFrame.parameter);
  textArea_ParameterID.invalidate();
  
  Unicode::snprintf(textArea_SignIDBuffer, TEXTAREA_SIGNID_SIZE, "%c", s_UARTFrame.sign);
  textArea_SignID.invalidate();
  
  //value displaying
  uint16_t stringToDisplay[10] = { 0 };
  
  s_UARTFrame.length = s_UARTFrame.length - '0'; //convert char to int length
  
  for (int i = 0; i < s_UARTFrame.length; i++)
  {
    *(stringToDisplay + i) = *(s_UARTFrame.payload + i);
  }
  
  Unicode::snprintf(textArea_ValueBuffer, s_UARTFrame.length + 1, "%s", stringToDisplay); //length + 1 because it is null-terminated string
  textArea_Value.invalidate();
}

void Screen_UART_RX_DebugView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}