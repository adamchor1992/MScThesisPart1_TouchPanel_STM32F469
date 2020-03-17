#include <gui/screen_module3_data_screen/Screen_Module3_DataView.hpp>
#include <gui/screen_module3_data_screen/Screen_Module3_DataPresenter.hpp>

Screen_Module3_DataPresenter::Screen_Module3_DataPresenter(Screen_Module3_DataView& v)
    : view(v)
{
}

void Screen_Module3_DataPresenter::NotifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.UpdateGuiPacketData(uartPacket);
}

void Screen_Module3_DataPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}