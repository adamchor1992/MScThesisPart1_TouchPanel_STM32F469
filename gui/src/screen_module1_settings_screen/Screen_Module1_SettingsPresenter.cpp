#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsView.hpp>
#include <gui/screen_module1_settings_screen/Screen_Module1_SettingsPresenter.hpp>

Screen_Module1_SettingsPresenter::Screen_Module1_SettingsPresenter(Screen_Module1_SettingsView& v)
	: view(v)
{
}

void Screen_Module1_SettingsPresenter::NotifyNewValueToSet(UartPacket& uartPacket)
{
	model->SetNewValueToSet(uartPacket);
}

void Screen_Module1_SettingsPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
	view.UpdateCpuUsage(value);
}