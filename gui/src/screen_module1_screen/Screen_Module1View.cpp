#include <gui/screen_module1_screen/Screen_Module1View.hpp>
#include "stm32469i_discovery.h" //for led driving

#define FRAME_SIZE 16

Screen_Module1View::Screen_Module1View()
{
  
}

void Screen_Module1View::setupScreen()
{
  Screen_Module1ViewBase::setupScreen();

  extern UART_HandleTypeDef huart6;
  /*Table to which UART interrupt writes*/
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];

  /*Activate green LED to show that receiving is active*/
  BSP_LED_On(LED1);

  /*Start of UART interrupt receiving*/
  HAL_UART_Receive_IT(&huart6, UART_ReceivedFrame, FRAME_SIZE);
  NVIC_EnableIRQ(USART6_IRQn);
}

void Screen_Module1View::tearDownScreen()
{
  /*Disable UART RX Interrupt*/
  NVIC_DisableIRQ(USART6_IRQn);

  /*Dectivate green LED to show that receiving is not active*/
  BSP_LED_Off(LED1);

  Screen_Module1ViewBase::tearDownScreen();
}

void Screen_Module1View::updateGUIFrameData(UARTFrameStruct_t s_UARTFrame)
{
  if (s_UARTFrame.module == '1')
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

void Screen_Module1View::updateValueToSet(int value)
{
  Unicode::itoa(value, textArea_ValueToSetBuffer, TEXTAREA_VALUETOSET_SIZE, 10);
  textArea_ValueToSet.setWildcard(textArea_ValueToSetBuffer);
  textArea_ValueToSet.invalidate();
}

void Screen_Module1View::setNewValue()
{
  /*Structure used to propagate UART frame contents up to Model class*/
  UARTFrameStruct_t s_UARTFrame;
  
  s_UARTFrame.source = '1';
  s_UARTFrame.module = '1';
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

void Screen_Module1View::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}