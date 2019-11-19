#include <gui/screen_module1_info_screen/Screen_Module1_InfoView.hpp>
#include <gui/model/Model.hpp>
#include <string>

Screen_Module1_InfoView::Screen_Module1_InfoView()
{
#ifndef SIMULATOR    
  uint16_t initParameterNameStringDisplay[INIT_PARAMETER_NAME_COUNT][PAYLOAD_SIZE] = { 0 };
  uint16_t initParameterValueStringDisplay[INIT_PARAMETER_VALUE_COUNT][PAYLOAD_SIZE] = { 0 };
  
  for(int i = 0; i < INIT_PARAMETER_NAME_COUNT; i++)
  {
    for (int character = 0; character < PAYLOAD_SIZE; character++)
    {
      initParameterNameStringDisplay[i][character] = Model::m_InitParametersModule1[i + INIT_PARAMETER_NAME_OFFSET][character];
    }
  }
  
  for(int i = 0; i < INIT_PARAMETER_VALUE_COUNT; i++)
  {
    for (int character = 0; character < PAYLOAD_SIZE; character++)
    {
      initParameterValueStringDisplay[i][character] = Model::m_InitParametersModule1[i + INIT_PARAMETER_VALUE_OFFSET][character];
    }
  }
  
  Unicode::snprintf(textArea_InitParameter1NameBuffer, TEXTAREA_INITPARAMETER1NAME_SIZE, "%s", initParameterNameStringDisplay[0]);
  textArea_InitParameter1Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter2NameBuffer, TEXTAREA_INITPARAMETER2NAME_SIZE, "%s", initParameterNameStringDisplay[1]);
  textArea_InitParameter2Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter3NameBuffer, TEXTAREA_INITPARAMETER3NAME_SIZE, "%s", initParameterNameStringDisplay[2]);
  textArea_InitParameter3Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter4NameBuffer, TEXTAREA_INITPARAMETER4NAME_SIZE, "%s", initParameterNameStringDisplay[3]);
  textArea_InitParameter4Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter5NameBuffer, TEXTAREA_INITPARAMETER5NAME_SIZE, "%s", initParameterNameStringDisplay[4]);
  textArea_InitParameter5Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter1ValueBuffer, TEXTAREA_INITPARAMETER1VALUE_SIZE, "%s", initParameterValueStringDisplay[0]);
  textArea_InitParameter1Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter2ValueBuffer, TEXTAREA_INITPARAMETER2VALUE_SIZE, "%s", initParameterValueStringDisplay[1]);
  textArea_InitParameter2Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter3ValueBuffer, TEXTAREA_INITPARAMETER3VALUE_SIZE, "%s", initParameterValueStringDisplay[2]);
  textArea_InitParameter3Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter4ValueBuffer, TEXTAREA_INITPARAMETER4VALUE_SIZE, "%s", initParameterValueStringDisplay[3]);
  textArea_InitParameter4Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter5ValueBuffer, TEXTAREA_INITPARAMETER5VALUE_SIZE, "%s", initParameterValueStringDisplay[4]);
  textArea_InitParameter5Value.invalidate();
#endif
}

void Screen_Module1_InfoView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}