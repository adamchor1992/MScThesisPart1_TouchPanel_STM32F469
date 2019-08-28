#ifndef SCREEN_MODULE1_PRESENTER_HPP
#define SCREEN_MODULE1_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1View;

class Screen_Module1Presenter : public Presenter, public ModelListener
{
public:
  Screen_Module1Presenter(Screen_Module1View& v);
  virtual void notifyNewUART_RXParsedFrame(UARTFrameStruct_t s_UARTFrame); 
  virtual void notifyNewValueToSet(UARTFrameStruct_t s_UARTFrame);
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
  
  virtual ~Screen_Module1Presenter() {};
  
private:
  Screen_Module1Presenter();
  
  Screen_Module1View& view;
};


#endif // SCREEN_MODULE1_PRESENTER_HPP
