#ifndef SCREEN_MODULE2_SETTINGS_VIEW_HPP
#define SCREEN_MODULE2_SETTINGS_VIEW_HPP

#include <gui_generated/screen_module2_settings_screen/Screen_Module2_SettingsViewBase.hpp>
#include <gui/screen_module2_settings_screen/Screen_Module2_SettingsPresenter.hpp>

class Screen_Module2_SettingsView : public Screen_Module2_SettingsViewBase
{
public:
    Screen_Module2_SettingsView();
    virtual ~Screen_Module2_SettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_MODULE2_SETTINGS_VIEW_HPP
