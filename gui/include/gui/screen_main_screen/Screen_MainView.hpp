#pragma once

#include <gui_generated/screen_main_screen/Screen_MainViewBase.hpp>
#include <gui/screen_main_screen/Screen_MainPresenter.hpp>

class Screen_MainView : public Screen_MainViewBase
{
public:
  virtual ~Screen_MainView() {}
  virtual void setupScreen() override;
  virtual void tearDownScreen() override;
  
  virtual void ClearLeds() override;

  void ProcessInitPacket(UartPacket& uartPacket);
  void UpdateCpuUsage(uint8_t value);
};