#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsView.hpp>
#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsPresenter.hpp>

Screen_Module1_SettingsPresenter::Screen_Module1_SettingsPresenter(Screen_Module1_SettingsView& v)
	: view(v)
{
}

void Screen_Module1_SettingsPresenter::notifyNewValueToSet(UartPacket & uartPacket)
{
	model->setNewValueToSet(uartPacket);
}

void Screen_Module1_SettingsPresenter::notifyNewCpuUsageValue(uint8_t value)
{
	view.updateCpuUsage(value);
}