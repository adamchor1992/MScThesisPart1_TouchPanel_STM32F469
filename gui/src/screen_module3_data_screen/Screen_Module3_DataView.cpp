#include <gui/screen_module3_data_screen/Screen_Module3_DataView.hpp>
#include <gui/model/Model.hpp>
#include <string>

Screen_Module3_DataView::Screen_Module3_DataView() : TextAreaClickedCallback(this, &Screen_Module3_DataView::TextAreaClickHandler)
{
#ifndef SIMULATOR       
  uint16_t parameterStringDisplay[CUSTOM_PARAMETER_NAME_COUNT][PAYLOAD_SIZE] = {{ 0 }};
  uint16_t valueStringDisplay[CUSTOM_PARAMETER_VALUE_COUNT][PAYLOAD_SIZE] = {{ 0 }};
  
  for(int i = 0; i < CUSTOM_PARAMETER_NAME_COUNT; i++)
  {
    for (int character = 0; character < PAYLOAD_SIZE; character++)
    {
      parameterStringDisplay[i][character] = Model::m_InitParametersModule3[i + CUSTOM_PARAMETER_NAME_OFFSET][character];
    }
  }
  
  for(int i = 0; i < CUSTOM_PARAMETER_VALUE_COUNT; i++)
  {
    for (int character = 0; character < PAYLOAD_SIZE; character++)
    {
      valueStringDisplay[i][character] = Model::m_InitParametersModule3[i + CUSTOM_PARAMETER_VALUE_OFFSET][character];
    }
  }
  
  Unicode::snprintf(textArea_Parameter1NameBuffer, TEXTAREA_PARAMETER1NAME_SIZE, "%s", parameterStringDisplay[0]);
  textArea_Parameter1Name.invalidate();
  
  Unicode::snprintf(textArea_Parameter2NameBuffer, TEXTAREA_PARAMETER2NAME_SIZE, "%s", parameterStringDisplay[1]);
  textArea_Parameter2Name.invalidate();
  
  Unicode::snprintf(textArea_Parameter3NameBuffer, TEXTAREA_PARAMETER3NAME_SIZE, "%s", parameterStringDisplay[2]);
  textArea_Parameter3Name.invalidate();
  
  Unicode::snprintf(textArea_Parameter4NameBuffer, TEXTAREA_PARAMETER4NAME_SIZE, "%s", parameterStringDisplay[3]);
  textArea_Parameter4Name.invalidate();
  
  Unicode::snprintf(textArea_Parameter1ValueBuffer, TEXTAREA_PARAMETER1VALUE_SIZE, "%s", valueStringDisplay[0]);
  textArea_Parameter1Value.invalidate();
  
  Unicode::snprintf(textArea_Parameter2ValueBuffer, TEXTAREA_PARAMETER2VALUE_SIZE, "%s", valueStringDisplay[1]);
  textArea_Parameter2Value.invalidate();
  
  Unicode::snprintf(textArea_Parameter3ValueBuffer, TEXTAREA_PARAMETER3VALUE_SIZE, "%s", valueStringDisplay[2]);
  textArea_Parameter3Value.invalidate();
  
  Unicode::snprintf(textArea_Parameter4ValueBuffer, TEXTAREA_PARAMETER4VALUE_SIZE, "%s", valueStringDisplay[3]);
  textArea_Parameter4Value.invalidate();
#endif
}

void Screen_Module3_DataView::TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& evt)
{
  if (&b == &textArea_Parameter1Name)
  {
    textArea_Parameter1Name.setVisible(false);
    textArea_Parameter1Value.setVisible(false);
    textArea_Parameter1Name.invalidate();
    textArea_Parameter1Value.invalidate();
  }
  else if (&b == &textArea_Parameter2Name)
  {
    textArea_Parameter2Name.setVisible(false);
    textArea_Parameter2Value.setVisible(false);
    textArea_Parameter2Name.invalidate();
    textArea_Parameter2Value.invalidate();
  }
  else if (&b == &textArea_Parameter3Name)
  {
    textArea_Parameter3Name.setVisible(false);
    textArea_Parameter3Value.setVisible(false);
    textArea_Parameter3Name.invalidate();
    textArea_Parameter3Value.invalidate();
  }
  else if (&b == &textArea_Parameter4Name)
  {
    textArea_Parameter4Name.setVisible(false);
    textArea_Parameter4Value.setVisible(false);
    textArea_Parameter4Name.invalidate();
    textArea_Parameter4Value.invalidate();
  }
}

void Screen_Module3_DataView::setupScreen()
{  
  textArea_Parameter1Name.setClickAction(TextAreaClickedCallback);
  textArea_Parameter2Name.setClickAction(TextAreaClickedCallback);
  textArea_Parameter3Name.setClickAction(TextAreaClickedCallback);
  textArea_Parameter4Name.setClickAction(TextAreaClickedCallback);
}

void Screen_Module3_DataView::UpdateGuiPacketData(UartPacket& uartPacket)
{
  double value = std::stod((char*)(uartPacket.GetPayload()));
  
  if (uartPacket.GetSign() == Sign::NEGATIVE_SIGN)
  {
    /*Make value negative*/
    value = value * (-1);
  }
  
  char stringToDisplayChar[PAYLOAD_SIZE + 2];
  
  /*Convert long double value to char string*/ 
  snprintf(stringToDisplayChar, PAYLOAD_SIZE + 2, "%lf", value);
  
  Unicode::UnicodeChar stringToDisplayUnicode[PAYLOAD_SIZE + 2];
  
  /*Convert char string to unicode string*/
  Unicode::strncpy(stringToDisplayUnicode, stringToDisplayChar, PAYLOAD_SIZE + 2);
  
#ifndef SIMULATOR
  if (uartPacket.GetModule() == ModuleID::MODULE3)
  {
    switch(uartPacket.GetParameter())
    {
    case Parameter::PARAMETER1:
      Unicode::snprintf(textArea_Parameter1ValueBuffer, TEXTAREA_PARAMETER1VALUE_SIZE, "%s", stringToDisplayUnicode);
      textArea_Parameter1Value.invalidate();
      break;
    case Parameter::PARAMETER2:
      Unicode::snprintf(textArea_Parameter2ValueBuffer, TEXTAREA_PARAMETER2VALUE_SIZE, "%s", stringToDisplayUnicode);
      textArea_Parameter2Value.invalidate();
      break;
    case Parameter::PARAMETER3:
      Unicode::snprintf(textArea_Parameter3ValueBuffer, TEXTAREA_PARAMETER3VALUE_SIZE, "%s", stringToDisplayUnicode);
      textArea_Parameter3Value.invalidate();
      break;
    case Parameter::PARAMETER4:
      Unicode::snprintf(textArea_Parameter4ValueBuffer, TEXTAREA_PARAMETER4VALUE_SIZE, "%s", stringToDisplayUnicode);
      textArea_Parameter4Value.invalidate();
      break;
    }
  }
#endif
}

void Screen_Module3_DataView::ShowAll()
{
  textArea_Parameter1Name.setVisible(true);
  textArea_Parameter1Value.setVisible(true);
  textArea_Parameter2Name.setVisible(true);
  textArea_Parameter2Value.setVisible(true);
  textArea_Parameter3Name.setVisible(true);
  textArea_Parameter3Value.setVisible(true);
  textArea_Parameter4Name.setVisible(true);
  textArea_Parameter4Value.setVisible(true);
  
  textArea_Parameter1Name.invalidate();
  textArea_Parameter1Value.invalidate();
  textArea_Parameter2Name.invalidate();
  textArea_Parameter2Value.invalidate();
  textArea_Parameter3Name.invalidate();
  textArea_Parameter3Value.invalidate();
  textArea_Parameter4Name.invalidate();
  textArea_Parameter4Value.invalidate();
}

void Screen_Module3_DataView::UpdateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}