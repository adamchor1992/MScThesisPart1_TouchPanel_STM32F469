#ifndef SCREEN_MODULE3_SETTINGS_VIEW_HPP
#define SCREEN_MODULE3_SETTINGS_VIEW_HPP

#include <gui_generated/screen_module3_settings_screen/Screen_Module3_SettingsViewBase.hpp>
#include <gui/screen_module3_settings_screen/Screen_Module3_SettingsPresenter.hpp>

class Screen_Module3_SettingsView : public Screen_Module3_SettingsViewBase
{
public:
	Screen_Module3_SettingsView();
	virtual ~Screen_Module3_SettingsView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	virtual void setNewValue();
	virtual void enableParameterButtonPushed();
	virtual void disableParameterButtonPushed();

	void updateCpuUsage(uint8_t value);

	void getScrollWheelValues(int values[]);
	void translateScrollWheelValues(int values[]);
	double processScrollWheelValues(const int values[]);

	virtual void scrollWheel_Digit1UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit2UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit3UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit4UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit5UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit6UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit7UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit8UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit9UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit10UpdateItem(DigitTemplate& item, int16_t itemIndex);
};

#endif