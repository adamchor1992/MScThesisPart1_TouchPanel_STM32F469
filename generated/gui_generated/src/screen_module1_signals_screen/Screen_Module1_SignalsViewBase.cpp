/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_module1_signals_screen/Screen_Module1_SignalsViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

Screen_Module1_SignalsViewBase::Screen_Module1_SignalsViewBase() :
    buttonCallback(this, &Screen_Module1_SignalsViewBase::buttonCallbackHandler),
    sliderValueChangedCallback(this, &Screen_Module1_SignalsViewBase::sliderValueChangedCallbackHandler)
{
    backgroundBox_Black.setPosition(0, 1, 800, 480);
    backgroundBox_Black.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    toggleButton_Voltage.setXY(235, 122);
    toggleButton_Voltage.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
    toggleButton_Voltage.setAction(buttonCallback);

    toggleButton_Current.setXY(235, 172);
    toggleButton_Current.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
    toggleButton_Current.setAction(buttonCallback);

    toggleButton_Frequency.setXY(235, 222);
    toggleButton_Frequency.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
    toggleButton_Frequency.setAction(buttonCallback);

    toggleButton_Power.setXY(235, 272);
    toggleButton_Power.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID));
    toggleButton_Power.setAction(buttonCallback);

    textArea_Power.setPosition(0, 261, 250, 49);
    textArea_Power.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Power.setLinespacing(0);
    textArea_Power.setTypedText(TypedText(T_SINGLEUSEID277));

    textArea_Frequency.setPosition(0, 211, 250, 49);
    textArea_Frequency.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Frequency.setLinespacing(0);
    textArea_Frequency.setTypedText(TypedText(T_SINGLEUSEID279));

    textArea_Current.setPosition(0, 161, 250, 49);
    textArea_Current.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Current.setLinespacing(0);
    textArea_Current.setTypedText(TypedText(T_SINGLEUSEID281));

    textArea_Voltage.setPosition(0, 111, 250, 49);
    textArea_Voltage.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Voltage.setLinespacing(0);
    textArea_Voltage.setTypedText(TypedText(T_SINGLEUSEID283));

    textArea_Title.setXY(328, 0);
    textArea_Title.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Title.setLinespacing(0);
    textArea_Title.setTypedText(TypedText(T_SINGLEUSEID285));

    textArea_CPU_Usage.setPosition(618, 451, 182, 29);
    textArea_CPU_Usage.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_CPU_Usage.setLinespacing(0);
    Unicode::snprintf(textArea_CPU_UsageBuffer, TEXTAREA_CPU_USAGE_SIZE, "%s", TypedText(T_SINGLEUSEID287).getText());
    textArea_CPU_Usage.setWildcard(textArea_CPU_UsageBuffer);
    textArea_CPU_Usage.setTypedText(TypedText(T_SINGLEUSEID286));

    buttonWithLabel_Back.setXY(315, 421);
    buttonWithLabel_Back.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_Back.setLabelText(TypedText(T_SINGLEUSEID288));
    buttonWithLabel_Back.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Back.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Back.setAction(buttonCallback);

    slider_TimeRange.setXY(410, 120);
    slider_TimeRange.setBitmaps(Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_BACK_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_FILL_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider_TimeRange.setupHorizontalSlider(2, 19, 2, 0, 310);
    slider_TimeRange.setValueRange(0, 1000);
    slider_TimeRange.setValue(720);
    slider_TimeRange.setNewValueCallback(sliderValueChangedCallback);

    slider_Y_AxisMin.setXY(410, 220);
    slider_Y_AxisMin.setBitmaps(Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_BACK_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_FILL_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider_Y_AxisMin.setupHorizontalSlider(2, 19, 2, 0, 310);
    slider_Y_AxisMin.setValueRange(0, 1000);
    slider_Y_AxisMin.setValue(1);
    slider_Y_AxisMin.setNewValueCallback(sliderValueChangedCallback);

    textArea_TimeRange.setPosition(410, 70, 390, 49);
    textArea_TimeRange.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_TimeRange.setLinespacing(0);
    Unicode::snprintf(textArea_TimeRangeBuffer, TEXTAREA_TIMERANGE_SIZE, "%s", TypedText(T_SINGLEUSEID295).getText());
    textArea_TimeRange.setWildcard(textArea_TimeRangeBuffer);
    textArea_TimeRange.setTypedText(TypedText(T_SINGLEUSEID289));

    textArea_Y_AxisMin.setPosition(410, 170, 390, 49);
    textArea_Y_AxisMin.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Y_AxisMin.setLinespacing(0);
    Unicode::snprintf(textArea_Y_AxisMinBuffer, TEXTAREA_Y_AXISMIN_SIZE, "%s", TypedText(T_SINGLEUSEID293).getText());
    textArea_Y_AxisMin.setWildcard(textArea_Y_AxisMinBuffer);
    textArea_Y_AxisMin.setTypedText(TypedText(T_SINGLEUSEID290));

    slider_Y_AxisMax.setXY(410, 320);
    slider_Y_AxisMax.setBitmaps(Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_BACK_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_FILL_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider_Y_AxisMax.setupHorizontalSlider(2, 19, 2, 0, 310);
    slider_Y_AxisMax.setValueRange(0, 1000);
    slider_Y_AxisMax.setValue(1);
    slider_Y_AxisMax.setNewValueCallback(sliderValueChangedCallback);

    textArea_Y_AxisMax.setPosition(410, 270, 390, 49);
    textArea_Y_AxisMax.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Y_AxisMax.setLinespacing(0);
    Unicode::snprintf(textArea_Y_AxisMaxBuffer, TEXTAREA_Y_AXISMAX_SIZE, "%s", TypedText(T_SINGLEUSEID294).getText());
    textArea_Y_AxisMax.setWildcard(textArea_Y_AxisMaxBuffer);
    textArea_Y_AxisMax.setTypedText(TypedText(T_SINGLEUSEID292));

    textArea_Auto_Y_Range.setPosition(568, 7, 130, 25);
    textArea_Auto_Y_Range.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Auto_Y_Range.setLinespacing(0);
    textArea_Auto_Y_Range.setTypedText(TypedText(T_SINGLEUSEID296));

    toggleButton_Auto_Y_Range.setXY(704, 0);
    toggleButton_Auto_Y_Range.setBitmaps(Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_SMALL_BUTTON_OFF_ID), Bitmap(BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_SMALL_BUTTON_ON_ID));
    toggleButton_Auto_Y_Range.setAction(buttonCallback);

    add(backgroundBox_Black);
    add(toggleButton_Voltage);
    add(toggleButton_Current);
    add(toggleButton_Frequency);
    add(toggleButton_Power);
    add(textArea_Power);
    add(textArea_Frequency);
    add(textArea_Current);
    add(textArea_Voltage);
    add(textArea_Title);
    add(textArea_CPU_Usage);
    add(buttonWithLabel_Back);
    add(slider_TimeRange);
    add(slider_Y_AxisMin);
    add(textArea_TimeRange);
    add(textArea_Y_AxisMin);
    add(slider_Y_AxisMax);
    add(textArea_Y_AxisMax);
    add(textArea_Auto_Y_Range);
    add(toggleButton_Auto_Y_Range);
}

void Screen_Module1_SignalsViewBase::setupScreen()
{

}

void Screen_Module1_SignalsViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &toggleButton_Voltage)
    {
        //Interaction_SetVoltageGraph
        //When toggleButton_Voltage clicked call virtual function
        //Call setVoltageGraphVisible
        setVoltageGraphVisible();
    }
    else if (&src == &toggleButton_Current)
    {
        //Interaction_SetCurrentGraph
        //When toggleButton_Current clicked call virtual function
        //Call setCurrentGraphVisible
        setCurrentGraphVisible();
    }
    else if (&src == &toggleButton_Frequency)
    {
        //Interaction_SetFrequencyGraph
        //When toggleButton_Frequency clicked call virtual function
        //Call setFrequencyGraphVisible
        setFrequencyGraphVisible();
    }
    else if (&src == &toggleButton_Power)
    {
        //Interaction_SetPowerGraph
        //When toggleButton_Power clicked call virtual function
        //Call setPowerGraphVisible
        setPowerGraphVisible();
    }
    else if (&src == &buttonWithLabel_Back)
    {
        //Interaction_GoBack
        //When buttonWithLabel_Back clicked change screen to Screen_Module1_Graph
        //Go to Screen_Module1_Graph with no screen transition
        application().gotoScreen_Module1_GraphScreenNoTransition();
    }
    else if (&src == &toggleButton_Auto_Y_Range)
    {
        //Interaction_PressedAutoRangeToggleButton
        //When toggleButton_Auto_Y_Range clicked call virtual function
        //Call pressedAutoRangeToggleButton
        pressedAutoRangeToggleButton();
    }
}

void Screen_Module1_SignalsViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider_TimeRange)
    {
        //Interaction_UpdateTimeRange
        //When slider_TimeRange value changed call virtual function
        //Call updateTimeRange
        updateTimeRange(value);
    }
    else if (&src == &slider_Y_AxisMin)
    {
        //Interaction_UpdateYAxisMin
        //When slider_Y_AxisMin value changed call virtual function
        //Call updateY_AxisMin
        updateY_AxisMin(value);
    }
    else if (&src == &slider_Y_AxisMax)
    {
        //Interaction_UpdateYAxisMax
        //When slider_Y_AxisMax value changed call virtual function
        //Call updateY_AxisMax
        updateY_AxisMax(value);
    }
}