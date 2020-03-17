#include <gui/screen_module3_settings_screen/Screen_Module3_SettingsView.hpp>
#include <gui/screen_module3_settings_screen/Screen_Module3_SettingsPresenter.hpp>

Screen_Module3_SettingsPresenter::Screen_Module3_SettingsPresenter(Screen_Module3_SettingsView& v)
	: view(v)
{
}

void Screen_Module3_SettingsPresenter::NotifyNewValueToSet(UartPacket& uartPacket)
{
	model->SetNewValueToSet(uartPacket);
}

void Screen_Module3_SettingsPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
	view.UpdateCpuUsage(value);
}