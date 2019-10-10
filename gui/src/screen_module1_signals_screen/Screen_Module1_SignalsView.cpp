#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsView.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <gui/model/Model.hpp>

#define SCALE_FACTOR 1000
#define SINE_PERIOD_DEGREES 360
#define PAYLOAD_SIZE 10

Screen_Module1_SignalsView::Screen_Module1_SignalsView()
{
  #ifndef SIMULATOR     
  uint16_t parameter1StringDisplay[10] = { 0 };
  uint16_t parameter2StringDisplay[10] = { 0 };
  uint16_t parameter3StringDisplay[10] = { 0 };
  uint16_t parameter4StringDisplay[10] = { 0 };
  
  for (int i = 0; i < PAYLOAD_SIZE; i++)
  {
    parameter1StringDisplay[i] = Model::m_Parameter1Name[i];
    parameter2StringDisplay[i] = Model::m_Parameter2Name[i];
    parameter3StringDisplay[i] = Model::m_Parameter3Name[i];
    parameter4StringDisplay[i] = Model::m_Parameter4Name[i];
  }
    
  Unicode::snprintf(textArea_Parameter1NameBuffer, TEXTAREA_PARAMETER1NAME_SIZE, "%s", parameter1StringDisplay);
  textArea_Parameter1Name.invalidate();

  Unicode::snprintf(textArea_Parameter2NameBuffer, TEXTAREA_PARAMETER2NAME_SIZE, "%s", parameter2StringDisplay);
  textArea_Parameter2Name.invalidate();

  Unicode::snprintf(textArea_Parameter3NameBuffer, TEXTAREA_PARAMETER3NAME_SIZE, "%s", parameter3StringDisplay);
  textArea_Parameter3Name.invalidate();

  Unicode::snprintf(textArea_Parameter4NameBuffer, TEXTAREA_PARAMETER4NAME_SIZE, "%s", parameter4StringDisplay);
  textArea_Parameter4Name.invalidate();
  #endif
}

void Screen_Module1_SignalsView::setupScreen()
{  
#ifndef SIMULATOR
  NVIC_DisableIRQ(USART6_IRQn);
#endif
  
  /*Initialize buttons' states*/
  toggleButton_Parameter1.forceState(Screen_Module1_GraphView::m_Parameter1GraphEnabled);
  toggleButton_Parameter2.forceState(Screen_Module1_GraphView::m_Parameter2GraphEnabled);
  toggleButton_Parameter3.forceState(Screen_Module1_GraphView::m_Parameter3GraphEnabled);
  toggleButton_Parameter4.forceState(Screen_Module1_GraphView::m_Parameter4GraphEnabled);
  toggleButton_Auto_Y_Range.forceState(Screen_Module1_GraphView::m_AutoRangeEnabled);
  
  /*Initialize sliders' values */
  slider_TimeRange.setValue(Screen_Module1_GraphView::m_GraphRangeRight / SINE_PERIOD_DEGREES);
  Unicode::snprintf(textArea_TimeRangeBuffer,6,"%d", Screen_Module1_GraphView::m_GraphRangeRight);
  textArea_TimeRange.invalidate();
  
  slider_Y_AxisMin.setValue(Screen_Module1_GraphView::m_GraphRangeBottom / SCALE_FACTOR  * (-1));
  Unicode::snprintf(textArea_Y_AxisMinBuffer,6,"%d", Screen_Module1_GraphView::m_GraphRangeBottom / SCALE_FACTOR);
  textArea_Y_AxisMin.invalidate();
  
  slider_Y_AxisMax.setValue(Screen_Module1_GraphView::m_GraphRangeTop / SCALE_FACTOR);
  Unicode::snprintf(textArea_Y_AxisMaxBuffer,6,"%d", Screen_Module1_GraphView::m_GraphRangeTop / SCALE_FACTOR);
  textArea_Y_AxisMax.invalidate();
}

void Screen_Module1_SignalsView::tearDownScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
  
  Screen_Module1_GraphView::setGraphRanges(slider_Y_AxisMin.getValue() * SCALE_FACTOR * (-1), slider_Y_AxisMax.getValue() * SCALE_FACTOR, slider_TimeRange.getValue() * SINE_PERIOD_DEGREES);
}

void Screen_Module1_SignalsView::setParameter1GraphVisible()
{
  if (toggleButton_Parameter1.getState() == true)
  {
    Screen_Module1_GraphView::m_Parameter1GraphEnabled = true;
  }
  else
  {
    Screen_Module1_GraphView::m_Parameter1GraphEnabled = false;
  }
}

void Screen_Module1_SignalsView::setParameter2GraphVisible()
{
  if (toggleButton_Parameter2.getState() == true)
  {
    Screen_Module1_GraphView::m_Parameter2GraphEnabled = true;
  }
  else
  {
    Screen_Module1_GraphView::m_Parameter2GraphEnabled = false;
  }
}

void Screen_Module1_SignalsView::setParameter3GraphVisible()
{
  if (toggleButton_Parameter3.getState() == true)
  {
    Screen_Module1_GraphView::m_Parameter3GraphEnabled = true;
  }
  else
  {
    Screen_Module1_GraphView::m_Parameter3GraphEnabled = false;
  }
}

void Screen_Module1_SignalsView::setParameter4GraphVisible()
{
  if (toggleButton_Parameter4.getState() == true)
  {
    Screen_Module1_GraphView::m_Parameter4GraphEnabled = true;
  }
  else
  {
    Screen_Module1_GraphView::m_Parameter4GraphEnabled = false;
  }
}

void Screen_Module1_SignalsView::updateTimeRange(int value)
{
  Unicode::snprintf(textArea_TimeRangeBuffer, 6, "%d", value * SINE_PERIOD_DEGREES);
  textArea_TimeRange.invalidate();
}

void Screen_Module1_SignalsView::updateY_AxisMin(int value)
{
  /*Negate value read from slider*/
  value = value * (-1);
  
  Unicode::snprintf(textArea_Y_AxisMinBuffer, 6, "%d", value);
  textArea_Y_AxisMin.invalidate();
}

void Screen_Module1_SignalsView::updateY_AxisMax(int value)
{
  Unicode::snprintf(textArea_Y_AxisMaxBuffer, 6, "%d", value);
  textArea_Y_AxisMax.invalidate();
}

void Screen_Module1_SignalsView::pressedAutoRangeToggleButton()
{
  if(toggleButton_Auto_Y_Range.getState() == true)
  {
    Screen_Module1_GraphView::m_AutoRangeEnabled = true; 
    
    textArea_Y_AxisMin.setVisible(false);
    textArea_Y_AxisMax.setVisible(false);
    slider_Y_AxisMin.setVisible(false);
    slider_Y_AxisMax.setVisible(false);
    
    textArea_Y_AxisMin.invalidate();
    textArea_Y_AxisMax.invalidate();
    slider_Y_AxisMin.invalidate();
    slider_Y_AxisMax.invalidate();
  }
  else
  {
    Screen_Module1_GraphView::m_AutoRangeEnabled = false;
    
    textArea_Y_AxisMin.setVisible(true);
    textArea_Y_AxisMax.setVisible(true);
    slider_Y_AxisMin.setVisible(true);
    slider_Y_AxisMax.setVisible(true);
    
    textArea_Y_AxisMin.invalidate();
    textArea_Y_AxisMax.invalidate();
    slider_Y_AxisMin.invalidate();
    slider_Y_AxisMax.invalidate();
  }
}

void Screen_Module1_SignalsView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}