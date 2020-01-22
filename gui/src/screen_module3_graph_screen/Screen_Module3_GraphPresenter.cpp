#include <gui/screen_module3_graph_screen/Screen_Module3_GraphView.hpp>
#include <gui/screen_module3_graph_screen/Screen_Module3_GraphPresenter.hpp>

Screen_Module3_GraphPresenter::Screen_Module3_GraphPresenter(Screen_Module3_GraphView& v)
    : view(v)
{
}

void Screen_Module3_GraphPresenter::notifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.addNewValueToGraphFromUart(uartPacket);
}

void Screen_Module3_GraphPresenter::notifyNewGraphRange(UartPacket& uartPacket)
{
  view.setNewGraphRange(uartPacket);
}

void Screen_Module3_GraphPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}