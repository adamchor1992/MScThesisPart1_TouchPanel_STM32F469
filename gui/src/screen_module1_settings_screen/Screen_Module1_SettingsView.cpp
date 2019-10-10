#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsView.hpp>
#include <gui/model/Model.hpp>
#include <string>

#define PAYLOAD_SIZE 10

Screen_Module1_SettingsView::Screen_Module1_SettingsView()
{
#ifndef SIMULATOR     
  uint16_t settableParameter1StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter2StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter3StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter4StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter5StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter6StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter7StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter8StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter9StringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t settableParameter10StringDisplay[PAYLOAD_SIZE] = { 0 };
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter1StringDisplay + i) = *(Model::m_SettableParameter1Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter2StringDisplay + i) = *(Model::m_SettableParameter2Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter3StringDisplay + i) = *(Model::m_SettableParameter3Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter4StringDisplay + i) = *(Model::m_SettableParameter4Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter5StringDisplay + i) = *(Model::m_SettableParameter5Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter6StringDisplay + i) = *(Model::m_SettableParameter6Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter7StringDisplay + i) = *(Model::m_SettableParameter7Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter8StringDisplay + i) = *(Model::m_SettableParameter8Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter9StringDisplay + i) = *(Model::m_SettableParameter9Name + i);
  }
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    *(settableParameter10StringDisplay + i) = *(Model::m_SettableParameter10Name + i);
  }
  
  Unicode::snprintf(textArea_SettableParameter1NameBuffer, TEXTAREA_SETTABLEPARAMETER1NAME_SIZE, "%s", settableParameter1StringDisplay);
  textArea_SettableParameter1Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter2NameBuffer, TEXTAREA_SETTABLEPARAMETER2NAME_SIZE, "%s", settableParameter2StringDisplay);
  textArea_SettableParameter2Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter3NameBuffer, TEXTAREA_SETTABLEPARAMETER3NAME_SIZE, "%s", settableParameter3StringDisplay);
  textArea_SettableParameter3Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter4NameBuffer, TEXTAREA_SETTABLEPARAMETER4NAME_SIZE, "%s", settableParameter4StringDisplay);
  textArea_SettableParameter4Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter5NameBuffer, TEXTAREA_SETTABLEPARAMETER5NAME_SIZE, "%s", settableParameter5StringDisplay);
  textArea_SettableParameter5Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter6NameBuffer, TEXTAREA_SETTABLEPARAMETER6NAME_SIZE, "%s", settableParameter6StringDisplay);
  textArea_SettableParameter6Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter7NameBuffer, TEXTAREA_SETTABLEPARAMETER7NAME_SIZE, "%s", settableParameter7StringDisplay);
  textArea_SettableParameter7Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter8NameBuffer, TEXTAREA_SETTABLEPARAMETER8NAME_SIZE, "%s", settableParameter8StringDisplay);
  textArea_SettableParameter8Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter9NameBuffer, TEXTAREA_SETTABLEPARAMETER9NAME_SIZE, "%s", settableParameter9StringDisplay);
  textArea_SettableParameter9Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter10NameBuffer, TEXTAREA_SETTABLEPARAMETER10NAME_SIZE, "%s", settableParameter10StringDisplay);
  textArea_SettableParameter10Name.invalidate();
#endif
}

void Screen_Module1_SettingsView::setupScreen()
{
#ifndef SIMULATOR
  NVIC_DisableIRQ(USART6_IRQn);
#endif
}

void Screen_Module1_SettingsView::tearDownScreen()
{
#ifndef SIMULATOR
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];

  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
}

void Screen_Module1_SettingsView::updateValueToSet(int value)
{
  float float_value = float(value) * 0.1;
  Unicode::snprintfFloat(textArea_ValueToSetBuffer, 6, "%.1f", float_value);
  textArea_ValueToSet.invalidate();
}

void Screen_Module1_SettingsView::setNewValue()
{
#ifndef SIMULATOR
  /*Structure used to propagate UART frame contents up to Model class*/
  UARTFrameStruct_t s_UARTFrame;
  
  uint16_t sliderValue;
  double sliderFloatValue;
  
  s_UARTFrame.source = '1';
  s_UARTFrame.module = '1';
  s_UARTFrame.function = '6';  //set parameter
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
  else if (radioButtonParameter5.getSelected())
  {
    s_UARTFrame.parameter = '5';
  }
  else if (radioButtonParameter6.getSelected())
  {
    s_UARTFrame.parameter = '6';
  }
  else if (radioButtonParameter7.getSelected())
  {
    s_UARTFrame.parameter = '7';
  }
  else if (radioButtonParameter8.getSelected())
  {
    s_UARTFrame.parameter = '8';
  }
  else if (radioButtonParameter9.getSelected())
  {
    s_UARTFrame.parameter = '9';
  }
  else if (radioButtonParameter10.getSelected())
  {
    s_UARTFrame.parameter = 'a';
  }
  
  s_UARTFrame.sign = '1'; //sign is always positive
  
  sliderValue = slider_Value.getValue();
  sliderFloatValue = double(sliderValue) * double(0.1);
  
  char data_chars[10] = {0}; //data starts from 6th element up to [6 + length] element
  
  sprintf(data_chars, "%.1lf", sliderFloatValue);
  
  uint8_t length_int = strlen(data_chars);
  
  s_UARTFrame.length = length_int + '0'; //convert to ASCII
  
  for (int i = 0; i < length_int; i++)
  {
    s_UARTFrame.payload[i] = data_chars[i];
  }
  
  this->presenter->notifyNewValueToSet(s_UARTFrame);
#endif
}

void Screen_Module1_SettingsView::enableParameterButtonPushed()
{
  /*Structure used to propagate UART frame contents up to Model class*/
  UARTFrameStruct_t s_UARTFrame;
  
  s_UARTFrame.source = '1';
  s_UARTFrame.module = '1';
  s_UARTFrame.function = '4';  //enable parameter
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
  else if (radioButtonParameter5.getSelected())
  {
    s_UARTFrame.parameter = '5';
  }
  else if (radioButtonParameter6.getSelected())
  {
    s_UARTFrame.parameter = '6';
  }
  else if (radioButtonParameter7.getSelected())
  {
    s_UARTFrame.parameter = '7';
  }
  else if (radioButtonParameter8.getSelected())
  {
    s_UARTFrame.parameter = '8';
  }
  else if (radioButtonParameter9.getSelected())
  {
    s_UARTFrame.parameter = '9';
  }
  else if (radioButtonParameter10.getSelected())
  {
    s_UARTFrame.parameter = 'a';
  }
  
  s_UARTFrame.sign = '1'; //sign is always positive
  s_UARTFrame.length = '1';
  s_UARTFrame.payload[6] = 0;
  
  this->presenter->notifyNewValueToSet(s_UARTFrame);
}

void Screen_Module1_SettingsView::disableParameterButtonPushed()
{
  /*Structure used to propagate UART frame contents up to Model class*/
  UARTFrameStruct_t s_UARTFrame;
  
  s_UARTFrame.source = '1';
  s_UARTFrame.module = '1';
  s_UARTFrame.function = '5';  //disable parameter
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
  else if (radioButtonParameter5.getSelected())
  {
    s_UARTFrame.parameter = '5';
  }
  else if (radioButtonParameter6.getSelected())
  {
    s_UARTFrame.parameter = '6';
  }
  else if (radioButtonParameter7.getSelected())
  {
    s_UARTFrame.parameter = '7';
  }
  else if (radioButtonParameter8.getSelected())
  {
    s_UARTFrame.parameter = '8';
  }
  else if (radioButtonParameter9.getSelected())
  {
    s_UARTFrame.parameter = '9';
  }
  else if (radioButtonParameter10.getSelected())
  {
    s_UARTFrame.parameter = 'a';
  }
  
  s_UARTFrame.sign = '1'; //sign is always positive
  s_UARTFrame.length = '1';
  s_UARTFrame.payload[6] = 0;
  
  this->presenter->notifyNewValueToSet(s_UARTFrame);
}

void Screen_Module1_SettingsView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}