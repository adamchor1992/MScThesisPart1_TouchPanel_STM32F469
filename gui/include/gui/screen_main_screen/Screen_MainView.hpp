#ifndef SCREEN_MAIN_VIEW_HPP
#define SCREEN_MAIN_VIEW_HPP

#include <gui_generated/screen_main_screen/Screen_MainViewBase.hpp>
#include <gui/screen_main_screen/Screen_MainPresenter.hpp>

class Screen_MainView : public Screen_MainViewBase
{
public:
  Screen_MainView();
  virtual ~Screen_MainView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  void processInitFrame(UARTFrameStruct_t & s_UARTFrame);
  void updateCpuUsage(uint8_t value);
};

#endif // SCREEN_MAIN_VIEW_HPP
