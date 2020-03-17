#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphPresenter.hpp>

Screen_Module1_GraphPresenter::Screen_Module1_GraphPresenter(Screen_Module1_GraphView& v)
    : view(v)
{
}

void Screen_Module1_GraphPresenter::NotifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.AddNewValueToGraphFromUart(uartPacket);
}

void Screen_Module1_GraphPresenter::NotifyNewGraphRange(UartPacket& uartPacket)
{
  view.SetNewGraphRange(uartPacket);
}

void Screen_Module1_GraphPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}