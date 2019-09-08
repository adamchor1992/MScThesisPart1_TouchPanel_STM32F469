#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugView.hpp>
#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugPresenter.hpp>

Screen_UART_RX_DebugPresenter::Screen_UART_RX_DebugPresenter(Screen_UART_RX_DebugView& v)
    : view(v)
{
}

void Screen_UART_RX_DebugPresenter::activate()
{

}

void Screen_UART_RX_DebugPresenter::deactivate()
{

}

void Screen_UART_RX_DebugPresenter::notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame)
{
  view.updateGUIFrameData(s_UARTFrame);
}

void Screen_UART_RX_DebugPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}