#ifndef SCREEN_MODULE3_VIEW_HPP
#define SCREEN_MODULE3_VIEW_HPP

#include <gui_generated/screen_module3_screen/Screen_Module3ViewBase.hpp>
#include <gui/screen_module3_screen/Screen_Module3Presenter.hpp>

class Screen_Module3View : public Screen_Module3ViewBase
{
public:
  Screen_Module3View();
  virtual ~Screen_Module3View() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  void updateGUIFrameData(UARTFrameStruct_t s_UARTFrame);
  
  void updateCpuUsage(uint8_t value);
protected:
};

#endif // SCREEN_MODULE3_VIEW_HPP
