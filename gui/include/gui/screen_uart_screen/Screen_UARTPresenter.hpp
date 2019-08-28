#ifndef SCREEN_UART_PRESENTER_HPP
#define SCREEN_UART_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_UARTView;

class Screen_UARTPresenter : public Presenter, public ModelListener
{
public:
  Screen_UARTPresenter(Screen_UARTView& v);
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
  
  virtual void notifyNewUART_RXValue(uint8_t *newValue); 
  virtual void notifyNewUART_TXValue(uint8_t *newValue); 
  
  virtual ~Screen_UARTPresenter() {};
  
private:
  Screen_UARTPresenter();
  
  Screen_UARTView& view;
};


#endif // SCREEN_UART_PRESENTER_HPP
