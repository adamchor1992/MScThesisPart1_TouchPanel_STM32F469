#include <gui/screen_module2_screen/Screen_Module2View.hpp>

Screen_Module2View::Screen_Module2View()
{
  
}

void Screen_Module2View::setupScreen()
{
  Screen_Module2ViewBase::setupScreen();
}

void Screen_Module2View::tearDownScreen()
{
  Screen_Module2ViewBase::tearDownScreen();
}

void Screen_Module2View::updateGUIFrameData(UARTFrameStruct_t s_UARTFrame)
{
  if (s_UARTFrame.module == '2')
  {
    Unicode::snprintf(textArea_SourceIDBuffer, TEXTAREA_SOURCEID_SIZE, "%c", s_UARTFrame.source);
    textArea_SourceID.invalidate();
    
    Unicode::snprintf(textArea_ModuleIDBuffer, TEXTAREA_MODULEID_SIZE, "%c", s_UARTFrame.module);
    textArea_ModuleID.invalidate();
    
    Unicode::snprintf(textArea_ParameterIDBuffer, TEXTAREA_PARAMETERID_SIZE, "%c", s_UARTFrame.parameter);
    textArea_ParameterID.invalidate();
    
    //value displaying
    uint16_t stringToDisplay[8] = { 0 };
    
    s_UARTFrame.length = s_UARTFrame.length - '0'; //convert char to int length
    
    for (int i = 0; i < s_UARTFrame.length; i++)
    {
      *(stringToDisplay + i) = *(s_UARTFrame.payload + i);
    }
    
    Unicode::snprintf(textArea_ValueBuffer, s_UARTFrame.length + 1, "%s", stringToDisplay); //length + 1 because it is null-terminated string
    textArea_Value.invalidate();
    
    //CRC displaying
    uint16_t CRCstringToDisplay[4] = { 0 };
    
    CRCstringToDisplay[0] = *(s_UARTFrame.payload + 8);
    CRCstringToDisplay[1] = *(s_UARTFrame.payload + 9);
    CRCstringToDisplay[2] = *(s_UARTFrame.payload + 10);
    CRCstringToDisplay[3] = *(s_UARTFrame.payload + 11);
    
    Unicode::snprintf(textArea_CRCBuffer, 5, "%s", CRCstringToDisplay); //length + 1 because it is null-terminated string
    textArea_CRC.invalidate();
  }
}

void Screen_Module2View::updateValueToSet(int value)
{
  Unicode::itoa(value, textArea_ValueToSetBuffer, TEXTAREA_VALUETOSET_SIZE, 10);
  textArea_ValueToSet.setWildcard(textArea_ValueToSetBuffer);
  textArea_ValueToSet.invalidate();
}

void Screen_Module2View::setNewValue()
{
  /*Structure used to propagate UART frame contents up to Model class*/
  UARTFrameStruct_t s_UARTFrame;
  
  s_UARTFrame.source = '1';
  s_UARTFrame.module = '2';
  s_UARTFrame.parameter = '0'; //this should be overwritten by following instructions
  
  if (radioButtonParameter1.getSelected())
  {
    s_UARTFrame.parameter = '1';
  }
  else if (radioButtonParameter2.getSelected())
  {
    s_UARTFrame.parameter = '2';
  }
  
//  uint8_t source = '1';
//  uint8_t module = '2';
//  uint8_t parameter = '0'; //this should be overwritten by following instructions
  
  uint8_t sliderValue = slider_Value.getValue();
  
  if (sliderValue < 10)
    s_UARTFrame.length = '1';
  else if (sliderValue < 100)
    s_UARTFrame.length = '2';
  else if (sliderValue >= 100)
    s_UARTFrame.length = '3';
  else
    s_UARTFrame.length = '9'; //error
  
  char data_chars[6] = { 255, 255, 255, 255, 255, 255 }; //data starts from 4th element up to [4 + length] element
  
  sprintf(data_chars, "%d", sliderValue);
  
  //uint8_t data[6] = { 255, 255, 255, 255, 255, 255 }; //data starts from 4th element up to [4 + length] element
  
  for (int i = 0; i < 6; i++)
  {
    s_UARTFrame.payload[i] = data_chars[i];
  }
  
  this->presenter->notifyNewValueToSet(s_UARTFrame);
}

void Screen_Module2View::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}