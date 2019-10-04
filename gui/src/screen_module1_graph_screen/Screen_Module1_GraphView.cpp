#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <string>
#include <cmath>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>
#endif

#ifdef SIMULATOR
#include <iostream>
using namespace std;
#endif

#define INITIAL_GRAPH_RANGE_BOTTOM -1000
#define INITIAL_GRAPH_RANGE_TOP 1000
#define INITIAL_GRAPH_RANGE_LEFT 0
#define INITIAL_GRAPH_RANGE_RIGHT 720

#define GRAPHS_COUNT 4
#define SCALE_FACTOR 1000

bool Screen_Module1_GraphView::m_Parameter1GraphEnabled = true;
bool Screen_Module1_GraphView::m_Parameter2GraphEnabled = true;
bool Screen_Module1_GraphView::m_Parameter3GraphEnabled = true;
bool Screen_Module1_GraphView::m_Parameter4GraphEnabled = true;
bool Screen_Module1_GraphView::m_AutoRangeEnabled = false;

int Screen_Module1_GraphView::m_GraphRangeBottom = INITIAL_GRAPH_RANGE_BOTTOM;
int Screen_Module1_GraphView::m_GraphRangeTop = INITIAL_GRAPH_RANGE_TOP;
int Screen_Module1_GraphView::m_GraphRangeRight = INITIAL_GRAPH_RANGE_RIGHT;

void Screen_Module1_GraphView::setGraphRanges(int bottom, int top, int right)
{
  m_GraphRangeBottom = bottom;
  m_GraphRangeTop = top;
  m_GraphRangeRight = right;
}

Screen_Module1_GraphView::Screen_Module1_GraphView()
{
  m_GraphRangeBottomChangedFlag = false;
  m_GraphRangeTopChangedFlag = false;
  
  m_PreviousYellow_X = 0;
  m_PreviousRed_X = 0;
  m_PreviousBlue_X = 0;
  m_PreviousGreen_X = 0;
  
  m_TickCounter = 0;
  
  m_Graphs[0] = &m_GraphYellow;
  m_Graphs[1] = &m_GraphRed;
  m_Graphs[2] = &m_GraphBlue;
  m_Graphs[3] = &m_GraphGreen;
}

void Screen_Module1_GraphView::setupScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern uint8_t UART_ReceivedFrame[FRAME_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
  
  m_TickCounter = 0;
  
  // Set the outer dimensions and color of the graphs
  m_GraphYellow.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), m_GraphRangeBottom, m_GraphRangeTop);
  m_GraphRed.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00), m_GraphRangeBottom, m_GraphRangeTop);
  m_GraphBlue.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF), m_GraphRangeBottom, m_GraphRangeTop);
  m_GraphGreen.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00), m_GraphRangeBottom, m_GraphRangeTop);
  
  // Initialize graphs
  for (int i = 0; i < GRAPHS_COUNT; i++)
  {
    // Place graphs on the screen
    m_Graphs[i]->setXY(55, 0);
    // Set the ranges for the x and y axis of the graphs
    m_Graphs[i]->setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
    // Set line width of the graphs
    m_Graphs[i]->setLineWidth(1);
  }
  
  /*Initialize graph ranges text areas */
  Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", m_GraphRangeTop / SCALE_FACTOR);
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", m_GraphRangeBottom / SCALE_FACTOR);
  textArea_GraphRangeBottom.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeRightBuffer, 6, "%d", m_GraphRangeRight);
  textArea_GraphRangeBottom.invalidate();
  
  add(m_GraphYellow);
  add(m_GraphRed);
  add(m_GraphBlue);
  add(m_GraphGreen);
}

void Screen_Module1_GraphView::tearDownScreen()
{
  
}

void Screen_Module1_GraphView::handleTickEvent()
{
  if (m_AutoRangeEnabled == true)
  {
    for (int i = 0; i < GRAPHS_COUNT; i++)
    {
      /*Check if value is higher than any graph's top range*/
      if (m_Value > m_Graphs[i]->getRangeTop())
      {
        m_GraphRangeTopChangedFlag = true;
        m_GraphRangeTop = m_Value;
      }
      /*Check if value is lower than graph bottom range*/
      else if (m_Value < m_Graphs[i]->getRangeBottom())
      {
        m_GraphRangeBottomChangedFlag = true;
        m_GraphRangeBottom = m_Value;
      }
    }
  }
  
  if (m_AutoRangeEnabled == true)
  {
    if (m_GraphRangeBottomChangedFlag)
    {
      m_GraphYellow.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      m_GraphRed.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      m_GraphBlue.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      m_GraphGreen.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      
      Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", m_GraphRangeBottom / SCALE_FACTOR);
      textArea_GraphRangeBottom.invalidate();
      
      /*Reset flag*/
      m_GraphRangeBottomChangedFlag = false;
    }
    
    if (m_GraphRangeTopChangedFlag)
    {
      m_GraphYellow.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      m_GraphRed.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      m_GraphBlue.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      m_GraphGreen.setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, m_GraphRangeBottom, m_GraphRangeTop);
      
      Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", m_GraphRangeTop / SCALE_FACTOR);
      textArea_GraphRangeTop.invalidate();
      
      /*Reset flag*/
      m_GraphRangeTopChangedFlag = false;
    }
  }
  
#ifdef SIMULATOR
  static int value1 = INITIAL_GRAPH_RANGE_BOTTOM;
  static int value2 = INITIAL_GRAPH_RANGE_BOTTOM + 40;
  static int value3 = INITIAL_GRAPH_RANGE_BOTTOM + 80;
  static int value4 = INITIAL_GRAPH_RANGE_BOTTOM + 120;
  
  static bool rising = true;
  
  static int multiplier = 1;
  
  const static int increment = 10;
  
  if (rising)
  {
    value1 = value1 + increment;
  }
  else
  {
    value1 = value1 - increment;
  }
  
  if (value1 >= 1000)
  {
    rising = false;
  }
  else if(value1 <= -1000)
  {
    rising = true;
  }
  
  m_TickCounter += 1;
  
  //value1 = multiplier * sin(m_TickCounter * 3.14159/180) * 100.0;
  
  value2 = value2 + increment;
  value3 = value3 + increment;
  value4 = value4 + increment;
  
  if (m_TickCounter >= m_graphRangeRight)
  {
    m_GraphYellow.clear();
    m_GraphYellow.invalidate();
    
    m_GraphRed.clear();
    m_GraphRed.invalidate();
    
    m_GraphBlue.clear();
    m_GraphBlue.invalidate();
    
    m_GraphGreen.clear();
    m_GraphGreen.invalidate();
    
    m_PreviousYellow_X = 0;
    m_PreviousRed_X = 0;
    m_PreviousBlue_X = 0;
    m_PreviousGreen_X = 0;
    
    m_TickCounter = 0;
  }
  
  char text_buffer1[40] = { 0 }; //temporary buffer
  sprintf(text_buffer1, "Graph bottom range %d\n", m_GraphRangeBottom); // convert
  OutputDebugString(text_buffer1); // print
  char text_buffer11[40] = { 0 }; //temporary buffer
  sprintf(text_buffer11, "Graph bottom range %d\n", m_GraphYellow.getRangeBottom()); // convert
  OutputDebugString(text_buffer11); // print
  
  char text_buffer2[40] = { 0 }; //temporary buffer
  sprintf(text_buffer2, "Graph top range %d\n", m_GraphRangeTop); // convert
  OutputDebugString(text_buffer2); // print
  char text_buffer22[40] = { 0 }; //temporary buffer
  sprintf(text_buffer22, "Graph top range %d\n", m_GraphYellow.getRangeTop()); // convert
  OutputDebugString(text_buffer22); // print
  
  char text_buffer3[40] = { 0 }; //temporary buffer
  sprintf(text_buffer3, "Value1 after scaling %d\n", value1); // convert
  OutputDebugString(text_buffer3); // print
  //char text_buffer33[40] = { 0 }; //temporary buffer
  //sprintf(text_buffer33, "Value1 after scaling %d\n", graphYellow.getRangeBottom()); // convert
  //OutputDebugString(text_buffer33); // print
  
  //cout << "Graph bottom range :" << m_GraphRangeBottom << endl;
  //cout << "Graph top range :" << m_GraphRangeTop << endl;
  //cout << "nValue after scaling :" << value << endl;
  
  if (m_Parameter1GraphEnabled == true)
  {
    if (m_PreviousYellow_X == m_TickCounter)
    {
      ++m_TickCounter;
      m_PreviousYellow_X = m_TickCounter;
    }
    else
    {
      m_PreviousYellow_X = m_TickCounter;
    }
    m_GraphYellow.addValue(m_TickCounter, value1);
  }
  
  if (m_Parameter2GraphEnabled == true)
  {
    if (m_PreviousRed_X == m_TickCounter)
    {
      ++m_TickCounter;
      m_PreviousRed_X = m_TickCounter;
    }
    else
    {
      m_PreviousRed_X = m_TickCounter;
    }
    m_GraphRed.addValue(m_TickCounter, value2);
  }
  
  if (m_Parameter3GraphEnabled == true)
  {
    if (m_PreviousBlue_X == m_TickCounter)
    {
      ++m_TickCounter;
      m_PreviousBlue_X = m_TickCounter;
    }
    else
    {
      m_PreviousBlue_X = m_TickCounter;
    }
    m_GraphBlue.addValue(m_TickCounter, value3);
  }
  
  if (m_Parameter4GraphEnabled == true)
  {
    if (m_PreviousGreen_X == m_TickCounter)
    {
      ++m_TickCounter;
      m_PreviousGreen_X = m_TickCounter;
    }
    else
    {
      m_PreviousGreen_X = m_TickCounter;
    }
    m_GraphGreen.addValue(m_TickCounter, value4);
  }
#endif
}

void Screen_Module1_GraphView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
  BSP_LED_Toggle(LED3);
  
  m_Value = int(std::stof((char*)(s_UARTFrame.payload)) * SCALE_FACTOR); //scale by 1000
  
  if (s_UARTFrame.sign == '2')
  {
    /*Make value_int negative*/
    m_Value = m_Value * (-1);
  }
  
  printf("Graph frame has value: %d\n", m_Value);
  
  if (m_AutoRangeEnabled == true)
  {
    for (int i = 0; i < GRAPHS_COUNT; i++)
    {
      /*Check if value is higher than any graph's top range*/
      if (m_Value > m_Graphs[i]->getRangeTop())
      {
        m_GraphRangeTopChangedFlag = true;
        m_GraphRangeTop = m_Value;
      }
      /*Check if value is lower than graph bottom range*/
      else if (m_Value < m_Graphs[i]->getRangeBottom())
      {
        m_GraphRangeBottomChangedFlag = true;
        m_GraphRangeBottom = m_Value;
      }
    }
  }
  
  if (m_TickCounter >= m_GraphRangeRight)
  {
    m_GraphYellow.clear();
    m_GraphYellow.invalidate();
    
    m_GraphRed.clear();
    m_GraphRed.invalidate();
    
    m_GraphBlue.clear();
    m_GraphBlue.invalidate();
    
    m_GraphGreen.clear();
    m_GraphGreen.invalidate();
    
    m_PreviousYellow_X = 0;
    m_PreviousRed_X = 0;
    m_PreviousBlue_X = 0;
    m_PreviousGreen_X = 0;
    
    m_TickCounter = 0;
  }
  
  printf("Graph bottom range: %d\n", m_GraphRangeBottom);
  printf("Graph top range: %d\n", m_GraphRangeTop);
  printf("Value after scaling: %d\n", m_Value);
  
  switch (s_UARTFrame.parameter)
  {
  case 'v':
    if (m_Parameter1GraphEnabled == true)
    {
      if (m_PreviousYellow_X == m_TickCounter)
      {
        ++m_TickCounter;
        m_PreviousYellow_X = m_TickCounter;
      }
      else
      {
        m_PreviousYellow_X = m_TickCounter;
      }
      m_GraphYellow.addValue(m_TickCounter, m_Value);
    }
    break;
  case 'c':
    if (m_Parameter2GraphEnabled == true)
    {
      if (m_PreviousRed_X == m_TickCounter)
      {
        ++m_TickCounter;
        m_PreviousRed_X = m_TickCounter;
      }
      else
      {
        m_PreviousRed_X = m_TickCounter;
      }
      m_GraphRed.addValue(m_TickCounter, m_Value);
    }
    break;
  case 'f':
    if (m_Parameter3GraphEnabled == true)
    {
      if (m_PreviousBlue_X == m_TickCounter)
      {
        ++m_TickCounter;
        m_PreviousBlue_X = m_TickCounter;
      }
      else
      {
        m_PreviousBlue_X = m_TickCounter;
      }
      m_GraphBlue.addValue(m_TickCounter, m_Value);
    }
    break;
  case 'p':
    if (m_Parameter4GraphEnabled == true)
    {
      if (m_PreviousGreen_X == m_TickCounter)
      {
        ++m_TickCounter;
        m_PreviousGreen_X = m_TickCounter;
      }
      else
      {
        m_PreviousGreen_X = m_TickCounter;
      }
      m_GraphGreen.addValue(m_TickCounter, m_Value);
    }
    break;
  }
#endif
}

uint8_t Screen_Module1_GraphView::activeSignalsCount()
{
  /*How many signals active/visible?*/
  uint8_t activeSignals = 0;
  
  if (m_Parameter1GraphEnabled == true)
    ++activeSignals;
  if (m_Parameter2GraphEnabled == true)
    ++activeSignals;
  if (m_Parameter3GraphEnabled == true)
    ++activeSignals;
  if (m_Parameter4GraphEnabled == true)
    ++activeSignals;
  
  return activeSignals;
}

void Screen_Module1_GraphView::updateCpuUsage(uint8_t value)
{
  Unicode::snprintf(textArea_CPU_UsageBuffer, 4, "%d", value);
  textArea_CPU_Usage.invalidate();
}