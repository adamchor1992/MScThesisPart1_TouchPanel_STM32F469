#include <gui/template_screen/TemplateView.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <string>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#endif

#ifndef SIMULATOR
void DebugPrint(const char* ch);
#endif

#ifdef SIMULATOR
#include <stdlib.h>
#endif

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

void TemplateView::setupScreen()
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
  
  TemplateViewBase::setupScreen();
}

void TemplateView::tearDownScreen()
{
  
}

void TemplateView::handleTickEvent()
{
  //  // Number of ticks between inserting a point in the graph
  //  int interval = 1;
  //  
  //  if (tickCounter % interval == 0)
  //  {
  //    // Insert a point in the graph.
  //    // The Y value is a random number in the y range of the graph.
  //    graph.addValue(tickCounter, Utils::randomNumberBetween(graph.getRangeBottom(), graph.getRangeTop()));
  //    //graph.addValue(tickCounter / interval, tickCounter / interval);
  //  }
  //  
  //  tickCounter++;
  //  
  //  if (tickCounter == 360 * interval)
  //  {
  //    // Reset the graph and start over
  //    //graph.setRange(0, 100, 0, 40);
  //    graph.setLineWidth(2);
  //    graph.clear();
  //    graph.invalidate();
  //    
  //    tickCounter = 0;
  //  }
}

void TemplateView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
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
  
#ifndef SIMULATOR
  BSP_LED_Toggle(LED3);
#endif
  
  if(isNegative)
  {
    /*Make value_int negative*/
    value_float = value_float * (-1); 
  }
  
  char str8[5];   
  
  snprintf(str8, sizeof(uint8_t), "%f", value_float);   // convert uint8_t to string 
  
  DebugPrint("\nRamka graphu ma wartosc: \n");
  DebugPrint(str8);
  
  graph.addValue(tickCounter, int(value_float));
  
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

void TemplateView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}