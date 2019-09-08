#include <gui/screen_module2_settings_screen/Screen_Module2_SettingsView.hpp>

Screen_Module2_SettingsView::Screen_Module2_SettingsView()
{

}

void Screen_Module2_SettingsView::setupScreen()
{
    Screen_Module2_SettingsViewBase::setupScreen();
}

void Screen_Module2_SettingsView::tearDownScreen()
{
    Screen_Module2_SettingsViewBase::tearDownScreen();
}

void Screen_Module2_SettingsView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}