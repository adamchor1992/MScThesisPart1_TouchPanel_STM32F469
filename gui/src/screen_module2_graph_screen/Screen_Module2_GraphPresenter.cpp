#include <gui/screen_module2_graph_screen/Screen_Module2_GraphView.hpp>
#include <gui/screen_module2_graph_screen/Screen_Module2_GraphPresenter.hpp>

Screen_Module2_GraphPresenter::Screen_Module2_GraphPresenter(Screen_Module2_GraphView& v)
    : view(v)
{
}

void Screen_Module2_GraphPresenter::NotifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.AddNewValueToGraphFromUart(uartPacket);
}

void Screen_Module2_GraphPresenter::NotifyNewGraphRange(UartPacket& uartPacket)
{
  view.SetNewGraphRange(uartPacket);
}

void Screen_Module2_GraphPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}