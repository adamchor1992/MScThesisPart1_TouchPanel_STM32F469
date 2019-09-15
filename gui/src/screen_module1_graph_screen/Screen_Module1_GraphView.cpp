#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <string>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>
void DebugPrint(const char* ch);
#endif

Screen_Module1_GraphView::Screen_Module1_GraphView()
{

}

void Screen_Module1_GraphView::setupScreen()
{
  tickCounter = 0;
  
  background.setXY(100, -100);
  background.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
  add(background);
  
  // Place the graph on the screen
  graphYellow.setXY(0, 0);
  graphRed.setXY(0, 0);
  graphBlue.setXY(0, 0);
  
  // Set the outer dimensions and color of the graph
  graphYellow.setup(800, 375, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC));
  graphRed.setup(800, 375, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00));
  graphBlue.setup(800, 375, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF));
  
  // Set the range for the x and y axis of the graph. That is
  // the max and min x/y value that can be displayed inside the
  // dimension of the graph.
  graphYellow.setRange(0, 1440, -1000, 1000);
  graphRed.setRange(0, 1440, -1000, 1000);
  graphBlue.setRange(0, 1440, -1000, 1000);
  
  // Set the line width in pixels
  graphYellow.setLineWidth(2);
  graphRed.setLineWidth(2);
  graphBlue.setLineWidth(2);
  
  add(graphYellow);
  add(graphRed);
  add(graphBlue);
  
  Screen_Module1_GraphViewBase::setupScreen();
}

void Screen_Module1_GraphView::tearDownScreen()
{
    Screen_Module1_GraphViewBase::tearDownScreen();
}

void Screen_Module1_GraphView::handleTickEvent()
{
  
}

void Screen_Module1_GraphView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
  if(s_UARTFrame.sign == '1')
  {
    isNegative = false;
  }
  else if(s_UARTFrame.sign == '2')
  {
    isNegative = true;
  }
  
  value_float = std::stof((char*)(s_UARTFrame.payload));
  
  BSP_LED_Toggle(LED3);
  
  if(isNegative)
  {
    /*Make value_int negative*/
    value_float = value_float * (-1); 
  }
  
  //char str8[5];   
  
  //snprintf(str8, sizeof(uint8_t), "%f", value_float);   // convert uint8_t to string 
  
  //DebugPrint("\nRamka graphu ma wartosc: \n");
  //DebugPrint(str8);
  
  /*Check if value is higher than graph upper range*/
  if(int(value_float) >= graphYellow.getRangeTop())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), graphYellow.getRangeBottom(), int(value_float));
    Unicode::snprintf(textArea_GraphUpperRangeBuffer,6,"%d",int(value_float));
    textArea_GraphUpperRange.invalidate();
  }
  /*Check if value is smaller than graph lower range*/
  else if(int(value_float) <= graphYellow.getRangeBottom())
  {
    graphYellow.setRange(graphYellow.getRangeLeft(), graphYellow.getRangeRight(), int(value_float), graphYellow.getRangeTop());
    Unicode::snprintf(textArea_GraphLowerRangeBuffer,6,"%d",int(value_float));
    textArea_GraphLowerRange.invalidate();
  }
  
  DebugPrint("drawing on graph\n");
  
  graphYellow.addValue(tickCounter, int(value_float));
  graphRed.addValue(tickCounter + 120, int(value_float));
  graphBlue.addValue(tickCounter + 240, int(value_float));
  
  tickCounter++;
  
  if (tickCounter == 1440)
  {
    tickCounter = 0;
    
    /*Reset graph and its range*/
    graphYellow.clear();
    graphYellow.invalidate();
    graphYellow.setRange(0, 1440, -1000, 1000);
    
    graphRed.clear();
    graphRed.invalidate();
    graphRed.setRange(0, 1440, -1000, 1000);
    
    graphBlue.clear();
    graphBlue.invalidate();
    graphBlue.setRange(0, 1440, -1000, 1000);
    
    Unicode::snprintf(textArea_GraphUpperRangeBuffer,6,"%d",graphYellow.getRangeTop());
    textArea_GraphUpperRange.invalidate();
    
    Unicode::snprintf(textArea_GraphLowerRangeBuffer,6,"%d",graphYellow.getRangeBottom());
    textArea_GraphLowerRange.invalidate();
  }
#endif
}

void Screen_Module1_GraphView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}