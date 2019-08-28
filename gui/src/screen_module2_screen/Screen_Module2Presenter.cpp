#include <gui/screen_module2_screen/Screen_Module2View.hpp>
#include <gui/screen_module2_screen/Screen_Module2Presenter.hpp>

Screen_Module2Presenter::Screen_Module2Presenter(Screen_Module2View& v)
: view(v)
{
}

void Screen_Module2Presenter::activate()
{
  
}

void Screen_Module2Presenter::deactivate()
{
  
}

void Screen_Module2Presenter::notifyNewUART_RXParsedFrame(UARTFrameStruct_t s_UARTFrame)
{
  view.updateGUIFrameData(s_UARTFrame);
}

void Screen_Module2Presenter::notifyNewValueToSet(UARTFrameStruct_t s_UARTFrame)
{
  model->setNewValueToSet(s_UARTFrame);
}

void Screen_Module2Presenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}
