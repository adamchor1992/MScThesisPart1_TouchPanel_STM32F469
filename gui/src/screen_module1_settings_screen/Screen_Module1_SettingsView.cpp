#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsView.hpp>
#include <gui/model/Model.hpp>
#include <string>
#include <cmath>

Screen_Module1_SettingsView::Screen_Module1_SettingsView()
{
#ifndef SIMULATOR     
  uint16_t settableParameterStringDisplay[SETTABLE_PARAMETER_NAME_COUNT][PAYLOAD_SIZE] = { 0 };
  
  for(int i=0; i< SETTABLE_PARAMETER_NAME_COUNT; i++)
  {
    for (int character = 0; character < PAYLOAD_SIZE; character++)
    {
      settableParameterStringDisplay[i][character] = Model::m_InitParametersModule1[i + SETTABLE_PARAMETER_NAME_OFFSET][character];
    }
  }
  
  Unicode::snprintf(textArea_SettableParameter1NameBuffer, TEXTAREA_SETTABLEPARAMETER1NAME_SIZE, "%s", settableParameterStringDisplay[0]);
  textArea_SettableParameter1Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter2NameBuffer, TEXTAREA_SETTABLEPARAMETER2NAME_SIZE, "%s", settableParameterStringDisplay[1]);
  textArea_SettableParameter2Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter3NameBuffer, TEXTAREA_SETTABLEPARAMETER3NAME_SIZE, "%s", settableParameterStringDisplay[2]);
  textArea_SettableParameter3Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter4NameBuffer, TEXTAREA_SETTABLEPARAMETER4NAME_SIZE, "%s", settableParameterStringDisplay[3]);
  textArea_SettableParameter4Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter5NameBuffer, TEXTAREA_SETTABLEPARAMETER5NAME_SIZE, "%s", settableParameterStringDisplay[4]);
  textArea_SettableParameter5Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter6NameBuffer, TEXTAREA_SETTABLEPARAMETER6NAME_SIZE, "%s", settableParameterStringDisplay[5]);
  textArea_SettableParameter6Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter7NameBuffer, TEXTAREA_SETTABLEPARAMETER7NAME_SIZE, "%s", settableParameterStringDisplay[6]);
  textArea_SettableParameter7Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter8NameBuffer, TEXTAREA_SETTABLEPARAMETER8NAME_SIZE, "%s", settableParameterStringDisplay[7]);
  textArea_SettableParameter8Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter9NameBuffer, TEXTAREA_SETTABLEPARAMETER9NAME_SIZE, "%s", settableParameterStringDisplay[8]);
  textArea_SettableParameter9Name.invalidate();
  Unicode::snprintf(textArea_SettableParameter10NameBuffer, TEXTAREA_SETTABLEPARAMETER10NAME_SIZE, "%s", settableParameterStringDisplay[9]);
  textArea_SettableParameter10Name.invalidate();
#endif
  
  scrollWheel_Digit1.initialize();
  scrollWheel_Digit2.initialize();
  scrollWheel_Digit3.initialize();
  scrollWheel_Digit4.initialize();
  scrollWheel_Digit5.initialize();
  scrollWheel_Digit6.initialize();
  scrollWheel_Digit7.initialize();
  scrollWheel_Digit8.initialize();
  scrollWheel_Digit9.initialize();
  scrollWheel_Digit10.initialize();
}

void Screen_Module1_SettingsView::setupScreen()
{
  /*Disable UART interrupts for this screen*/
#ifndef SIMULATOR
  NVIC_DisableIRQ(USART6_IRQn);
#endif
}

void Screen_Module1_SettingsView::tearDownScreen()
{
  /*Reenable UART interrupts when leaving this screen*/
#ifndef SIMULATOR
  extern UartPacket uartPacket;
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, uartPacket.GetPacketTable(), PACKET_SIZE);
#endif
}

void Screen_Module1_SettingsView::SetNewValue()
{
#ifndef SIMULATOR
  UartPacket uartPacket;
  
  uartPacket.SetSource(Source::SOURCE_TARGET1);
  uartPacket.SetModule(ModuleID::MODULE1);
  uartPacket.SetFunction(Function::SET_PARAMETER_PACKET);
  
  if (radioButtonParameter1.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER1);
  }
  else if (radioButtonParameter2.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER2);
  }
  else if (radioButtonParameter3.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER3);
  }
  else if (radioButtonParameter4.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER4);
  }
  else if (radioButtonParameter5.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER5);
  }
  else if (radioButtonParameter6.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER6);
  }
  else if (radioButtonParameter7.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER7);
  }
  else if (radioButtonParameter8.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER8);
  }
  else if (radioButtonParameter9.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER9);
  }
  else if (radioButtonParameter10.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER10);
  }
  
  if(radioButton_Plus.getSelected())
  {
    /*Value is positive*/
    uartPacket.SetSign(Sign::POSITIVE_SIGN);
  }
  else if(radioButton_Minus.getSelected())
  {
    /*Value is negative*/
    uartPacket.SetSign(Sign::NEGATIVE_SIGN);
  }
  
  /*Position 0 is '.', position 1 is digit 0, position 2 is digit 1 and so on*/
  int scrollWheelPositions[PAYLOAD_SIZE] = { 0 };
  
  GetScrollWheelsPositions(scrollWheelPositions);
  
  char scrollWheelsAsciiValues[PAYLOAD_SIZE] = { 0 };
  
  TranslateScrollWheelPositionsToAsciiValues(scrollWheelPositions, scrollWheelsAsciiValues);
  
  /*Send all 10 bytes*/;
  uartPacket.SetLength(PAYLOAD_SIZE);
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    uartPacket.SetPayload()[i] = scrollWheelsAsciiValues[i];
  }
  
  this->presenter->NotifyNewValueToSet(uartPacket);
#endif
}

void Screen_Module1_SettingsView::GetScrollWheelsPositions(int positions[])
{
  positions[9] = scrollWheel_Digit1.getSelectedItem();
  positions[8] = scrollWheel_Digit2.getSelectedItem();
  positions[7] = scrollWheel_Digit3.getSelectedItem();
  positions[6] = scrollWheel_Digit4.getSelectedItem();
  positions[5] = scrollWheel_Digit5.getSelectedItem();
  positions[4] = scrollWheel_Digit6.getSelectedItem();
  positions[3] = scrollWheel_Digit7.getSelectedItem();
  positions[2] = scrollWheel_Digit8.getSelectedItem();
  positions[1] = scrollWheel_Digit9.getSelectedItem();
  positions[0] = scrollWheel_Digit10.getSelectedItem();
}

void Screen_Module1_SettingsView::TranslateScrollWheelPositionsToAsciiValues(const int positions[], char values[])
{
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    switch (positions[i])
    {
    case 0:
      values[i] = '.';
      break;
    case 1:
      values[i] = '0';
      break;
    case 2:
      values[i] = '1';
      break;
    case 3:
      values[i] = '2';
      break;
    case 4:
      values[i] = '3';
      break;
    case 5:
      values[i] = '4';
      break;
    case 6:
      values[i] = '5';
      break;
    case 7:
      values[i] = '6';
      break;
    case 8:
      values[i] = '7';
      break;
    case 9:
      values[i] = '8';
      break;
    case 10:
      values[i] = '9';
      break;
    }
  }
}

void Screen_Module1_SettingsView::EnableParameterButtonPushed()
{
  /*Structure used to propagate UART packet contents up to Model class*/
  UartPacket uartPacket;
  
  uartPacket.SetSource(Source::SOURCE_TARGET1);
  uartPacket.SetModule(ModuleID::MODULE1);
  uartPacket.SetFunction(Function::ENABLE_PARAMETER_PACKET);
  
  if (radioButtonParameter1.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER1);
  }
  else if (radioButtonParameter2.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER2);
  }
  else if (radioButtonParameter3.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER3);
  }
  else if (radioButtonParameter4.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER4);
  }
  else if (radioButtonParameter5.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER5);
  }
  else if (radioButtonParameter6.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER6);
  }
  else if (radioButtonParameter7.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER7);
  }
  else if (radioButtonParameter8.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER8);
  }
  else if (radioButtonParameter9.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER9);
  }
  else if (radioButtonParameter10.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER10);
  }
  
  uartPacket.SetSign(Sign::POSITIVE_SIGN);
  uartPacket.SetLength(Length::NO_PAYLOAD);
  
  this->presenter->NotifyNewValueToSet(uartPacket);
}

void Screen_Module1_SettingsView::DisableParameterButtonPushed()
{
  /*Structure used to propagate UART packet contents up to Model class*/
  UartPacket uartPacket;
  
  uartPacket.SetSource(Source::SOURCE_TARGET1);
  uartPacket.SetModule(ModuleID::MODULE1);
  uartPacket.SetFunction(Function::DISABLE_PARAMETER_PACKET);
  
  if (radioButtonParameter1.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER1);
  }
  else if (radioButtonParameter2.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER2);
  }
  else if (radioButtonParameter3.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER3);
  }
  else if (radioButtonParameter4.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER4);
  }
  else if (radioButtonParameter5.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER5);
  }
  else if (radioButtonParameter6.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER6);
  }
  else if (radioButtonParameter7.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER7);
  }
  else if (radioButtonParameter8.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER8);
  }
  else if (radioButtonParameter9.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER9);
  }
  else if (radioButtonParameter10.getSelected())
  {
    uartPacket.SetParameter(Parameter::PARAMETER10);
  }
  
  uartPacket.SetSign(Sign::POSITIVE_SIGN);
  uartPacket.SetLength(Length::NO_PAYLOAD);
  
  this->presenter->NotifyNewValueToSet(uartPacket);
}

void Screen_Module1_SettingsView::UpdateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}

void Screen_Module1_SettingsView::scrollWheel_Digit1UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit2UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit3UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit4UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit5UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit6UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit7UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit8UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit9UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit10UpdateItem(DigitTemplate& item, int16_t itemIndex)
{
  item.SetDigitWithComma(itemIndex);
}