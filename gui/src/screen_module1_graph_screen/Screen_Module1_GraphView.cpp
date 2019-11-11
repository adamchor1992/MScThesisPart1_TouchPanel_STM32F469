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
    
    m_Graphs[i]->setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
    
    m_TimeBase = 0;
  }
  
  /*Initialize graph ranges text areas */
  Unicode::snprintf(textArea_GraphRangeTopBuffer, 12, "%d", m_GraphRangeTop);
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer, 12, "%d", m_GraphRangeBottom);
  textArea_GraphRangeBottom.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeRightBuffer, 12, "%d", m_GraphRangeRight);
  textArea_GraphRangeRight.invalidate();
}

Screen_Module1_GraphView::Screen_Module1_GraphView()
{
  m_GraphRangeBottomChangedFlag = false;
  m_GraphRangeTopChangedFlag = false;
  
  m_PreviousYellow_X = 0;
  m_PreviousRed_X = 0;
  m_PreviousBlue_X = 0;
  m_PreviousGreen_X = 0;
  
  m_TimeBase = 0;
  
  m_Graphs[0] = &m_GraphYellow;
  m_Graphs[1] = &m_GraphRed;
  m_Graphs[2] = &m_GraphBlue;
  m_Graphs[3] = &m_GraphGreen;
}

void Screen_Module1_GraphView::setupScreen()
{
#ifndef SIMULATOR
  /*Restart UART RX*/
  extern UartPacket uartPacket;
  
  HAL_UART_DeInit(Model::m_pHuart6);
  HAL_UART_Init(Model::m_pHuart6);
  
  NVIC_EnableIRQ(USART6_IRQn);
  
  HAL_UART_Receive_IT(Model::m_pHuart6, uartPacket.getPacketTable(), PACKET_SIZE);
#endif
  
  m_TimeBase = 0;
  
  // Set the outer dimensions and color of the graphs
  m_GraphYellow.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  m_GraphRed.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00), m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  m_GraphBlue.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF), m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  m_GraphGreen.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00), m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  
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
  static int value = INITIAL_GRAPH_RANGE_BOTTOM;
  
  static int valueGraph;
  
  valueGraph = int((((1 - (double(m_GraphRangeTop - value) / double(m_GraphRangeTop - m_GraphRangeBottom)))) * GRAPH_CONSTANT_MAX_MIN_INTERVAL) - GRAPH_CONSTANT_RANGE_TOP);
  
  static bool rising = true;
  
  static int multiplier = 1;
  
  const static int increment = 10;
  
  if (rising)
  {
    value = value + increment;
  }
  else
  {
    value = value - increment;
  }
  
  if (value >= 10000)
  {
    rising = false;
  }
  else if(value <= -10000)
  {
    rising = true;
  }
  
  m_TimeBase += 1;
  
  //value = multiplier * sin(m_TimeBase * 3.14159/180) * 100.0;
  
  if (m_TimeBase >= m_GraphRangeRight)
  {
    m_GraphYellow.clear();
    m_GraphYellow.invalidate();
    
    m_PreviousYellow_X = 0;
    
    m_TimeBase = 0;
  }
  
  //touchgfx_printf("Graph bottom range %d\n", m_GraphRangeBottom);
  //touchgfx_printf("Graph bottom range %d\n", m_GraphYellow.getRangeBottom());
  //touchgfx_printf("Graph top range %d\n", m_GraphYellow.getRangeTop());
  //touchgfx_printf("Value1 after scaling %d\n", value);
  
  if (m_Parameter1GraphEnabled == true)
  {
    if (m_PreviousYellow_X == m_TimeBase)
    {
      ++m_TimeBase;
      m_PreviousYellow_X = m_TimeBase;
    }
    else
    {
      m_PreviousYellow_X = m_TimeBase;
    }
    
    m_GraphYellow.addValue(m_TimeBase, valueGraph);
  }
#endif
}

void Screen_Module1_GraphView::addNewValueToGraphFromUart(UartPacket & uartPacket)
{
#ifndef SIMULATOR
  BSP_LED_Toggle(LED3);
  
  int value = int(std::stof((char*)(uartPacket.getPayload())));
  
  value = int((((1 - (double(m_GraphRangeTop - value) / double(m_GraphRangeTop - m_GraphRangeBottom)))) * GRAPH_CONSTANT_MAX_MIN_INTERVAL) - GRAPH_CONSTANT_RANGE_TOP);
  
  if (uartPacket.getSign() == Sign::NEGATIVE_SIGN)
  {
    /*Make value_int negative*/
    value = value * (-1);
  }
  
  if (m_AutoRangeEnabled == true)
  {
    for (int i = 0; i < GRAPHS_COUNT; i++)
    {
      /*Check if value is higher than any graph's top range*/
      if (value > m_Graphs[i]->getRangeTop())
      {
        m_GraphRangeTopChangedFlag = true;
        m_GraphRangeTop = value;
      }
      /*Check if value is lower than graph bottom range*/
      else if (value < m_Graphs[i]->getRangeBottom())
      {
        m_GraphRangeBottomChangedFlag = true;
        m_GraphRangeBottom = value;
      }
    }
  }
  
  if (m_TimeBase >= m_GraphRangeRight)
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
    
    m_TimeBase = 0;
  }
  
  printf("Graph real bottom range: %d\n", m_GraphYellow.getRangeBottom());
  printf("Graph real top range: %d\n", m_GraphYellow.getRangeTop());
  printf("Graph virtual bottom range: %d\n", m_GraphRangeBottom);
  printf("Graph virtual top range: %d\n", m_GraphRangeTop);
  printf("Value after scaling: %d\n", value);
  
  switch (uartPacket.getParameter())
  {
  case Parameter::VOLTAGE_PARAMETER:
    if (m_Parameter1GraphEnabled == true)
    {
      if (m_PreviousYellow_X == m_TimeBase)
      {
        ++m_TimeBase;
        m_PreviousYellow_X = m_TimeBase;
      }
      else
      {
        m_PreviousYellow_X = m_TimeBase;
      }
      m_GraphYellow.addValue(m_TimeBase, value);
    }
    break;
  case Parameter::CURRENT_PARAMETER:
    if (m_Parameter2GraphEnabled == true)
    {
      if (m_PreviousRed_X == m_TimeBase)
      {
        ++m_TimeBase;
        m_PreviousRed_X = m_TimeBase;
      }
      else
      {
        m_PreviousRed_X = m_TimeBase;
      }
      m_GraphRed.addValue(m_TimeBase, value);
    }
    break;
  case Parameter::FREQUENCY_PARAMETER:
    if (m_Parameter3GraphEnabled == true)
    {
      if (m_PreviousBlue_X == m_TimeBase)
      {
        ++m_TimeBase;
        m_PreviousBlue_X = m_TimeBase;
      }
      else
      {
        m_PreviousBlue_X = m_TimeBase;
      }
      m_GraphBlue.addValue(m_TimeBase, value);
    }
    break;
  case Parameter::POWER_PARAMETER:
    if (m_Parameter4GraphEnabled == true)
    {
      if (m_PreviousGreen_X == m_TimeBase)
      {
        ++m_TimeBase;
        m_PreviousGreen_X = m_TimeBase;
      }
      else
      {
        m_PreviousGreen_X = m_TimeBase;
      }
      m_GraphGreen.addValue(m_TimeBase, value);
    }
    break;
  }
#endif
}

void Screen_Module1_GraphView::setNewGraphRange(UartPacket & uartPacket)
{
  int newValue = 0;
  
  printf("Dlugosc pakietu jako znak %c\n", uartPacket.getLength());
  printf("Dlugosc pakietu jako liczba %d\n", uartPacket.getLength());
  printf("Payload pakietu %.10s\n", uartPacket.getPayload());
  
  switch(uartPacket.getFunction())
  {
  case Function::SET_GRAPH_RANGE_MIN:
    newValue = int(std::stof((char*)(uartPacket.getPayload())));
    
    printf("New minimum value after casting to int: %d\n", newValue);
    
    if(uartPacket.getSign() == Sign::NEGATIVE_SIGN)
    {
      newValue = newValue * (-1);
    }
    
    setGraphRanges(newValue, m_GraphRangeTop, m_GraphRangeRight);
    
    resetGraph();
    
    break;
    
  case Function::SET_GRAPH_RANGE_MAX:    
    newValue = int(std::stof((char*)(uartPacket.getPayload())));
    
    printf("New maximum value after casting to int: %d\n", newValue);
    
    if(uartPacket.getSign() == Sign::NEGATIVE_SIGN)
    {
      newValue = newValue * (-1);
    }
    
    setGraphRanges(m_GraphRangeBottom, newValue, m_GraphRangeRight);
    
    resetGraph();
    
    break;
    
  case Function::SET_GRAPH_TIME_RANGE:    
    newValue = int(std::stof((char*)(uartPacket.getPayload())));
    
    printf("New time range value after casting to int: %d\n", newValue);
    
    if(uartPacket.getSign() == Sign::NEGATIVE_SIGN)
    {
      printf("Time range cannot be negative, packet discarded\n");
      return;
    }
    
    setGraphRanges(m_GraphRangeBottom, m_GraphRangeTop, newValue);
    
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