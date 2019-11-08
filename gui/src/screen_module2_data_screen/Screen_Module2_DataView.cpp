#include <gui/screen_module2_data_screen/Screen_Module2_DataView.hpp>

Screen_Module2_DataView::Screen_Module2_DataView()
{

}

void Screen_Module2_DataView::setupScreen()
{
    Screen_Module2_DataViewBase::setupScreen();
}

void Screen_Module2_DataView::tearDownScreen()
{
    Screen_Module2_DataViewBase::tearDownScreen();
}

void Screen_Module2_DataView::updateGuiPacketData(UartPacket & uartPacket)
{
  if (uartPacket.module == '2')
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
}

void Screen_Module2_DataView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}