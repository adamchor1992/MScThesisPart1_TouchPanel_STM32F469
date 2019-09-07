#include <gui/screen_module1_data_screen/Screen_Module1_DataView.hpp>

Screen_Module1_DataView::Screen_Module1_DataView()
{

}

void Screen_Module1_DataView::setupScreen()
{
    Screen_Module1_DataViewBase::setupScreen();
}

void Screen_Module1_DataView::tearDownScreen()
{
    Screen_Module1_DataViewBase::tearDownScreen();
}

void Screen_Module1_DataView::updateGUIFrameData(UARTFrameStruct_t & s_UARTFrame)
{
  if (s_UARTFrame.module == '1')
  {
    Unicode::snprintf(textArea_SourceIDBuffer, TEXTAREA_SOURCEID_SIZE, "%c", s_UARTFrame.source);
    textArea_SourceID.invalidate();
    
    Unicode::snprintf(textArea_ModuleIDBuffer, TEXTAREA_MODULEID_SIZE, "%c", s_UARTFrame.module);
    textArea_ModuleID.invalidate();
    
    Unicode::snprintf(textArea_TypeIDBuffer, TEXTAREA_TYPEID_SIZE, "%c", s_UARTFrame.type);
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
}
