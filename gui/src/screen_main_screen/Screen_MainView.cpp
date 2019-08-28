#include <gui/screen_main_screen/Screen_MainView.hpp>

Screen_MainView::Screen_MainView()
{
  /*Dim and deactivate Module buttons*/
  buttonWithLabel_Module1.setAlpha(100);
  //buttonWithLabel_Module1.setTouchable(false);
  buttonWithLabel_Module2.setAlpha(100);
  //buttonWithLabel_Module2.setTouchable(false);
  buttonWithLabel_Module3.setAlpha(100);
  //buttonWithLabel_Module3.setTouchable(false);
}

void Screen_MainView::setupScreen()
{
  Screen_MainViewBase::setupScreen();
}

void Screen_MainView::tearDownScreen()
{
  Screen_MainViewBase::tearDownScreen();
}

void Screen_MainView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}