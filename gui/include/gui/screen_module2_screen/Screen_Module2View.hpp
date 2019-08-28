#ifndef SCREEN_MODULE2_VIEW_HPP
#define SCREEN_MODULE2_VIEW_HPP

#include <gui_generated/screen_module2_screen/Screen_Module2ViewBase.hpp>
#include <gui/screen_module2_screen/Screen_Module2Presenter.hpp>
#include "stdio.h"

class Screen_Module2View : public Screen_Module2ViewBase
{
public:
  Screen_Module2View();
  virtual ~Screen_Module2View() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  void updateGUIFrameData(UARTFrameStruct_t s_UARTFrame);	
  virtual void updateValueToSet(int value);
  virtual void setNewValue();
  
  void updateCpuUsage(uint8_t value);
protected:
};

#endif // SCREEN_MODULE2_VIEW_HPP
