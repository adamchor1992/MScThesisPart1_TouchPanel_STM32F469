#include <gui/screen_module3_data_screen/Screen_Module3_DataView.hpp>
#include <gui/screen_module3_data_screen/Screen_Module3_DataPresenter.hpp>

Screen_Module3_DataPresenter::Screen_Module3_DataPresenter(Screen_Module3_DataView& v)
    : view(v)
{
}

void Screen_Module3_DataPresenter::activate()
{

}

void Screen_Module3_DataPresenter::deactivate()
{

}

void Screen_Module3_DataPresenter::notifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.updateGuiPacketData(uartPacket);
}

void Screen_Module3_DataPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}