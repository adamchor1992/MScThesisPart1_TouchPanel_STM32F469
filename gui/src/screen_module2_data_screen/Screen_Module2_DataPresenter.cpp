#include <gui/screen_module2_data_screen/Screen_Module2_DataView.hpp>
#include <gui/screen_module2_data_screen/Screen_Module2_DataPresenter.hpp>

Screen_Module2_DataPresenter::Screen_Module2_DataPresenter(Screen_Module2_DataView& v)
    : view(v)
{
}

void Screen_Module2_DataPresenter::NotifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.UpdateGuiPacketData(uartPacket);
}

void Screen_Module2_DataPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}