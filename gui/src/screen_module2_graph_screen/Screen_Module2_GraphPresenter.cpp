#include <gui/screen_module2_graph_screen/Screen_Module2_GraphView.hpp>
#include <gui/screen_module2_graph_screen/Screen_Module2_GraphPresenter.hpp>

Screen_Module2_GraphPresenter::Screen_Module2_GraphPresenter(Screen_Module2_GraphView& v)
    : view(v)
{
}

void Screen_Module2_GraphPresenter::activate()
{

}

void Screen_Module2_GraphPresenter::deactivate()
{

}

void Screen_Module2_GraphPresenter::notifyNewUartRxParsedPacket(UartPacket & uartPacket)
{
  view.addNewValueToGraphFromUART(uartPacket);
}

void Screen_Module2_GraphPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}
