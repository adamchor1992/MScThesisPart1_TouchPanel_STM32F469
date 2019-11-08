#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module2_graph_screen/Screen_Module2_GraphView.hpp>
#include <string>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>
#endif

Screen_Module2_GraphView::Screen_Module2_GraphView()
{
  
}

void Screen_Module2_GraphView::setupScreen()
{ 
  Screen_Module2_GraphViewBase::setupScreen();
}

void Screen_Module2_GraphView::tearDownScreen()
{
  Screen_Module2_GraphViewBase::tearDownScreen();
}

/*Random signal generation*/
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

void Screen_Module2_GraphView::addNewValueToGraphFromUART(UartPacket & uartPacket)
{
  
}

void Screen_Module2_GraphView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}