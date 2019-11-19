#include <gui/screen_module3_settings_screen/Screen_Module3_SettingsView.hpp>
#include <gui/screen_module3_settings_screen/Screen_Module3_SettingsPresenter.hpp>

Screen_Module3_SettingsPresenter::Screen_Module3_SettingsPresenter(Screen_Module3_SettingsView& v)
	: view(v)
{
}

void Screen_Module3_SettingsPresenter::notifyNewValueToSet(UartPacket & uartPacket)
{
	model->setNewValueToSet(uartPacket);
}

void Screen_Module3_SettingsPresenter::notifyNewCpuUsageValue(uint8_t value)
{
	view.updateCpuUsage(value);
}