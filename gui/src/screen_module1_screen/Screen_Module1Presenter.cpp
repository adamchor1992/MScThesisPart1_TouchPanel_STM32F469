#include <gui/screen_module1_screen/Screen_Module1View.hpp>
#include <gui/screen_module1_screen/Screen_Module1Presenter.hpp>

Screen_Module1Presenter::Screen_Module1Presenter(Screen_Module1View& v)
: view(v)
{
}

void Screen_Module1Presenter::activate()
{
  
}

void Screen_Module1Presenter::deactivate()
{
  
}

void Screen_Module1Presenter::notifyNewUART_RXParsedFrame(UARTFrameStruct_t s_UARTFrame)
{
  view.updateGUIFrameData(s_UARTFrame);
}

void Screen_Module1Presenter::notifyNewValueToSet(UARTFrameStruct_t s_UARTFrame)
{
  model->setNewValueToSet(s_UARTFrame);
}

void Screen_Module1Presenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}
