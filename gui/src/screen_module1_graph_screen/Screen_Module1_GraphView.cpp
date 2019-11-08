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

#define GRAPH_CONSTANT_RANGE_BOTTOM -2500
#define GRAPH_CONSTANT_RANGE_TOP +2500
#define GRAPH_CONSTANT_MAX_MIN_INTERVAL 5000

#define INITIAL_GRAPH_RANGE_BOTTOM -10000
#define INITIAL_GRAPH_RANGE_TOP 10000
#define INITIAL_GRAPH_RANGE_LEFT 0
#define INITIAL_GRAPH_RANGE_RIGHT 720

#define GRAPHS_COUNT 4

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

void Screen_Module1_GraphView::resetGraph()
{
  for (int i = 0; i < GRAPHS_COUNT; i++)
  {
    m_Graphs[i]->clear();
    m_Graphs[i]->invalidate();
    
    m_TickCounter = 0;
  }
  
  /*Initialize graph ranges text areas */
  Unicode::snprintf(textArea_GraphRangeTopBuffer, 12, "%d", m_GraphRangeTop);
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer, 12, "%d", m_GraphRangeBottom);
  textArea_GraphRangeBottom.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeRightBuffer, 10, "%d", m_GraphRangeRight);
  textArea_GraphRangeBottom.invalidate();
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
  extern uint8_t uartReceivedPacket[PACKET_SIZE];
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, uartReceivedPacket, PACKET_SIZE);
#endif
  
  m_TickCounter = 0;
  
  // Set the outer dimensions and color of the graphs
  m_GraphYellow.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  m_GraphRed.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00), GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  m_GraphBlue.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF), GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  m_GraphGreen.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00), GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  
  // Initialize graphs
  for (int i = 0; i < GRAPHS_COUNT; i++)
  {
    // Place graphs on the screen
    m_Graphs[i]->setXY(55, 0);
    // Set the ranges for the x and y axis of the graphs
    m_Graphs[i]->setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
    // Set line width of the graphs
    m_Graphs[i]->setLineWidth(1);
  }
  
  /*Initialize graph ranges text areas */
  Unicode::snprintf(textArea_GraphRangeTopBuffer, 12, "%d", m_GraphRangeTop);
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer, 12, "%d", m_GraphRangeBottom);
  textArea_GraphRangeBottom.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeRightBuffer, 10, "%d", m_GraphRangeRight);
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
#ifdef SIMULATOR
  static int value1 = INITIAL_GRAPH_RANGE_BOTTOM;
  
  static int valueGraph;

  valueGraph = int((((1 - (double(m_GraphRangeTop - value1) / double(m_GraphRangeTop - m_GraphRangeBottom)))) * GRAPH_CONSTANT_MAX_MIN_INTERVAL) - GRAPH_CONSTANT_RANGE_TOP);

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
  
  if (value1 >= 10000)
  {
    rising = false;
  }
  else if(value1 <= -10000)
  {
    rising = true;
  }
  
  m_TickCounter += 1;
  
  //value1 = multiplier * sin(m_TickCounter * 3.14159/180) * 100.0;
  
  if (m_TickCounter >= m_GraphRangeRight)
  {
    m_GraphYellow.clear();
    m_GraphYellow.invalidate();
    
    m_PreviousYellow_X = 0;
    
    m_TickCounter = 0;
  }
  
  //touchgfx_printf("Graph bottom range %d\n", m_GraphRangeBottom);
  //touchgfx_printf("Graph bottom range %d\n", m_GraphYellow.getRangeBottom());
  //touchgfx_printf("Graph top range %d\n", m_GraphYellow.getRangeTop());
  //touchgfx_printf("Value1 after scaling %d\n", value1);
  
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

    m_GraphYellow.addValue(m_TickCounter, valueGraph);
  }
#endif
}

void Screen_Module1_GraphView::addNewValueToGraphFromUART(UartPacket & uartPacket)
{
#ifndef SIMULATOR
  BSP_LED_Toggle(LED3);
  
  m_Value = int(std::stof((char*)(uartPacket.payload)));
  
  m_Value = int((((1 - (double(m_GraphRangeTop - m_Value) / double(m_GraphRangeTop - m_GraphRangeBottom)))) * GRAPH_CONSTANT_MAX_MIN_INTERVAL) - GRAPH_CONSTANT_RANGE_TOP);
    
  if (uartPacket.sign == '2')
  {
    /*Make value_int negative*/
    m_Value = m_Value * (-1);
  }
  
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
  
  printf("Graph real bottom range: %d\n", m_GraphYellow.getRangeBottom());
  printf("Graph real top range: %d\n", m_GraphYellow.getRangeTop());
  printf("Graph virtual bottom range: %d\n", m_GraphRangeBottom);
  printf("Graph virtual top range: %d\n", m_GraphRangeTop);
  printf("Value after scaling: %d\n", m_Value);
  
  switch (uartPacket.parameter)
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

void Screen_Module1_GraphView::setNewGraphRange(UartPacket & uartPacket)
{
  int value = 0;
  
  switch(uartPacket.function)
  {
  case '7':
    value = int(std::stof((char*)(uartPacket.payload)));
    
    if(uartPacket.sign == '2')
    {
      value = value * (-1);
    }
    
    setGraphRanges(value, m_GraphRangeTop, m_GraphRangeRight);
    
    resetGraph();
    
    break;
    
  case '8':    
    value = int(std::stof((char*)(uartPacket.payload)));
    
    if(uartPacket.sign == '2')
    {
      value = value * (-1);
    }
    
    setGraphRanges(m_GraphRangeBottom, value, m_GraphRangeRight);
    
    resetGraph();
    
    break;
    
  default:
    printf("Unknown function in graph view\n");
  }
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