#include <gui/screen_main_screen/Screen_MainView.hpp>
#include <gui/screen_main_screen/Screen_MainPresenter.hpp>

Screen_MainPresenter::Screen_MainPresenter(Screen_MainView& v)
: view(v)
{
}

void Screen_MainPresenter::NotifyAllInitPacketsReceived(UartPacket& uartPacket)
{
  view.ProcessInitPacket(uartPacket);
}

void Screen_MainPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}