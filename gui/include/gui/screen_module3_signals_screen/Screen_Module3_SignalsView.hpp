#pragma once

#include <gui_generated/screen_module3_signals_screen/Screen_Module3_SignalsViewBase.hpp>
#include <gui/screen_module3_signals_screen/Screen_Module3_SignalsPresenter.hpp>

class Screen_Module3_SignalsView : public Screen_Module3_SignalsViewBase
{
  /*Forward declaration*/
  enum class Sign;
  
public:
  Screen_Module3_SignalsView();
  virtual ~Screen_Module3_SignalsView() override {}
  virtual void setupScreen();
  
  virtual void SetRanges() override;
  
  virtual void SetParameter1GraphVisible() override;
  virtual void SetParameter2GraphVisible() override;
  virtual void SetParameter3GraphVisible() override;
  virtual void SetParameter4GraphVisible() override;
  
  virtual void PressedAutoRangeToggleButton() override;
  virtual void UpdateTimeRange(int value) override;
  
  void InitializeScrollWheels();
  void SetMinScrollWheelValues(long long int bottom);
  void SetMaxScrollWheelValues(long long int top);
  
  void GetMinRangeScrollWheelsPositions(int positions[]);
  void GetMaxRangeScrollWheelsPositions(int positions[]);
  void TranslateScrollWheelPositionsToAsciiValues(int const positions[], char values[]);
  
  void HideManualRangeSettings();
  void ShowManualRangeSettings();       
  
  void SetSignMin(Sign sign);
  void SetSignMax(Sign sign);
  
  Sign GetSignMin();
  Sign GetSignMax();
  
  virtual void scrollWheel_MinDigit1UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit2UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit3UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit4UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit5UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit6UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit7UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit8UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit9UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MinDigit10UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  
  virtual void scrollWheel_MaxDigit1UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit2UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit3UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit4UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit5UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit6UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit7UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit8UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  virtual void scrollWheel_MaxDigit9UpdateItem(DigitTemplate& item, int16_t itemIndex) override ;
  virtual void scrollWheel_MaxDigit10UpdateItem(DigitTemplate& item, int16_t itemIndex) override;
  
  void UpdateCpuUsage(uint8_t value);
  
private:
  enum class Sign { NEGATIVE = 0, POSITIVE = 1};
};