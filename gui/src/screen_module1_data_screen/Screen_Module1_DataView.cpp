#include <gui/screen_module1_data_screen/Screen_Module1_DataView.hpp>

Screen_Module1_DataView::Screen_Module1_DataView() : TextAreaClickedCallback(this, &Screen_Module1_DataView::TextAreaClickHandler)
{

}

void Screen_Module1_DataView::TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& evt)
{
	if (&b == &textArea_Voltage)
	{
		textArea_Voltage.setVisible(false);
		textArea_Voltage.invalidate();
	}
	else if (&b == &textArea_Current)
	{
		textArea_Current.setVisible(false);
		textArea_Current.invalidate();
	}
	else if (&b == &textArea_Frequency)
	{
		textArea_Frequency.setVisible(false);
		textArea_Frequency.invalidate();
	}
	else if (&b == &textArea_Power)
	{
		textArea_Power.setVisible(false);
		textArea_Power.invalidate();
	}
}

void Screen_Module1_DataView::setupScreen()
{
    Screen_Module1_DataViewBase::setupScreen();

	// Add the callback to HiddenBox
	textArea_Voltage.setClickAction(TextAreaClickedCallback);
	textArea_Current.setClickAction(TextAreaClickedCallback);
	textArea_Frequency.setClickAction(TextAreaClickedCallback);
	textArea_Power.setClickAction(TextAreaClickedCallback);
}

void Screen_Module1_DataView::tearDownScreen()
{
    Screen_Module1_DataViewBase::tearDownScreen();
}

void Screen_Module1_DataView::updateGUIFrameData(UARTFrameStruct_t & s_UARTFrame)
{
  //value to display
  uint16_t stringToDisplay[10] = { 0 };
  
  uint8_t length_int = s_UARTFrame.length - '0'; //convert char to int length
  
  for (int i = 0; i < length_int; i++)
  {
    *(stringToDisplay + i) = *(s_UARTFrame.payload + i);
  }
    
#ifndef SIMULATOR
  if (s_UARTFrame.module == '1')
  {
    switch(s_UARTFrame.parameter)
    {
    case 'b':
      Unicode::snprintf(textArea_VoltageBuffer, TEXTAREA_VOLTAGE_SIZE, "%s", stringToDisplay);
      textArea_Voltage.invalidate();
      break;
    case 'c':
      Unicode::snprintf(textArea_CurrentBuffer, TEXTAREA_CURRENT_SIZE, "%s", stringToDisplay);
      textArea_Current.invalidate();
      break;
    case 'd':
      Unicode::snprintf(textArea_FrequencyBuffer, TEXTAREA_FREQUENCY_SIZE, "%s", stringToDisplay);
      textArea_Frequency.invalidate();
      break;
    case 'e':
      Unicode::snprintf(textArea_PowerBuffer, TEXTAREA_POWER_SIZE, "%s", stringToDisplay);
      textArea_Power.invalidate();
      break;
    }
  }
#endif
}

void Screen_Module1_DataView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}

void Screen_Module1_DataView::showAll()
{
	textArea_Voltage.setVisible(true);
	textArea_Current.setVisible(true);
	textArea_Frequency.setVisible(true);
	textArea_Power.setVisible(true);

	textArea_Voltage.invalidate();
	textArea_Current.invalidate();
	textArea_Frequency.invalidate();
	textArea_Power.invalidate();
}