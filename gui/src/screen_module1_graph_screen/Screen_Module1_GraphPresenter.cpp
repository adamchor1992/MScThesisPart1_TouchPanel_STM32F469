#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphPresenter.hpp>

Screen_Module1_GraphPresenter::Screen_Module1_GraphPresenter(Screen_Module1_GraphView& v)
    : view(v)
{
}

void Screen_Module1_GraphPresenter::activate()
{

}

void Screen_Module1_GraphPresenter::deactivate()
{

}

void Screen_Module1_GraphPresenter::notifyNewUartRxParsedPacket(UartPacket & uartPacket)
{
  view.addNewValueToGraphFromUart(uartPacket);
}

void Screen_Module1_GraphPresenter::notifyNewGraphRange(UartPacket & uartPacket)
{
  view.setNewGraphRange(uartPacket);
}

void Screen_Module1_GraphPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}