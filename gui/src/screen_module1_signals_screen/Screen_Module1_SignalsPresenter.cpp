#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsView.hpp>
#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsPresenter.hpp>

Screen_Module1_SignalsPresenter::Screen_Module1_SignalsPresenter(Screen_Module1_SignalsView& v)
    : view(v)
{
}

void Screen_Module1_SignalsPresenter::activate()
{

}

void Screen_Module1_SignalsPresenter::deactivate()
{

}

void Screen_Module1_SignalsPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}