#include <gui/screen_module3_screen/Screen_Module3View.hpp>

Screen_Module3View::Screen_Module3View()
{

}

void Screen_Module3View::setupScreen()
{
	Screen_Module3ViewBase::setupScreen();
}

void Screen_Module3View::tearDownScreen()
{
	Screen_Module3ViewBase::tearDownScreen();
}

void Screen_Module3View::updateGUIFrameData(UARTFrameStruct_t s_UARTFrame)
{
	if (s_UARTFrame.module == '3')
	{
		Unicode::snprintf(textArea_SourceIDBuffer, TEXTAREA_SOURCEID_SIZE, "%c", s_UARTFrame.source);
		textArea_SourceID.invalidate();

		Unicode::snprintf(textArea_ModuleIDBuffer, TEXTAREA_MODULEID_SIZE, "%c", s_UARTFrame.module);
		textArea_ModuleID.invalidate();

		Unicode::snprintf(textArea_ParameterIDBuffer, TEXTAREA_PARAMETERID_SIZE, "%c", s_UARTFrame.parameter);
		textArea_ParameterID.invalidate();

		uint16_t stringToDisplay[7] = { 255,255,255,255,255,255,255 };

		s_UARTFrame.length = s_UARTFrame.length - '0'; //convert char to int length

		for (int i = 0; i < s_UARTFrame.length; i++)
		{
			*(stringToDisplay + i) = *(s_UARTFrame.payload + i);
		}

		Unicode::snprintf(textArea_ValueBuffer, s_UARTFrame.length + 1, "%s", stringToDisplay); //length + 1 because it is null-terminated string
		textArea_Value.invalidate();
	}
}

void Screen_Module3View::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}