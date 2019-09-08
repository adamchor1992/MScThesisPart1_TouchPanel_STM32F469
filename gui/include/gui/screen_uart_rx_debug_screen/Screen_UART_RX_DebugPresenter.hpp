#ifndef SCREEN_UART_RX_DEBUG_PRESENTER_HPP
#define SCREEN_UART_RX_DEBUG_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_UART_RX_DebugView;

class Screen_UART_RX_DebugPresenter : public Presenter, public ModelListener
{
public:
    Screen_UART_RX_DebugPresenter(Screen_UART_RX_DebugView& v);

    virtual void notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame); 
    void notifyNewCpuUsageValue(uint8_t value);
    
    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen_UART_RX_DebugPresenter() {};

private:
    Screen_UART_RX_DebugPresenter();

    Screen_UART_RX_DebugView& view;
};


#endif // SCREEN_UART_RX_DEBUG_PRESENTER_HPP
