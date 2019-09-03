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

void Screen_Module2_GraphPresenter::notifyNewUART_RX_Parsed_Frame_Graph(UARTFrameStruct_t & s_UARTFrame)
{
  view.addNewValueToGraphFromUART(s_UARTFrame);
}

void Screen_Module2_GraphPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}
