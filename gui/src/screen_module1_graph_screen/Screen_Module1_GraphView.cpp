#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <string>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>
void DebugPrint(const char* ch);
#endif

#define GRAPH_RANGE_BOTTOM -1000
#define GRAPH_RANGE_TOP 1000
#define GRAPH_RANGE_LEFT 0
#define GRAPH_RANGE_RIGHT 720

Screen_Module1_GraphView::Screen_Module1_GraphView()
{

}

void Screen_Module1_GraphView::setupScreen()
{
  tickCounter = 0;
  
  // Place the graph on the screen
  graphYellow.setXY(55, 0);
  graphRed.setXY(55, 0);
  graphBlue.setXY(55, 0);
  graphGreen.setXY(55, 0);
  
  // Set the outer dimensions and color of the graph
  graphYellow.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC));
  graphRed.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00));
  graphBlue.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF));
  graphGreen.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00));
  
  // Set the range for the x and y axis of the graph. That is
  // the max and min x/y value that can be displayed inside the
  // dimension of the graph.
  graphYellow.setRange(GRAPH_RANGE_LEFT, GRAPH_RANGE_RIGHT, GRAPH_RANGE_BOTTOM, GRAPH_RANGE_TOP);
  graphRed.setRange(GRAPH_RANGE_LEFT, GRAPH_RANGE_RIGHT, GRAPH_RANGE_BOTTOM, GRAPH_RANGE_TOP);
  graphBlue.setRange(GRAPH_RANGE_LEFT, GRAPH_RANGE_RIGHT, GRAPH_RANGE_BOTTOM, GRAPH_RANGE_TOP);
  graphGreen.setRange(GRAPH_RANGE_LEFT, GRAPH_RANGE_RIGHT, GRAPH_RANGE_BOTTOM, GRAPH_RANGE_TOP);
  
  /*Initialize graph vertical range text areas */
  Unicode::snprintf(textArea_GraphRangeTopBuffer,6,"%d",graphYellow.getRangeTop());
  textArea_GraphRangeTop.invalidate();
  
  Unicode::snprintf(textArea_GraphRangeBottomBuffer,6,"%d",graphYellow.getRangeBottom());
  textArea_GraphRangeBottom.invalidate();
  
  // Set the line width in pixels
  graphYellow.setLineWidth(2);
  graphRed.setLineWidth(2);
  graphBlue.setLineWidth(2);
  graphGreen.setLineWidth(2);
  
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
#ifdef SIMULATOR
  static int value = GRAPH_RANGE_BOTTOM;
  
  /*Check if value is higher than graph upper range*/
  if(value >= graphYellow.getRangeTop())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), value);
    Unicode::snprintf(textArea_GraphRangeTopBuffer,6,"%d", value);
    textArea_GraphRangeTop.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if(value <= graphYellow.getRangeBottom())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), value, graphYellow.getRangeTop());
    Unicode::snprintf(textArea_GraphRangeBottomBuffer,6,"%d", value);
    textArea_GraphRangeBottom.invalidate();
  }
  
  if (tickCounter > GRAPH_RANGE_RIGHT)
  {
    graphYellow.setRange(graphYellow.getRangeLeft() + 1, graphYellow.getRangeRight() + 1, graphYellow.getRangeBottom(), graphYellow.getRangeTop());
    
    Unicode::snprintf(textArea_GraphRangeLeftBuffer, 6, "%d", graphYellow.getRangeLeft());
    textArea_GraphRangeLeft.invalidate();
    
    Unicode::snprintf(textArea_GraphRangeRightBuffer, 6, "%d", graphYellow.getRangeRight());
    textArea_GraphRangeRight.invalidate();
    
    /*Delete value which is no longer visible on graph*/
    graphYellow.deleteValue(graphYellow.getRangeRight() - GRAPH_RANGE_RIGHT);
  }
  
  //graphRed.addValue(tickCounter + 120, tickCounter);
  //graphBlue.addValue(tickCounter + 240, tickCounter);
  //graphGreen.addValue(tickCounter + 240, tickCounter);
  
  tickCounter++;
  value++;
  
  graphYellow.addValue(tickCounter, value);
#endif
}

void Screen_Module1_GraphView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
  BSP_LED_Toggle(LED3);
  
  value = std::stof((char*)(s_UARTFrame.payload));
  
  if(s_UARTFrame.sign == '2')
  {
    /*Make value_int negative*/
    value = value * (-1); 
  }
  
  //char str8[5];   
  //snprintf(str8, sizeof(uint8_t), "%f", value_float);   // convert uint8_t to string 
  //DebugPrint("\nRamka graphu ma wartosc: \n");
  //DebugPrint(str8);
  
  /*Check if value is higher than graph upper range*/
  if(value >= graphYellow.getRangeTop())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), value);
    //graphRed.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), value);
    //graphBlue.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), value);
    //graphGreen.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), value);
    
    Unicode::snprintf(textArea_GraphRangeTopBuffer,6,"%d", value);
    textArea_GraphRangeTop.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if(value <= graphYellow.getRangeBottom())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), value, graphYellow.getRangeTop());
    //graphRed.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), value, graphYellow.getRangeTop());
    //graphBlue.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), value, graphYellow.getRangeTop());
    //graphGreen.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), value, graphYellow.getRangeTop());
    
    Unicode::snprintf(textArea_GraphRangeBottomBuffer,6,"%d", value);
    textArea_GraphRangeBottom.invalidate();
  }
  
  if (tickCounter > GRAPH_RANGE_RIGHT)
  {
    graphYellow.setRange(graphYellow.getRangeLeft() + 1, graphYellow.getRangeRight() + 1, graphYellow.getRangeBottom(), graphYellow.getRangeTop());
    //graphRed.setRange(graphYellow.getRangeLeft() + 1, graphYellow.getRangeRight() + 1, graphYellow.getRangeBottom(), graphYellow.getRangeTop());
    //graphBlue.setRange(graphYellow.getRangeLeft() + 1, graphYellow.getRangeRight() + 1, graphYellow.getRangeBottom(), graphYellow.getRangeTop());
    //graphGreen.setRange(graphYellow.getRangeLeft() + 1, graphYellow.getRangeRight() + 1, graphYellow.getRangeBottom(), graphYellow.getRangeTop());
    
    Unicode::snprintf(textArea_GraphRangeLeftBuffer, 6, "%d", graphYellow.getRangeLeft());
    textArea_GraphRangeLeft.invalidate();
    
    Unicode::snprintf(textArea_GraphRangeRightBuffer, 6, "%d", graphYellow.getRangeRight());
    textArea_GraphRangeRight.invalidate();
    
    /*Delete value which is no longer visible on graph*/
    graphYellow.deleteValue(graphYellow.getRangeRight() - GRAPH_RANGE_RIGHT);
  }

  tickCounter++;
  value++;
  
  graphYellow.addValue(tickCounter, value);
  //graphRed.addValue(tickCounter + 40, value);
  //graphBlue.addValue(tickCounter + 80, value);
  //graphGreen.addValue(tickCounter + 120, value);
#endif
}

void Screen_Module1_GraphView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}