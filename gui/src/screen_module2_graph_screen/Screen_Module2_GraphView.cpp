#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module2_graph_screen/Screen_Module2_GraphView.hpp>
#include <string>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>

void DebugPrint(const char* ch);
#endif

Screen_Module2_GraphView::Screen_Module2_GraphView()
{

}

void Screen_Module2_GraphView::setupScreen()
{
  tickCounter = 0;
  
  background.setXY(0, -100);
  background.setBitmap(Bitmap(BITMAP_BACKGROUND_ID));
  add(background);
  
  // Place the graph on the screen
  graph.setXY(0, 0);
  
  // Set the outer dimensions and color of the graph
  //graph.setup(440, 200, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC));
  graph.setup(800, 375, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), -1000, 1000);
  
  // Set the range for the x and y axis of the graph. That is
  // the max and min x/y value that can be displayed inside the
  // dimension of the graph.
  graph.setRange(0, 360, -1000, 1000);
  
  // Set the line width in pixels
  graph.setLineWidth(2);
  
  add(graph);
  
  Screen_Module2_GraphViewBase::setupScreen();
}

void Screen_Module2_GraphView::tearDownScreen()
{
    Screen_Module2_GraphViewBase::tearDownScreen();
}

class Utils
{
public:
  static int randomNumberBetween(int lowest, int highest)
  {
#ifdef SIMULATOR
    return lowest + (highest - lowest) * rand() / RAND_MAX;
#else
    uint32_t random = (touchgfx::HAL::getInstance()->getCPUCycles() * HAL::getInstance()->getCPUCycles());
    return lowest + (random % (highest - lowest));
#endif
  } 
};

void Screen_Module2_GraphView::handleTickEvent()
{

}

void Screen_Module2_GraphView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
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
  
  value = int(std::stof((char*)(s_UARTFrame.payload)));
  
  BSP_LED_Toggle(LED3);

  if(isNegative)
  {
    /*Make value_int negative*/
    value = value * (-1); 
  }
  
  //char str8[5];   
  
  //snprintf(str8, sizeof(uint8_t), "%f", value);   // convert uint8_t to string 
  
  //DebugPrint("\nRamka graphu ma wartosc: \n");
  //DebugPrint(str8);
  
  graph.addValue(tickCounter, value);
  
  tickCounter++;
  
  if (tickCounter == 360)
  {
    // Reset the graph and start over
    //graph.setRange(0, 1000, 0, 1000);
    //graph.setLineWidth(2);
    graph.clear();
    graph.invalidate();
    
    tickCounter = 0;
  }
#endif
}

void Screen_Module2_GraphView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}