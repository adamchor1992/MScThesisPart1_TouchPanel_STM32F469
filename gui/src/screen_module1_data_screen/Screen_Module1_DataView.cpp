#include <gui/screen_module1_data_screen/Screen_Module1_DataView.hpp>
#include <gui/model/Model.hpp>

Screen_Module1_DataView::Screen_Module1_DataView() : TextAreaClickedCallback(this, &Screen_Module1_DataView::TextAreaClickHandler)
{
#ifndef SIMULATOR       
  uint16_t parameterStringDisplay[CUSTOM_PARAMETER_NAME_COUNT][PAYLOAD_SIZE] = {{ 0 }};
  
  for(int i = 0; i < CUSTOM_PARAMETER_NAME_COUNT; i++)
  {
    for (int character = 0; character < PAYLOAD_SIZE; character++)
    {
      parameterStringDisplay[i][character] = Model::m_InitParametersModule1[i + CUSTOM_PARAMETER_NAME_OFFSET][character];
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
#endif
}

void Screen_Module1_DataView::TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& evt)
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

void Screen_Module1_DataView::setupScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
  
  textArea_Parameter1Name.setClickAction(TextAreaClickedCallback);
  textArea_Parameter2Name.setClickAction(TextAreaClickedCallback);
  textArea_Parameter3Name.setClickAction(TextAreaClickedCallback);
  textArea_Parameter4Name.setClickAction(TextAreaClickedCallback);
}

void Screen_Module1_DataView::tearDownScreen()
{
  
}

void Screen_Module1_DataView::updateGUIFrameData(UARTFrameStruct_t & s_UARTFrame)
{
  //value to display
  uint16_t stringToDisplay[10] = { 0 };
  
  uint8_t length_int = s_UARTFrame.length - '0'; //convert char to int length
  
  for (int i = 0; i < length_int; i++)
  {
    stringToDisplay[i] = s_UARTFrame.payload[i];
  }
  
#ifndef SIMULATOR
  if (s_UARTFrame.module == '1')
  {
    switch(s_UARTFrame.parameter)
    {
    case '1':
      Unicode::snprintf(textArea_Parameter1ValueBuffer, TEXTAREA_PARAMETER1VALUE_SIZE, "%s", stringToDisplay);
      textArea_Parameter1Value.invalidate();
      break;
    case '2':
      Unicode::snprintf(textArea_Parameter2ValueBuffer, TEXTAREA_PARAMETER2VALUE_SIZE, "%s", stringToDisplay);
      textArea_Parameter2Value.invalidate();
      break;
    case '3':
      Unicode::snprintf(textArea_Parameter3ValueBuffer, TEXTAREA_PARAMETER3VALUE_SIZE, "%s", stringToDisplay);
      textArea_Parameter3Value.invalidate();
      break;
    case '4':
      Unicode::snprintf(textArea_Parameter4ValueBuffer, TEXTAREA_PARAMETER4VALUE_SIZE, "%s", stringToDisplay);
      textArea_Parameter4Value.invalidate();
      break;
    }
  }
#endif
}

void Screen_Module1_DataView::showAll()
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

void Screen_Module1_DataView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}