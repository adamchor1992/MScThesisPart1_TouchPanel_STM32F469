#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <string>
#include "stm32469i_discovery.h"

/*Real graph range minimum value which is used for graph drawing. 
Values to be drawn on graph are scaled in terms of this value*/
const int GRAPH_CONSTANT_RANGE_BOTTOM = -2500;
/*Real graph range maximum value which is used for graph drawing. 
Values to be drawn on graph are scaled in terms of this value*/
const int GRAPH_CONSTANT_RANGE_TOP = +2500;
/*Real graph resolution (Number of distinct points which can be drawn on Y axis)*/
const int GRAPH_CONSTANT_MAX_MIN_INTERVAL = 5000;

const int INITIAL_GRAPH_RANGE_BOTTOM = -10000;
const int INITIAL_GRAPH_RANGE_TOP = 10000;
const int INITIAL_GRAPH_RANGE_LEFT = 0;
const int INITIAL_GRAPH_RANGE_RIGHT = 720;

const int GRAPHS_COUNT = 4;

bool Screen_Module1_GraphView::m_Parameter1GraphEnabled = true;
bool Screen_Module1_GraphView::m_Parameter2GraphEnabled = true;
bool Screen_Module1_GraphView::m_Parameter3GraphEnabled = true;
bool Screen_Module1_GraphView::m_Parameter4GraphEnabled = true;
bool Screen_Module1_GraphView::m_AutoRangeEnabled = false;

long long int Screen_Module1_GraphView::m_GraphRangeBottom = INITIAL_GRAPH_RANGE_BOTTOM;
long long int Screen_Module1_GraphView::m_GraphRangeTop = INITIAL_GRAPH_RANGE_TOP;
int Screen_Module1_GraphView::m_GraphRangeRight = INITIAL_GRAPH_RANGE_RIGHT;

Screen_Module1_GraphView::Screen_Module1_GraphView()
{
  m_PreviousYellow_X = 0;
  m_PreviousRed_X = 0;
  m_PreviousBlue_X = 0;
  m_PreviousGreen_X = 0;
  
  m_Graphs[0] = &m_GraphYellow;
  m_Graphs[1] = &m_GraphRed;
  m_Graphs[2] = &m_GraphBlue;
  m_Graphs[3] = &m_GraphGreen;
  
  m_TimeBase = 0;
}

void Screen_Module1_GraphView::setupScreen()
{  
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
  
  /*Initialize graph range text areas */
  SetGraphRangeTextAreas(m_GraphRangeBottom, m_GraphRangeTop, m_GraphRangeRight);
  
  add(m_GraphYellow);
  add(m_GraphRed);
  add(m_GraphBlue);
  add(m_GraphGreen);
}

void Screen_Module1_GraphView::SetGraphRanges(long long int bottom, long long int top, int right)
{
  m_GraphRangeBottom = bottom;
  m_GraphRangeTop = top;
  m_GraphRangeRight = right;
}

void Screen_Module1_GraphView::SetGraphRangeTextAreas(long long int bottom, long long int top, int right)
{
  /*Buffer for range bottom string - up to 10 digits + optional sign + null character*/
  char graphRangeBottomString[PAYLOAD_SIZE + 2];
  char graphRangeTopString[PAYLOAD_SIZE + 2];
  
  snprintf(graphRangeBottomString, PAYLOAD_SIZE + 2, "%lld", bottom);
  snprintf(graphRangeTopString, PAYLOAD_SIZE + 2, "%lld", top);
  
  Unicode::UnicodeChar graphRangeBottomUnicodeString[PAYLOAD_SIZE + 2];
  Unicode::UnicodeChar graphRangeTopUnicodeString[PAYLOAD_SIZE + 2];
  
  Unicode::strncpy(graphRangeBottomUnicodeString, graphRangeBottomString, PAYLOAD_SIZE + 2);
  Unicode::strncpy(graphRangeTopUnicodeString, graphRangeTopString, PAYLOAD_SIZE + 2);
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer, PAYLOAD_SIZE + 2, "%s", graphRangeBottomUnicodeString);
  textArea_GraphRangeBottom.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeTopBuffer, PAYLOAD_SIZE + 2, "%s", graphRangeTopUnicodeString);
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeRightBuffer, PAYLOAD_SIZE + 2, "%d", right);
  textArea_GraphRangeRight.invalidate();
}

void Screen_Module1_GraphView::ResetGraph()
{
  for (int i = 0; i < GRAPHS_COUNT; i++)
  {
    m_Graphs[i]->clear();
    m_Graphs[i]->invalidate();
    m_Graphs[i]->setRange(INITIAL_GRAPH_RANGE_LEFT, m_GraphRangeRight, GRAPH_CONSTANT_RANGE_BOTTOM, GRAPH_CONSTANT_RANGE_TOP);
  }
  
  m_TimeBase = 0;
  
  m_PreviousYellow_X = 0;
  m_PreviousRed_X = 0;
  m_PreviousBlue_X = 0;
  m_PreviousGreen_X = 0;
  
  SetGraphRangeTextAreas(m_GraphRangeBottom, m_GraphRangeTop, m_GraphRangeRight);
}

void Screen_Module1_GraphView::handleTickEvent()
{
#ifdef SIMULATOR
  static long long int value = INITIAL_GRAPH_RANGE_BOTTOM;
  
  static long long int valueGraph;
  
  valueGraph = long long int((((1 - (double(m_GraphRangeTop - value) / double(m_GraphRangeTop - m_GraphRangeBottom)))) * GRAPH_CONSTANT_MAX_MIN_INTERVAL) - GRAPH_CONSTANT_RANGE_TOP);
  
  static bool rising = true;
  
  static int multiplier = 1;
  
  static const int increment = 10;
  
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
  
  if (m_TimeBase >= m_GraphRangeRight)
  {
    m_GraphYellow.clear();
    m_GraphYellow.invalidate();
    
    m_PreviousYellow_X = 0;
    
    m_TimeBase = 0;
  }
  
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

void Screen_Module1_GraphView::AddNewValueToGraphFromUart(UartPacket& uartPacket)
{
#ifndef SIMULATOR
  
  /*Skip packet if it is not addressed to this module*/
  if(uartPacket.GetModule() != ModuleID::MODULE1)
  {
    BSP_LED_On(LED2);
    
    printf("Packet skipped because it is not addressed to current module (1)\n");
    return;
  }
  
  long long int rawValue;
  int scaledValue;
  
  static uint8_t numericValueBuffer[PAYLOAD_SIZE];
  
  uartPacket.GetPayload(numericValueBuffer);
  
  rawValue = std::stoll(reinterpret_cast<const char*>(numericValueBuffer));
  
  if (uartPacket.GetSign() == Sign::NEGATIVE_SIGN)
  {
    /*Make rawValue negative*/
    rawValue = rawValue * (-1);
  }
  
  if (m_AutoRangeEnabled == true)
  { 
    /*Check if raw value is higher than graph's top range*/
    if (rawValue > m_GraphRangeTop)
    { 
      m_GraphRangeTop = rawValue;
      
      SetGraphRangeTextAreas(m_GraphRangeBottom, m_GraphRangeTop, m_GraphRangeRight);
    }
    /*Check if raw value is lower than graph bottom range*/
    else if (rawValue < m_GraphRangeBottom)
    {
      m_GraphRangeBottom = rawValue;
      
      SetGraphRangeTextAreas(m_GraphRangeBottom, m_GraphRangeTop, m_GraphRangeRight);
    }
  }
  
  scaledValue = int((((1 - (double(m_GraphRangeTop - rawValue) / double(m_GraphRangeTop - m_GraphRangeBottom)))) * GRAPH_CONSTANT_MAX_MIN_INTERVAL) - GRAPH_CONSTANT_RANGE_TOP);
  
  printf("Value after scaling: %d\n", scaledValue);
  
  /*If autorange is not enabled the scaled value must be constrained within constant upper and lower graph range*/
  if(m_AutoRangeEnabled == false)
  {
    if(scaledValue > GRAPH_CONSTANT_RANGE_TOP)
    {
      scaledValue = GRAPH_CONSTANT_RANGE_TOP;
    }
    else if(scaledValue < GRAPH_CONSTANT_RANGE_BOTTOM)
    {
      scaledValue = GRAPH_CONSTANT_RANGE_BOTTOM;
    }
  }
  
  if (m_TimeBase >= m_GraphRangeRight)
  {
    ResetGraph();
  }
  
  switch (uartPacket.GetParameter())
  {
  case Parameter::GRAPH_PARAMETER1:
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
      m_GraphYellow.addValue(m_TimeBase, scaledValue);
    }
    break;
    
  case Parameter::GRAPH_PARAMETER2:
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
      m_GraphRed.addValue(m_TimeBase, scaledValue);
    }
    break;
    
  case Parameter::GRAPH_PARAMETER3:
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
      m_GraphBlue.addValue(m_TimeBase, scaledValue);
    }
    break;
    
  case Parameter::GRAPH_PARAMETER4:
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
      m_GraphGreen.addValue(m_TimeBase, scaledValue);
    }
    break;
    
  }
#endif
}

void Screen_Module1_GraphView::SetNewGraphRange(UartPacket& uartPacket)
{
#ifndef SIMULATOR
  
  /*Skip packet if it is not addressed to this module*/
  if(uartPacket.GetModule() != ModuleID::MODULE1)
  {
    BSP_LED_On(LED2);
    
    printf("Packet skipped because it is not addressed to current module (1)\n");
    return;
  }
  
  switch(uartPacket.GetFunction())
  {
  case Function::SET_GRAPH_RANGE_MIN:
    static long long int newGraphRangeMinValue = 0;
    
    newGraphRangeMinValue = std::stoll((char*)(uartPacket.GetPayload()));
    
    if(uartPacket.GetSign() == Sign::NEGATIVE_SIGN)
    {
      newGraphRangeMinValue = newGraphRangeMinValue * (-1);
    }
    
    if(newGraphRangeMinValue >= m_GraphRangeTop)
    {
      BSP_LED_On(LED2);
      
      printf("New graph range minimum value (%lld) is higher than or equal to current graph maximum value (%lld), aborting\n", newGraphRangeMinValue, m_GraphRangeTop); 
      
      return;
    }
    
    SetGraphRanges(newGraphRangeMinValue, m_GraphRangeTop, m_GraphRangeRight);
    
    ResetGraph();
    
    break;
    
  case Function::SET_GRAPH_RANGE_MAX: 
    static long long int newGraphRangeMaxValue = 0;
    
    newGraphRangeMaxValue = std::stoll((char*)(uartPacket.GetPayload()));
    
    if(uartPacket.GetSign() == Sign::NEGATIVE_SIGN)
    {
      newGraphRangeMaxValue = newGraphRangeMaxValue * (-1);
    }
    
    if(newGraphRangeMaxValue <= m_GraphRangeBottom)
    {
      BSP_LED_On(LED2);
      
      printf("New graph range maximum value (%lld) is lower than or equal to current graph minimum value (%lld), aborting\n", newGraphRangeMaxValue, m_GraphRangeBottom); 
      
      return;
    }
    
    SetGraphRanges(m_GraphRangeBottom, newGraphRangeMaxValue, m_GraphRangeRight);
    
    ResetGraph();
    
    break;
    
  case Function::SET_GRAPH_TIME_RANGE:    
    static int newTimeRangeValue = 0;
    
    newTimeRangeValue = std::stoi((char*)(uartPacket.GetPayload()));
    
    if(uartPacket.GetSign() == Sign::NEGATIVE_SIGN)
    {
      BSP_LED_On(LED2);
      
      printf("Time range cannot be negative, packet discarded\n");
      return;
    }
    
    SetGraphRanges(m_GraphRangeBottom, m_GraphRangeTop, newTimeRangeValue);
    
    ResetGraph();
    
    break;
    
  default:
    BSP_LED_On(LED2);
    
    printf("Unknown function in graph view\n");
  }
#endif
}

uint8_t Screen_Module1_GraphView::ActiveSignalsCount()
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

void Screen_Module1_GraphView::UpdateCpuUsage(uint8_t value)
{
  Unicode::snprintf(textArea_CPU_UsageBuffer, 4, "%d", value);
  textArea_CPU_Usage.invalidate();
}