#include <gui/screen_module2_signals_screen/Screen_Module2_SignalsView.hpp>
#include <gui/screen_module2_signals_screen/Screen_Module2_SignalsPresenter.hpp>

Screen_Module2_SignalsPresenter::Screen_Module2_SignalsPresenter(Screen_Module2_SignalsView& v)
: view(v)
{
}

void Screen_Module2_SignalsPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}