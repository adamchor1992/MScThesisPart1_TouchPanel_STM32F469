#include <gui/screen_module1_data_screen/Screen_Module1_DataView.hpp>
#include <gui/screen_module1_data_screen/Screen_Module1_DataPresenter.hpp>

Screen_Module1_DataPresenter::Screen_Module1_DataPresenter(Screen_Module1_DataView& v)
    : view(v)
{
}

void Screen_Module1_DataPresenter::activate()
{

}

void Screen_Module1_DataPresenter::deactivate()
{

}

void Screen_Module1_DataPresenter::notifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.updateGuiPacketData(uartPacket);
}

void Screen_Module1_DataPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}