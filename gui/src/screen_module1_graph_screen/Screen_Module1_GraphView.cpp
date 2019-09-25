#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <string>
#include <cmath>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>
void DebugPrint(const char* ch);
#endif

#define INITIAL_GRAPH_RANGE_BOTTOM -1000
#define INITIAL_GRAPH_RANGE_TOP 1000
#define INITIAL_GRAPH_RANGE_LEFT 0
#define INITIAL_GRAPH_RANGE_RIGHT 720

#define GRAPHS_COUNT 4
#define SCALE_FACTOR 1000

bool Screen_Module1_GraphView::voltageGraphEnabled = true;
bool Screen_Module1_GraphView::currentGraphEnabled = true;
bool Screen_Module1_GraphView::frequencyGraphEnabled = true;
bool Screen_Module1_GraphView::powerGraphEnabled = true;
bool Screen_Module1_GraphView::autoRangeEnabled = false;

int Screen_Module1_GraphView::m_graphRangeBottom = INITIAL_GRAPH_RANGE_BOTTOM;
int Screen_Module1_GraphView::m_graphRangeTop = INITIAL_GRAPH_RANGE_TOP;
int Screen_Module1_GraphView::m_graphRangeRight = INITIAL_GRAPH_RANGE_RIGHT;

void Screen_Module1_GraphView::setGraphRanges(int bottom, int top, int right)
{
  m_graphRangeBottom = bottom;
  m_graphRangeTop = top;
  m_graphRangeRight = right;
}

Screen_Module1_GraphView::Screen_Module1_GraphView()
{
  m_graphRangeBottomChangedFlag = false;
  m_graphRangeTopChangedFlag = false;
  
  m_PreviousYellow_X = 0;
  m_PreviousRed_X = 0;
  m_PreviousBlue_X = 0;
  m_PreviousGreen_X = 0;
  
  tickCounter = 0;
  
  graphs[0] = &graphYellow;
  graphs[1] = &graphRed;
  graphs[2] = &graphBlue;
  graphs[3] = &graphGreen;
}

void Screen_Module1_GraphView::setupScreen()
{
  tickCounter = 0;
  
  // Set the outer dimensions and color of the graphs
  graphYellow.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), m_graphRangeBottom, m_graphRangeTop);
  graphRed.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00), m_graphRangeBottom, m_graphRangeTop);
  graphBlue.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF), m_graphRangeBottom, m_graphRangeTop);
  graphGreen.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00), m_graphRangeBottom, m_graphRangeTop);
  
  // Initialize graphs
  for(int i=0; i < GRAPHS_COUNT; i++)
  {
    // Place graphs on the screen
    graphs[i]->setXY(55, 0);
    // Set the ranges for the x and y axis of the graphs
    graphs[i]->setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
    // Set line width of the graphs
    graphs[i]->setLineWidth(2);
  }
  
  /*Initialize graph ranges text areas */
  Unicode::snprintf(textArea_GraphRangeTopBuffer,6,"%d", m_graphRangeTop / SCALE_FACTOR);
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer,6,"%d", m_graphRangeBottom / SCALE_FACTOR);
  textArea_GraphRangeBottom.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeRightBuffer,6,"%d", m_graphRangeRight);
  textArea_GraphRangeBottom.invalidate();
  
  add(graphYellow);
  add(graphRed);
  add(graphBlue);
  add(graphGreen);
  
  Screen_Module1_GraphViewBase::setupScreen();
}

void Screen_Module1_GraphView::tearDownScreen()
{
  Screen_Module1_GraphViewBase::tearDownScreen();
}

void Screen_Module1_GraphView::handleTickEvent()
{	
  if(autoRangeEnabled == true)
  {
    if(m_graphRangeBottomChangedFlag)
    {
      graphYellow.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      graphRed.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      graphBlue.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      graphGreen.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      
      Unicode::snprintf(textArea_GraphRangeBottomBuffer,6,"%d", m_graphRangeBottom / SCALE_FACTOR);
      textArea_GraphRangeBottom.invalidate();
      
      /*Reset flag*/
      m_graphRangeBottomChangedFlag = false;
    }
    
    if(m_graphRangeTopChangedFlag)
    {
      graphYellow.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      graphRed.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      graphBlue.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      graphGreen.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
      
      Unicode::snprintf(textArea_GraphRangeTopBuffer,6,"%d", m_graphRangeTop / SCALE_FACTOR);
      textArea_GraphRangeTop.invalidate();
      
      /*Reset flag*/
      m_graphRangeTopChangedFlag = false;
    }
  }
  
#ifdef SIMULATOR
  static int value1 = INITIAL_GRAPH_RANGE_BOTTOM;
  static int value2 = INITIAL_GRAPH_RANGE_BOTTOM + 40;
  static int value3 = INITIAL_GRAPH_RANGE_BOTTOM + 80;
  static int value4 = INITIAL_GRAPH_RANGE_BOTTOM + 120;
  
  /*Check if value is higher than graph upper range*/
  if(value1 >= graphYellow.getRangeTop())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), value1);
    Unicode::snprintf(textArea_GraphRangeTopBuffer,6,"%d", value1);
    textArea_GraphRangeTop.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if(value1 <= graphYellow.getRangeBottom())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), value1, graphYellow.getRangeTop());
    Unicode::snprintf(textArea_GraphRangeBottomBuffer,6,"%d", value1);
    textArea_GraphRangeBottom.invalidate();
  }
  
  /*Check if value is higher than graph upper range*/
  if (value2 >= graphRed.getRangeTop())
  {
    graphRed.setRange(graphRed.getRangeLeft(), graphRed.getRangeRight(), graphRed.getRangeBottom(), value2);
    Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", value2);
    textArea_GraphRangeTop.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if (value2 <= graphRed.getRangeBottom())
  {
    graphRed.setRange(graphRed.getRangeLeft(), graphRed.getRangeRight(), value2, graphRed.getRangeTop());
    Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", value2);
    textArea_GraphRangeBottom.invalidate();
  }
  
  /*Check if value is higher than graph upper range*/
  if (value3 >= graphBlue.getRangeTop())
  {
    graphBlue.setRange(graphBlue.getRangeLeft(), graphBlue.getRangeRight(), graphBlue.getRangeBottom(), value3);
    Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", value3);
    textArea_GraphRangeTop.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if (value3 <= graphBlue.getRangeBottom())
  {
    graphBlue.setRange(graphBlue.getRangeLeft(), graphBlue.getRangeRight(), value3, graphBlue.getRangeTop());
    Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", value3);
    textArea_GraphRangeBottom.invalidate();
  }
  
  /*Check if value is higher than graph upper range*/
  if (value4 >= graphGreen.getRangeTop())
  {
    graphGreen.setRange(graphGreen.getRangeLeft(), graphGreen.getRangeRight(), graphGreen.getRangeBottom(), value4);
    Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", value4);
    textArea_GraphRangeTop.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if (value4 <= graphGreen.getRangeBottom())
  {
    graphGreen.setRange(graphGreen.getRangeLeft(), graphGreen.getRangeRight(), value4, graphGreen.getRangeTop());
    Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", value4);
    textArea_GraphRangeBottom.invalidate();
  }
    
  if (voltageGraphEnabled)
  {
    graphYellow.addValue(tickCounter, value1);
  }
  
  if (currentGraphEnabled)
  {
    graphRed.addValue(tickCounter, value2 + 20);
  }
  
  if (frequencyGraphEnabled)
  {
    graphBlue.addValue(tickCounter, value3 + 40);
  }
  if (powerGraphEnabled)
  {
    graphGreen.addValue(tickCounter, value4 + 60);
  }
  
  tickCounter++;
  value1++;
  value2++;
  value3++;
  value4++;
  
  if (tickCounter >= m_graphRangeRight)
  {
    graphYellow.clear();
    graphYellow.invalidate();
    
    graphRed.clear();
    graphRed.invalidate();
    
    graphBlue.clear();
    graphBlue.invalidate();
    
    graphGreen.clear();
    graphGreen.invalidate();
    
    tickCounter = 0;
  }
  
#endif
}

void Screen_Module1_GraphView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
  BSP_LED_Toggle(LED3);
  
  value = int(std::stof((char*)(s_UARTFrame.payload)) * SCALE_FACTOR); //scale by 1000
    
  if(s_UARTFrame.sign == '2')
  {
    /*Make value_int negative*/
    value = value * (-1); 
  }
  
  //char str8[5];   
  //snprintf(str8, sizeof(uint8_t), "%f", value_float);   // convert uint8_t to string 
  //DebugPrint("\nRamka graphu ma wartosc: \n");
  //DebugPrint(str8);
  
  if(autoRangeEnabled == true)
  {
    for(int i=0; i < GRAPHS_COUNT; i++)
    {
      /*Check if value is higher than any graph's top range*/
      if(value > graphs[i]->getRangeTop())
      {
        m_graphRangeTopChangedFlag = true;
        m_graphRangeTop = value;
      }
      /*Check if value is lower than graph bottom range*/
      else if(value < graphs[i]->getRangeBottom())
      {
        m_graphRangeBottomChangedFlag = true;
        m_graphRangeBottom = value;
      }
    }
  }
  
  if(tickCounter >= m_graphRangeRight)
  {
    graphYellow.clear();
    graphYellow.invalidate();
    
    graphRed.clear();
    graphRed.invalidate();
    
    graphBlue.clear();
    graphBlue.invalidate();
    
    graphGreen.clear();
    graphGreen.invalidate();
    
    m_PreviousYellow_X = 0;
    m_PreviousRed_X = 0;
    m_PreviousBlue_X = 0;
    m_PreviousGreen_X = 0;
    
    tickCounter = 0;
  }
  
  char str_bottom[10] = {'\0'};
  snprintf(str_bottom, 3 * sizeof(int), "%d", m_graphRangeBottom);   // convert uint8_t to string 
  DebugPrint("\nGraph bottom range: ");
  DebugPrint(str_bottom);
  DebugPrint("\n");
  
  char str_top[10] = {'\0'};
  snprintf(str_top, 3 * sizeof(int), "%d", m_graphRangeTop);   // convert uint8_t to string 
  DebugPrint("\nGraph top range: ");
  DebugPrint(str_top);
  DebugPrint("\n");
  
  char str_value[10] = {'\0'};
  snprintf(str_value, 3 * sizeof(int), "%d", value);   // convert uint8_t to string 
  DebugPrint("\nValue after scaling: ");
  DebugPrint(str_value);
  DebugPrint("\n");
  
  switch(s_UARTFrame.parameter)
  {
  case 'v':
    if(voltageGraphEnabled == true)
    {
      if(m_PreviousYellow_X == tickCounter)
      {
        ++tickCounter; 
        m_PreviousYellow_X = tickCounter;
      }
      else
      {
        m_PreviousYellow_X = tickCounter;
      }
      graphYellow.addValue(tickCounter, value);
    }
    break;
  case 'c':
    if(currentGraphEnabled == true)
    {
      if(m_PreviousRed_X == tickCounter)
      {
        ++tickCounter; 
        m_PreviousRed_X = tickCounter;
      }
      else
      {
        m_PreviousRed_X = tickCounter;
      }
      graphRed.addValue(tickCounter, value);
    }
    break;
  case 'f':
    if(frequencyGraphEnabled == true)
    {
      if(m_PreviousBlue_X == tickCounter)
      {
        ++tickCounter; 
        m_PreviousBlue_X = tickCounter;
      }
      else
      {
        m_PreviousBlue_X = tickCounter;
      }
      graphBlue.addValue(tickCounter, value);
    }
    break;
  case 'p':
    if(powerGraphEnabled == true)
    {
      if(m_PreviousGreen_X == tickCounter)
      {
        ++tickCounter; 
        m_PreviousGreen_X = tickCounter;
      }
      else
      {
        m_PreviousGreen_X = tickCounter;
      }
      graphGreen.addValue(tickCounter, value);
    }
    break;
  }
#endif
}

uint8_t Screen_Module1_GraphView::activeSignalsCount()
{
  /*How many signals active/visible?*/
  uint8_t activeSignals = 0;
  
  if(voltageGraphEnabled == true)
    ++activeSignals;
  if(currentGraphEnabled == true)
    ++activeSignals;
  if(frequencyGraphEnabled == true)
    ++activeSignals;
  if(powerGraphEnabled == true)
    ++activeSignals;
  
  return activeSignals;
}

void Screen_Module1_GraphView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}