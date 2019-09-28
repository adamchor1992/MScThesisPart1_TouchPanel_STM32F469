#ifndef SCREEN_MODULE1_SIGNALS_VIEW_HPP
#define SCREEN_MODULE1_SIGNALS_VIEW_HPP

#include <gui_generated/screen_module1_signals_screen/Screen_Module1_SignalsViewBase.hpp>
#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsPresenter.hpp>

class Screen_Module1_SignalsView : public Screen_Module1_SignalsViewBase
{
public:
  Screen_Module1_SignalsView();
  virtual ~Screen_Module1_SignalsView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  virtual void setParameter1GraphVisible();
  virtual void setParameter2GraphVisible();
  virtual void setParameter3GraphVisible();
  virtual void setParameter4GraphVisible();
  
  virtual void updateTimeRange(int value);
  virtual void updateY_AxisMin(int value);
  virtual void updateY_AxisMax(int value);
  
  virtual void pressedAutoRangeToggleButton();
};

#endif // SCREEN_MODULE1_SIGNALS_VIEW_HPP
