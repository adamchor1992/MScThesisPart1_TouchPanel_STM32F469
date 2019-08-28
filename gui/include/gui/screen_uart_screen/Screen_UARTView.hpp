#ifndef SCREEN_UART_VIEW_HPP
#define SCREEN_UART_VIEW_HPP

#include <gui_generated/screen_uart_screen/Screen_UARTViewBase.hpp>
#include <gui/screen_uart_screen/Screen_UARTPresenter.hpp>

#include <stm32f4xx_hal_uart.h>

class Screen_UARTView : public Screen_UARTViewBase
{
public:
  Screen_UARTView();
  virtual ~Screen_UARTView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  void updateUART_RX(uint8_t *newValue);
  void updateUART_TX(uint8_t *newValue);
  void updateCpuUsage(uint8_t value);
protected:
  virtual void sendUARTHello();
private:
  char UART_String[10];
  UART_HandleTypeDef m_huart6;
};

#endif // SCREEN_UART_VIEW_HPP
