#include <gui/screen_module3_info_screen/Screen_Module3_InfoView.hpp>
#include <gui/screen_module3_info_screen/Screen_Module3_InfoPresenter.hpp>

Screen_Module3_InfoPresenter::Screen_Module3_InfoPresenter(Screen_Module3_InfoView& v)
    : view(v)
{
}

void Screen_Module3_InfoPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}