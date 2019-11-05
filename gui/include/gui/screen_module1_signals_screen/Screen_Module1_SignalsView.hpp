#ifndef SCREEN_MODULE1_SIGNALS_VIEW_HPP
#define SCREEN_MODULE1_SIGNALS_VIEW_HPP

#include <gui_generated/screen_module1_signals_screen/Screen_Module1_SignalsViewBase.hpp>
#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsPresenter.hpp>

class Screen_Module1_SignalsView : public Screen_Module1_SignalsViewBase
{
public:
  Screen_Module1_SignalsView();
  virtual ~Screen_Module1_SignalsView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();

  virtual void setRanges();

  void initializeScrollWheels();

  void setMinScrollWheelValues(int bottom);
  void setMaxScrollWheelValues(int top);

  void getScrollWheelMinValues(int values[]);

  void getScrollWheelMaxValues(int values[]);

  void translateScrollWheelValues(int values[]);

  int processScrollWheelValues(const int values[]);
  
  virtual void setParameter1GraphVisible();
  virtual void setParameter2GraphVisible();
  virtual void setParameter3GraphVisible();
  virtual void setParameter4GraphVisible();
  
  virtual void updateTimeRange(int value);
  virtual void updateY_AxisMin(int value);
  virtual void updateY_AxisMax(int value);
  
  virtual void pressedAutoRangeToggleButton();
  
  void updateCpuUsage(uint8_t value);

  virtual void scrollWheel_MinDigit1UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit2UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit3UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit4UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit5UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit6UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit7UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit8UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit9UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MinDigit10UpdateItem(DigitTemplate& item, int16_t itemIndex);

  virtual void scrollWheel_MaxDigit1UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit2UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit3UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit4UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit5UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit6UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit7UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit8UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit9UpdateItem(DigitTemplate& item, int16_t itemIndex);
  virtual void scrollWheel_MaxDigit10UpdateItem(DigitTemplate& item, int16_t itemIndex);
};

#endif // SCREEN_MODULE1_SIGNALS_VIEW_HPP
