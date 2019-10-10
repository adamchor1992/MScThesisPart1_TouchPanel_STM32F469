#include <gui/screen_module1_info_screen/Screen_Module1_InfoView.hpp>
#include <gui/model/Model.hpp>
#include <string>

#define PAYLOAD_SIZE 10

Screen_Module1_InfoView::Screen_Module1_InfoView()
{
#ifndef SIMULATOR    
  uint16_t initParameter1NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter2NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter3NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter4NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter5NameStringDisplay[PAYLOAD_SIZE] = { 0 };
  
  uint16_t initParameter1ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter2ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter3ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter4ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t initParameter5ValueStringDisplay[PAYLOAD_SIZE] = { 0 };
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    initParameter1NameStringDisplay[i] = Model::m_InitParameter1Name[i];
    initParameter2NameStringDisplay[i] = Model::m_InitParameter2Name[i];
    initParameter3NameStringDisplay[i] = Model::m_InitParameter3Name[i];
    initParameter4NameStringDisplay[i] = Model::m_InitParameter4Name[i];
    initParameter5NameStringDisplay[i] = Model::m_InitParameter5Name[i];
    initParameter1ValueStringDisplay[i] = Model::m_InitParameter1Value[i];
    initParameter2ValueStringDisplay[i] = Model::m_InitParameter2Value[i];
    initParameter3ValueStringDisplay[i] = Model::m_InitParameter3Value[i];
    initParameter4ValueStringDisplay[i] = Model::m_InitParameter4Value[i];
    initParameter5ValueStringDisplay[i] = Model::m_InitParameter5Value[i];
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
#ifndef SIMULATOR
  NVIC_DisableIRQ(USART6_IRQn);
#endif
}

void Screen_Module1_InfoView::tearDownScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
}

void Screen_Module1_InfoView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}