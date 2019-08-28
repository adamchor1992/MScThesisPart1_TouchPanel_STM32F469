#include <gui/screen_uart_screen/Screen_UARTView.hpp>
#include <gui/screen_uart_screen/Screen_UARTPresenter.hpp>

Screen_UARTPresenter::Screen_UARTPresenter(Screen_UARTView& v)
    : view(v)
{
}

void Screen_UARTPresenter::activate()
{

}

void Screen_UARTPresenter::deactivate()
{

}

void Screen_UARTPresenter::notifyNewUART_RXValue(uint8_t *newValue)
{
	view.updateUART_RX(newValue);
}

void Screen_UARTPresenter::notifyNewUART_TXValue(uint8_t *newValue)
{
	view.updateUART_TX(newValue);
}

void Screen_UARTPresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}
