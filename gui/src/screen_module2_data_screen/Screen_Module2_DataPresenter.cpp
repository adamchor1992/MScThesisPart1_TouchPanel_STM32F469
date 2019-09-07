#include <gui/screen_module2_data_screen/Screen_Module2_DataView.hpp>
#include <gui/screen_module2_data_screen/Screen_Module2_DataPresenter.hpp>

Screen_Module2_DataPresenter::Screen_Module2_DataPresenter(Screen_Module2_DataView& v)
    : view(v)
{
}

void Screen_Module2_DataPresenter::activate()
{

}

void Screen_Module2_DataPresenter::deactivate()
{

}

void Screen_Module2_DataPresenter::notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame)
{
  view.updateGUIFrameData(s_UARTFrame);
}