#include <gui/screen_module2_settings_screen/Screen_Module2_SettingsView.hpp>
#include <gui/screen_module2_settings_screen/Screen_Module2_SettingsPresenter.hpp>

Screen_Module2_SettingsPresenter::Screen_Module2_SettingsPresenter(Screen_Module2_SettingsView& v)
	: view(v)
{
}

void Screen_Module2_SettingsPresenter::NotifyNewValueToSet(UartPacket& uartPacket)
{
	model->SetNewValueToSet(uartPacket);
}

void Screen_Module2_SettingsPresenter::NotifyNewCpuUsageValue(uint8_t value)
{
	view.UpdateCpuUsage(value);
}