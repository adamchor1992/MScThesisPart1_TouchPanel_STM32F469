#include <gui/screen_module3_graph_screen/Screen_Module3_GraphView.hpp>
#include <gui/screen_module3_graph_screen/Screen_Module3_GraphPresenter.hpp>

Screen_Module3_GraphPresenter::Screen_Module3_GraphPresenter(Screen_Module3_GraphView& v)
    : view(v)
{
}

void Screen_Module3_GraphPresenter::NotifyNewUartRxParsedPacket(UartPacket& uartPacket)
{
  view.AddNewValueToGraphFromUart(uartPacket);
}

void Screen_Module3_GraphPresenter::NotifyNewGraphRange(UartPacket& uartPacket)
{
  view.SetNewGraphRange(uartPacket);
}

void Screen_Module3_GraphPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
  view.UpdateCpuUsage(value);
}