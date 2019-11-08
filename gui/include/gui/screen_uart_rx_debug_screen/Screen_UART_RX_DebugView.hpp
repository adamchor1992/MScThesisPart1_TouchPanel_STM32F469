#ifndef SCREEN_UART_RX_DEBUG_VIEW_HPP
#define SCREEN_UART_RX_DEBUG_VIEW_HPP

#include <gui_generated/screen_uart_rx_debug_screen/Screen_UART_RX_DebugViewBase.hpp>
#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugPresenter.hpp>

class Screen_UART_RX_DebugView : public Screen_UART_RX_DebugViewBase
{
public:
    Screen_UART_RX_DebugView();
    virtual ~Screen_UART_RX_DebugView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    void updateGuiPacketData(UartPacket & uartPacket);
    void updateCpuUsage(uint8_t value);
};

#endif // SCREEN_UART_RX_DEBUG_VIEW_HPP
