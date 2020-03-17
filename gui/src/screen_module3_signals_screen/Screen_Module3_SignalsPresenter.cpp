#include <gui/screen_module3_signals_screen/Screen_Module3_SignalsView.hpp>
#include <gui/screen_module3_signals_screen/Screen_Module3_SignalsPresenter.hpp>

Screen_Module3_SignalsPresenter::Screen_Module3_SignalsPresenter(Screen_Module3_SignalsView& v)
: view(v)
{
}

void Screen_Module3_SignalsPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}