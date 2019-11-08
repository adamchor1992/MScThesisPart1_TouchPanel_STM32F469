#include <gui/screen_module2_data_screen/Screen_Module2_DataView.hpp>
#include <gui/screen_module2_data_screen/Screen_Module2_DataPresenter.hpp>

Screen_Module2_DataPresenter::Screen_Module2_DataPresenter(Screen_Module2_DataView& v)
    : view(v)
{
}

void Screen_Module2_DataPresenter::activate()
{

}

void Screen_Module2_DataPresenter::deactivate()
{

}

void Screen_Module2_DataPresenter::notifyNewUartRxParsedPacket(UartPacket & uartPacket)
{
  view.updateGuiPacketData(uartPacket);
}

void Screen_Module2_DataPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}