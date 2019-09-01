#ifndef SCREEN_MODULE2_SETTINGS_PRESENTER_HPP
#define SCREEN_MODULE2_SETTINGS_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_SettingsView;

class Screen_Module2_SettingsPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module2_SettingsPresenter(Screen_Module2_SettingsView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen_Module2_SettingsPresenter() {};

private:
    Screen_Module2_SettingsPresenter();

    Screen_Module2_SettingsView& view;
};


#endif // SCREEN_MODULE2_SETTINGS_PRESENTER_HPP
