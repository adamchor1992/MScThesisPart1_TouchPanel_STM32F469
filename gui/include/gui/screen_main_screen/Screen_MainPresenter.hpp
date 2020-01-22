#ifndef SCREEN_MAIN_PRESENTER_HPP
#define SCREEN_MAIN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_MainView;

class Screen_MainPresenter : public Presenter, public ModelListener
{
public:
  Screen_MainPresenter(Screen_MainView& v);
  
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
  
  virtual ~Screen_MainPresenter() {};
  
  void notifyAllInitPacketsReceived(UartPacket& uartPacket);

private:
  Screen_MainPresenter();
  
  Screen_MainView& view;
};


#endif // SCREEN_MAIN_PRESENTER_HPP
