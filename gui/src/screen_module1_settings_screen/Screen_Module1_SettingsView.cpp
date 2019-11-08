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
#ifndef SIMULATOR
  NVIC_DisableIRQ(USART6_IRQn);
#endif
}

void Screen_Module1_SettingsView::tearDownScreen()
{
#ifndef SIMULATOR
  extern uint8_t uartReceivedPacket[PACKET_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, uartReceivedPacket, PACKET_SIZE);
#endif
}

void Screen_Module1_SettingsView::setNewValue()
{
#ifndef SIMULATOR
  /*Structure used to propagate UART packet contents up to Model class*/
  UartPacket uartPacket;
    
  uartPacket.source = '1';
  uartPacket.module = '1';
  uartPacket.function = '6';  //set parameter
  uartPacket.parameter = '0'; //this should be overwritten by following instructions
  
  if (radioButtonParameter1.getSelected())
  {
    uartPacket.parameter = '1';
  }
  else if (radioButtonParameter2.getSelected())
  {
    uartPacket.parameter = '2';
  }
  else if (radioButtonParameter3.getSelected())
  {
    uartPacket.parameter = '3';
  }
  else if (radioButtonParameter4.getSelected())
  {
    uartPacket.parameter = '4';
  }
  else if (radioButtonParameter5.getSelected())
  {
    uartPacket.parameter = '5';
  }
  else if (radioButtonParameter6.getSelected())
  {
    uartPacket.parameter = '6';
  }
  else if (radioButtonParameter7.getSelected())
  {
    uartPacket.parameter = '7';
  }
  else if (radioButtonParameter8.getSelected())
  {
    uartPacket.parameter = '8';
  }
  else if (radioButtonParameter9.getSelected())
  {
    uartPacket.parameter = '9';
  }
  else if (radioButtonParameter10.getSelected())
  {
    uartPacket.parameter = 'a';
  }
  
  if(radioButton_Plus.getSelected())
  {
    /*Value is positive*/
    uartPacket.sign = '1'; 
  }
  else
  {
    /*Value is negative*/
    uartPacket.sign = '2';
  }
     
  char valueBuffer[PAYLOAD_SIZE] = {0};
     
  int values[PAYLOAD_SIZE];
     
  getScrollWheelValues(values);
  translateScrollWheelValues(values);
  
  double value = processScrollWheelValues(values);
     
  sprintf(valueBuffer, "%10lf", value);

  uartPacket.length = PAYLOAD_SIZE + '0'; //convert 10 to ASCII ':'
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    uartPacket.payload[i] = valueBuffer[i];
  }
  
  this->presenter->notifyNewValueToSet(uartPacket);
#endif
}

void Screen_Module1_SettingsView::getScrollWheelValues(int values[])
{
	values[9] = scrollWheel_Digit1.getSelectedItem();
	values[8] = scrollWheel_Digit2.getSelectedItem();
	values[7] = scrollWheel_Digit3.getSelectedItem();
	values[6] = scrollWheel_Digit4.getSelectedItem();
	values[5] = scrollWheel_Digit5.getSelectedItem();
	values[4] = scrollWheel_Digit6.getSelectedItem();
	values[3] = scrollWheel_Digit7.getSelectedItem();
	values[2] = scrollWheel_Digit8.getSelectedItem();
	values[1] = scrollWheel_Digit9.getSelectedItem();
	values[0] = scrollWheel_Digit10.getSelectedItem();
}

void Screen_Module1_SettingsView::translateScrollWheelValues(int values[])
{
	for (int i = 0; i < PAYLOAD_SIZE; i++)
	{
		switch (values[i])
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

double Screen_Module1_SettingsView::processScrollWheelValues(const int values[])
{
	char asciiScrollWheelValues[PAYLOAD_SIZE + 1];

	for (int i = 0; i < PAYLOAD_SIZE; i++)
	{
		asciiScrollWheelValues[i] = values[i];
	}

	asciiScrollWheelValues[PAYLOAD_SIZE] = '\0';

	return atof(asciiScrollWheelValues);
}

void Screen_Module1_SettingsView::enableParameterButtonPushed()
{
  /*Structure used to propagate UART packet contents up to Model class*/
  UartPacket uartPacket;
  
  uartPacket.source = '1';
  uartPacket.module = '1';
  uartPacket.function = '4';  //enable parameter
  uartPacket.parameter = '0'; //this should be overwritten by following instructions
  
  if (radioButtonParameter1.getSelected())
  {
    uartPacket.parameter = '1';
  }
  else if (radioButtonParameter2.getSelected())
  {
    uartPacket.parameter = '2';
  }
  else if (radioButtonParameter3.getSelected())
  {
    uartPacket.parameter = '3';
  }
  else if (radioButtonParameter4.getSelected())
  {
    uartPacket.parameter = '4';
  }
  else if (radioButtonParameter5.getSelected())
  {
    uartPacket.parameter = '5';
  }
  else if (radioButtonParameter6.getSelected())
  {
    uartPacket.parameter = '6';
  }
  else if (radioButtonParameter7.getSelected())
  {
    uartPacket.parameter = '7';
  }
  else if (radioButtonParameter8.getSelected())
  {
    uartPacket.parameter = '8';
  }
  else if (radioButtonParameter9.getSelected())
  {
    uartPacket.parameter = '9';
  }
  else if (radioButtonParameter10.getSelected())
  {
    uartPacket.parameter = 'a';
  }
  
  uartPacket.sign = '1'; //sign is always positive
  uartPacket.length = '1';
  uartPacket.payload[6] = 0;
  
  this->presenter->notifyNewValueToSet(uartPacket);
}

void Screen_Module1_SettingsView::disableParameterButtonPushed()
{
  /*Structure used to propagate UART packet contents up to Model class*/
  UartPacket uartPacket;
  
  uartPacket.source = '1';
  uartPacket.module = '1';
  uartPacket.function = '5';  //disable parameter
  uartPacket.parameter = '0'; //this should be overwritten by following instructions
  
  if (radioButtonParameter1.getSelected())
  {
    uartPacket.parameter = '1';
  }
  else if (radioButtonParameter2.getSelected())
  {
    uartPacket.parameter = '2';
  }
  else if (radioButtonParameter3.getSelected())
  {
    uartPacket.parameter = '3';
  }
  else if (radioButtonParameter4.getSelected())
  {
    uartPacket.parameter = '4';
  }
  else if (radioButtonParameter5.getSelected())
  {
    uartPacket.parameter = '5';
  }
  else if (radioButtonParameter6.getSelected())
  {
    uartPacket.parameter = '6';
  }
  else if (radioButtonParameter7.getSelected())
  {
    uartPacket.parameter = '7';
  }
  else if (radioButtonParameter8.getSelected())
  {
    uartPacket.parameter = '8';
  }
  else if (radioButtonParameter9.getSelected())
  {
    uartPacket.parameter = '9';
  }
  else if (radioButtonParameter10.getSelected())
  {
    uartPacket.parameter = 'a';
  }
  
  uartPacket.sign = '1'; //sign is always positive
  uartPacket.length = '1';
  uartPacket.payload[6] = 0;
  
  this->presenter->notifyNewValueToSet(uartPacket);
}

void Screen_Module1_SettingsView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}

void Screen_Module1_SettingsView::scrollWheel_Digit1UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit2UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit3UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit4UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit5UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit6UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit7UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit8UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit9UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}

void Screen_Module1_SettingsView::scrollWheel_Digit10UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithComma(itemIndex);
}