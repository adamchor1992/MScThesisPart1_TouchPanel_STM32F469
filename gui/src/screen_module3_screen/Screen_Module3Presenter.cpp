#include <gui/screen_module3_screen/Screen_Module3View.hpp>
#include <gui/screen_module3_screen/Screen_Module3Presenter.hpp>

Screen_Module3Presenter::Screen_Module3Presenter(Screen_Module3View& v)
: view(v)
{
}

void Screen_Module3Presenter::activate()
{
  
}

void Screen_Module3Presenter::deactivate()
{
  
}

void Screen_Module3Presenter::notifyNewUART_RXParsedFrame(UARTFrameStruct_t s_UARTFrame)
{
  view.updateGUIFrameData(s_UARTFrame);
}

void Screen_Module3Presenter::notifyNewValueToSet(UARTFrameStruct_t s_UARTFrame)
{
  model->setNewValueToSet(s_UARTFrame);
}

void Screen_Module3Presenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}
