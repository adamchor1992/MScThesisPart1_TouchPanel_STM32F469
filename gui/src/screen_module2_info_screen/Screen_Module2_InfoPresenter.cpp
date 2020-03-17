#include <gui/screen_module2_info_screen/Screen_Module2_InfoView.hpp>
#include <gui/screen_module2_info_screen/Screen_Module2_InfoPresenter.hpp>

Screen_Module2_InfoPresenter::Screen_Module2_InfoPresenter(Screen_Module2_InfoView& v)
    : view(v)
{
}

void Screen_Module2_InfoPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}