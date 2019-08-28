#ifndef SCREEN_MODULE1_VIEW_HPP
#define SCREEN_MODULE1_VIEW_HPP

#include <gui_generated/screen_module1_screen/Screen_Module1ViewBase.hpp>
#include <gui/screen_module1_screen/Screen_Module1Presenter.hpp>
#include "stdio.h"

class Screen_Module1View : public Screen_Module1ViewBase
{
public:
  Screen_Module1View();
  virtual ~Screen_Module1View() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  void updateGUIFrameData(UARTFrameStruct_t s_UARTFrame);
  virtual void updateValueToSet(int value);
  virtual void setNewValue();
  
  void updateCpuUsage(uint8_t value);
protected:
};

#endif // SCREEN_MODULE1_VIEW_HPP
