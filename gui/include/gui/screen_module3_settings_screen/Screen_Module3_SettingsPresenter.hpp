#ifndef SCREEN_MODULE3_SETTINGS_PRESENTER_HPP
#define SCREEN_MODULE3_SETTINGS_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_SettingsView;

class Screen_Module3_SettingsPresenter : public Presenter, public ModelListener
{
public:
	Screen_Module3_SettingsPresenter(Screen_Module3_SettingsView& v);

	virtual void notifyNewValueToSet(UartPacket& uartPacket);
	void notifyNewCpuUsageValue(uint8_t value);

	virtual ~Screen_Module3_SettingsPresenter() {};

private:
	Screen_Module3_SettingsPresenter();

	Screen_Module3_SettingsView& view;
};

#endif
