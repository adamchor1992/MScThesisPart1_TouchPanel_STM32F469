#include <gui/screen_module1_data_screen/Screen_Module1_DataView.hpp>
#include <gui/screen_module1_data_screen/Screen_Module1_DataPresenter.hpp>

Screen_Module1_DataPresenter::Screen_Module1_DataPresenter(Screen_Module1_DataView& v)
    : view(v)
{
}

void Screen_Module1_DataPresenter::NotifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.UpdateGuiPacketData(uartPacket);
}

void Screen_Module1_DataPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}