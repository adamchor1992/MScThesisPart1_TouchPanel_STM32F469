#ifndef SCREEN_MODULE1_SETTINGS_VIEW_HPP
#define SCREEN_MODULE1_SETTINGS_VIEW_HPP

#include <gui_generated/screen_module1_settings_screen/Screen_Module1_SettingsViewBase.hpp>
#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsPresenter.hpp>

class Screen_Module1_SettingsView : public Screen_Module1_SettingsViewBase
{
public:
  Screen_Module1_SettingsView();
  virtual ~Screen_Module1_SettingsView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  virtual void updateValueToSet(int value);
  virtual void setNewValue();
  virtual void enableParameterButtonPushed();
  virtual void disableParameterButtonPushed();
  virtual void scrollWheel_ExponentsUpdateItem(ExponentContainer& item, int16_t itemIndex);
  void updateCpuUsage(uint8_t value);
};

#endif // SCREEN_MODULE1_SETTINGS_VIEW_HPP
