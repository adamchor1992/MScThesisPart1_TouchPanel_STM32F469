#include <gui/screen_module1_info_screen/Screen_Module1_InfoView.hpp>
#include <gui/model/Model.hpp>
#include <string>

#define PAYLOAD_SIZE 10

Screen_Module1_InfoView::Screen_Module1_InfoView()
{
#ifndef SIMULATOR  
  uint8_t initParameter1NameStringLength_int = Model::m_initParameter1NameStringLength - '0';
  uint8_t initParameter2NameStringLength_int = Model::m_initParameter2NameStringLength - '0';
  uint8_t initParameter3NameStringLength_int = Model::m_initParameter3NameStringLength - '0';
  uint8_t initParameter4NameStringLength_int = Model::m_initParameter4NameStringLength - '0';
  uint8_t initParameter5NameStringLength_int = Model::m_initParameter5NameStringLength - '0';
  
  uint16_t initParameter1NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter2NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter3NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter4NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter5NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  
  uint8_t initParameter1ValueStringLength_int = Model::m_initParameter1ValueStringLength - '0';
  uint8_t initParameter2ValueStringLength_int = Model::m_initParameter2ValueStringLength - '0';
  uint8_t initParameter3ValueStringLength_int = Model::m_initParameter3ValueStringLength - '0';
  uint8_t initParameter4ValueStringLength_int = Model::m_initParameter4ValueStringLength - '0';
  uint8_t initParameter5ValueStringLength_int = Model::m_initParameter5ValueStringLength - '0';
  
  uint16_t initParameter1ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter2ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter3ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter4ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter5ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  
  for (int i = 0; i < initParameter1NameStringLength_int; i++)
  {
    *(initParameter1NameStringDisplay + i) = *(Model::m_initParameter1Name + i);
  }
  
  for (int i = 0; i < initParameter2NameStringLength_int; i++)
  {
    *(initParameter2NameStringDisplay + i) = *(Model::m_initParameter2Name + i);
  }
  
  for (int i = 0; i < initParameter3NameStringLength_int; i++)
  {
    *(initParameter3NameStringDisplay + i) = *(Model::m_initParameter3Name + i);
  }
  
  for (int i = 0; i < initParameter4NameStringLength_int; i++)
  {
    *(initParameter4NameStringDisplay + i) = *(Model::m_initParameter4Name + i);
  }
  
  for (int i = 0; i < initParameter5NameStringLength_int; i++)
  {
    *(initParameter5NameStringDisplay + i) = *(Model::m_initParameter5Name + i);
  }
  
    for (int i = 0; i < initParameter1ValueStringLength_int; i++)
  {
    *(initParameter1ValueStringDisplay + i) = *(Model::m_initParameter1Value + i);
  }
  
  for (int i = 0; i < initParameter2ValueStringLength_int; i++)
  {
    *(initParameter2ValueStringDisplay + i) = *(Model::m_initParameter2Value + i);
  }
  
  for (int i = 0; i < initParameter3ValueStringLength_int; i++)
  {
    *(initParameter3ValueStringDisplay + i) = *(Model::m_initParameter3Value + i);
  }
  
  for (int i = 0; i < initParameter4ValueStringLength_int; i++)
  {
    *(initParameter4ValueStringDisplay + i) = *(Model::m_initParameter4Value + i);
  }
  
  for (int i = 0; i < initParameter5ValueStringLength_int; i++)
  {
    *(initParameter5ValueStringDisplay + i) = *(Model::m_initParameter5Value + i);
  }
  
  Unicode::snprintf(textArea_InitParameter1NameBuffer, TEXTAREA_INITPARAMETER1NAME_SIZE, "%s", initParameter1NameStringDisplay);
  textArea_InitParameter1Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter2NameBuffer, TEXTAREA_INITPARAMETER2NAME_SIZE, "%s", initParameter2NameStringDisplay);
  textArea_InitParameter2Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter3NameBuffer, TEXTAREA_INITPARAMETER3NAME_SIZE, "%s", initParameter3NameStringDisplay);
  textArea_InitParameter3Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter4NameBuffer, TEXTAREA_INITPARAMETER4NAME_SIZE, "%s", initParameter4NameStringDisplay);
  textArea_InitParameter4Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter5NameBuffer, TEXTAREA_INITPARAMETER5NAME_SIZE, "%s", initParameter5NameStringDisplay);
  textArea_InitParameter5Name.invalidate();
  
  Unicode::snprintf(textArea_InitParameter1ValueBuffer, TEXTAREA_INITPARAMETER1VALUE_SIZE, "%s", initParameter1ValueStringDisplay);
  textArea_InitParameter1Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter2ValueBuffer, TEXTAREA_INITPARAMETER2VALUE_SIZE, "%s", initParameter2ValueStringDisplay);
  textArea_InitParameter2Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter3ValueBuffer, TEXTAREA_INITPARAMETER3VALUE_SIZE, "%s", initParameter3ValueStringDisplay);
  textArea_InitParameter3Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter4ValueBuffer, TEXTAREA_INITPARAMETER4VALUE_SIZE, "%s", initParameter4ValueStringDisplay);
  textArea_InitParameter4Value.invalidate();
  
  Unicode::snprintf(textArea_InitParameter5ValueBuffer, TEXTAREA_INITPARAMETER5VALUE_SIZE, "%s", initParameter5ValueStringDisplay);
  textArea_InitParameter5Value.invalidate();
#endif
}

void Screen_Module1_InfoView::setupScreen()
{
  Screen_Module1_InfoViewBase::setupScreen();
}

void Screen_Module1_InfoView::tearDownScreen()
{
  Screen_Module1_InfoViewBase::tearDownScreen();
}

void Screen_Module1_InfoView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}