#include <gui/screen_module1_info_screen/Screen_Module1_InfoView.hpp>
#include <gui/screen_module1_info_screen/Screen_Module1_InfoPresenter.hpp>

Screen_Module1_InfoPresenter::Screen_Module1_InfoPresenter(Screen_Module1_InfoView& v)
    : view(v)
{
}

void Screen_Module1_InfoPresenter::activate()
{

}

void Screen_Module1_InfoPresenter::deactivate()
{

}

void Screen_Module1_InfoPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}