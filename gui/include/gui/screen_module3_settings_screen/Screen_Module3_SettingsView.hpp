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
        virtual void RadioButtonParameter1Selected() override;
        virtual void RadioButtonParameter2Selected() override;
        virtual void RadioButtonParameter3Selected() override;
        virtual void RadioButtonParameter4Selected() override;
        virtual void RadioButtonParameter5Selected() override;
        virtual void RadioButtonParameter6Selected() override;
        virtual void RadioButtonParameter7Selected() override;
        virtual void RadioButtonParameter8Selected() override;
        virtual void RadioButtonParameter9Selected() override;
        virtual void RadioButtonParameter10Selected() override;

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
        
private:
  void SetScrollWheelValues(int parameterIndex);
  void TranslateAsciiValuesToScrollWheelPositionsToAsciiValues(const uint8_t values[], int positions[]);
  void SetValueSign(const uint8_t value[]);
  
  uint8_t m_SettableParameterValues[SETTABLE_PARAMETER_VALUE_COUNT][PAYLOAD_SIZE] = { 0 };
};