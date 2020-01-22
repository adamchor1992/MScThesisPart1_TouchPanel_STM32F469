#ifndef SCREEN_MODULE2_SETTINGS_VIEW_HPP
#define SCREEN_MODULE2_SETTINGS_VIEW_HPP

#include <gui_generated/screen_module2_settings_screen/Screen_Module2_SettingsViewBase.hpp>
#include <gui/screen_module2_settings_screen/Screen_Module2_SettingsPresenter.hpp>

class Screen_Module2_SettingsView : public Screen_Module2_SettingsViewBase
{
public:
	Screen_Module2_SettingsView();
	virtual ~Screen_Module2_SettingsView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();

	virtual void setNewValue();
	virtual void enableParameterButtonPushed();
	virtual void disableParameterButtonPushed();

	void updateCpuUsage(uint8_t value);

	void getScrollWheelsPositions(int positions[]);
	void translateScrollWheelPositionsToAsciiValues(const int positions[], char values[]);

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

#endif // SCREEN_MODULE2_SETTINGS_VIEW_HPP
