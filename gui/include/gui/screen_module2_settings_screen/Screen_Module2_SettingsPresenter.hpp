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

	virtual void notifyNewValueToSet(UartPacket& uartPacket);
	void notifyNewCpuUsageValue(uint8_t value);

	virtual ~Screen_Module2_SettingsPresenter() {};

private:
	Screen_Module2_SettingsPresenter();

	Screen_Module2_SettingsView& view;
};

#endif
