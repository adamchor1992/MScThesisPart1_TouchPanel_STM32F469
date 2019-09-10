#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsView.hpp>

Screen_Module1_SettingsView::Screen_Module1_SettingsView()
{

}

void Screen_Module1_SettingsView::setupScreen()
{
    Screen_Module1_SettingsViewBase::setupScreen();
    
	#ifndef SIMULATOR
    NVIC_DisableIRQ(USART6_IRQn);
    #endif
    
}

void Screen_Module1_SettingsView::tearDownScreen()
{
    Screen_Module1_SettingsViewBase::tearDownScreen();
    
	#ifndef SIMULATOR
    extern UART_HandleTypeDef huart6;
    extern uint8_t UART_ReceivedFrame[FRAME_SIZE];
    
    HAL_UART_DeInit(&huart6);
    HAL_UART_Init(&huart6);
    
    NVIC_EnableIRQ(USART6_IRQn);
    
    HAL_UART_Receive_IT(&huart6, UART_ReceivedFrame, FRAME_SIZE);
	#endif
}

void Screen_Module1_SettingsView::updateValueToSet(int value)
{
  Unicode::itoa(value, textArea_ValueToSetBuffer, TEXTAREA_VALUETOSET_SIZE, 10);
  textArea_ValueToSet.setWildcard(textArea_ValueToSetBuffer);
  textArea_ValueToSet.invalidate();
}

void Screen_Module1_SettingsView::setNewValue()
{
  /*Structure used to propagate UART frame contents up to Model class*/
  UARTFrameStruct_t s_UARTFrame;
  
  s_UARTFrame.source = '1';
  s_UARTFrame.module = '1';
  s_UARTFrame.type = '2';  //data frame type
  s_UARTFrame.parameter = '0'; //this should be overwritten by following instructions
  
  if (radioButtonParameter1.getSelected())
  {
    s_UARTFrame.parameter = '1';
  }
  else if (radioButtonParameter2.getSelected())
  {
    s_UARTFrame.parameter = '2';
  }
  else if (radioButtonParameter3.getSelected())
  {
    s_UARTFrame.parameter = '3';
  }
  else if (radioButtonParameter4.getSelected())
  {
    s_UARTFrame.parameter = '4';
  }
  
  s_UARTFrame.sign = '1'; //sign is always positive
    
  uint8_t sliderValue = slider_Value.getValue();
  
  if (sliderValue < 10)
    s_UARTFrame.length = '1';
  else if (sliderValue < 100)
    s_UARTFrame.length = '2';
  else if (sliderValue >= 100)
    s_UARTFrame.length = '3';
  else
    s_UARTFrame.length = '9'; //error
  
  #ifndef SIMULATOR
  char data_chars[10] = { 255, 255, 255, 255, 255, 255 }; //data starts from 6th element up to [6 + length] element
  
  sprintf(data_chars, "%d", sliderValue);
  
  for (int i = 0; i < 10; i++)
  {
    s_UARTFrame.payload[i] = data_chars[i];
  }
  #endif
  
  this->presenter->notifyNewValueToSet(s_UARTFrame);
}

void Screen_Module1_SettingsView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}