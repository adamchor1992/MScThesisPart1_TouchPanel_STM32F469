#pragma once

#include <gui_generated/screen_module3_settings_screen/Screen_Module3_SettingsViewBase.hpp>
#include <gui/screen_module3_settings_screen/Screen_Module3_SettingsPresenter.hpp>

class Screen_Module3_SettingsView : public Screen_Module3_SettingsViewBase
{
public:
	Screen_Module3_SettingsView();
	virtual ~Screen_Module3_SettingsView() override {}
	virtual void setupScreen() override;
	virtual void tearDownScreen() override;

	virtual void SetNewValue() override;
	virtual void EnableParameterButtonPushed() override;
	virtual void DisableParameterButtonPushed() override;

	void UpdateCpuUsage(uint8_t value);

	void GetScrollWheelsPositions(int positions[]);
	void TranslateScrollWheelPositionsToAsciiValues(const int positions[], char values[]);

	virtual void scrollWheel_Digit1UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit2UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit3UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit4UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit5UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit6UpdateItem(DigitTemplate& item, int16_t itemIndex) override;	
	virtual void scrollWheel_Digit7UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit8UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit9UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
	virtual void scrollWheel_Digit10UpdateItem(DigitTemplate& item, int16_t itemIndex) override;	
};