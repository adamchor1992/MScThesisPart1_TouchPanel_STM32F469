#include <gui/screen_main_screen/Screen_MainView.hpp>
#include <gui/screen_main_screen/Screen_MainPresenter.hpp>

Screen_MainPresenter::Screen_MainPresenter(Screen_MainView& v)
: view(v)
{
}

void Screen_MainPresenter::activate()
{
  
}

void Screen_MainPresenter::deactivate()
{
  
}

void Screen_MainPresenter::notifyAllInitFrameReceived(UARTFrameStruct_t & s_UARTFrame)
{
  view.processInitFrame(s_UARTFrame);
}

void Screen_MainPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}