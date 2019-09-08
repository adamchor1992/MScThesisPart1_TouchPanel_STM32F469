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

void Screen_Module1_DataPresenter::notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame)
{
  view.updateGUIFrameData(s_UARTFrame);
}

void Screen_Module1_DataPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}