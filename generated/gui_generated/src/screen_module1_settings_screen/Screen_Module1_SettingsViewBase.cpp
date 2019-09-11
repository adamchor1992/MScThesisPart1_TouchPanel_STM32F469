/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_module1_settings_screen/Screen_Module1_SettingsViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

Screen_Module1_SettingsViewBase::Screen_Module1_SettingsViewBase() :
    buttonCallback(this, &Screen_Module1_SettingsViewBase::buttonCallbackHandler),
    sliderValueChangedCallback(this, &Screen_Module1_SettingsViewBase::sliderValueChangedCallbackHandler)
{
    CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    backgroundBox_Black.setPosition(0, 0, 800, 480);
    backgroundBox_Black.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    buttonWithLabel_SetValue.setXY(495, 359);
    buttonWithLabel_SetValue.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_SetValue.setLabelText(TypedText(T_SINGLEUSEID131));
    buttonWithLabel_SetValue.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_SetValue.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_SetValue.setAction(buttonCallback);

    slider_Value.setXY(392, 296);
    slider_Value.setBitmaps(Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_BACK_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_SLIDER_ROUND_FILL_ID), Bitmap(BITMAP_BLUE_SLIDER_HORIZONTAL_MEDIUM_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider_Value.setupHorizontalSlider(2, 19, 2, 0, 310);
    slider_Value.setValueRange(0, 1000);
    slider_Value.setValue(0);
    slider_Value.setNewValueCallback(sliderValueChangedCallback);

    radioButtonParameter2.setXY(62, 113);
    radioButtonParameter2.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter2.setSelected(false);
    radioButtonParameter2.setDeselectionEnabled(false);

    textArea_Parameter2.setXY(0, 113);
    textArea_Parameter2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter2.setLinespacing(0);
    textArea_Parameter2.setTypedText(TypedText(T_SINGLEUSEID132));

    radioButtonParameter1.setXY(62, 73);
    radioButtonParameter1.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter1.setSelected(true);
    radioButtonParameter1.setDeselectionEnabled(false);

    textArea_Parameter1.setXY(0, 73);
    textArea_Parameter1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter1.setLinespacing(0);
    textArea_Parameter1.setTypedText(TypedText(T_SINGLEUSEID133));

    textArea_ValueToSet.setPosition(402, 209, 398, 49);
    textArea_ValueToSet.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_ValueToSet.setLinespacing(0);
    Unicode::snprintf(textArea_ValueToSetBuffer, TEXTAREA_VALUETOSET_SIZE, "%s", TypedText(T_SINGLEUSEID135).getText());
    textArea_ValueToSet.setWildcard(textArea_ValueToSetBuffer);
    textArea_ValueToSet.setTypedText(TypedText(T_SINGLEUSEID134));

    textArea_ParameterToSet.setPosition(0, 49, 106, 24);
    textArea_ParameterToSet.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_ParameterToSet.setLinespacing(0);
    textArea_ParameterToSet.setTypedText(TypedText(T_SINGLEUSEID136));

    textArea_Title.setXY(219, 0);
    textArea_Title.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Title.setLinespacing(0);
    textArea_Title.setTypedText(TypedText(T_SINGLEUSEID137));

    textArea_Parameter3.setXY(0, 153);
    textArea_Parameter3.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter3.setLinespacing(0);
    textArea_Parameter3.setTypedText(TypedText(T_SINGLEUSEID138));

    textArea_Parameter4.setXY(0, 193);
    textArea_Parameter4.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter4.setLinespacing(0);
    textArea_Parameter4.setTypedText(TypedText(T_SINGLEUSEID139));

    radioButtonParameter3.setXY(62, 153);
    radioButtonParameter3.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter3.setSelected(false);
    radioButtonParameter3.setDeselectionEnabled(false);

    radioButtonParameter4.setXY(62, 193);
    radioButtonParameter4.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter4.setSelected(false);
    radioButtonParameter4.setDeselectionEnabled(false);

    buttonWithLabel_Back.setXY(295, 419);
    buttonWithLabel_Back.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_Back.setLabelText(TypedText(T_SINGLEUSEID140));
    buttonWithLabel_Back.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Back.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Back.setAction(buttonCallback);

    textArea_CPU_Usage.setPosition(618, 451, 182, 29);
    textArea_CPU_Usage.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_CPU_Usage.setLinespacing(0);
    Unicode::snprintf(textArea_CPU_UsageBuffer, TEXTAREA_CPU_USAGE_SIZE, "%s", TypedText(T_SINGLEUSEID143).getText());
    textArea_CPU_Usage.setWildcard(textArea_CPU_UsageBuffer);
    textArea_CPU_Usage.setTypedText(TypedText(T_SINGLEUSEID142));

    textArea_Parameter5.setXY(0, 233);
    textArea_Parameter5.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter5.setLinespacing(0);
    textArea_Parameter5.setTypedText(TypedText(T_SINGLEUSEID189));

    textArea_Parameter6.setXY(0, 273);
    textArea_Parameter6.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter6.setLinespacing(0);
    textArea_Parameter6.setTypedText(TypedText(T_SINGLEUSEID190));

    textArea_Parameter7.setXY(0, 313);
    textArea_Parameter7.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter7.setLinespacing(0);
    textArea_Parameter7.setTypedText(TypedText(T_SINGLEUSEID191));

    textArea_Parameter8.setXY(0, 353);
    textArea_Parameter8.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter8.setLinespacing(0);
    textArea_Parameter8.setTypedText(TypedText(T_SINGLEUSEID192));

    radioButtonParameter5.setXY(62, 233);
    radioButtonParameter5.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter5.setSelected(false);
    radioButtonParameter5.setDeselectionEnabled(false);

    radioButtonParameter6.setXY(62, 273);
    radioButtonParameter6.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter6.setSelected(false);
    radioButtonParameter6.setDeselectionEnabled(false);

    radioButtonParameter7.setXY(62, 313);
    radioButtonParameter7.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter7.setSelected(false);
    radioButtonParameter7.setDeselectionEnabled(false);

    radioButtonParameter8.setXY(62, 353);
    radioButtonParameter8.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter8.setSelected(false);
    radioButtonParameter8.setDeselectionEnabled(false);

    line1.setPosition(107, 47, 15, 432);
    line1Painter.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(5, 5);
    line1.setEnd(5, 429);
    line1.setLineWidth(4);
    line1.setLineEndingStyle(Line::ROUND_CAP_ENDING);

    buttonWithLabel_EnableParameter.setXY(150, 65);
    buttonWithLabel_EnableParameter.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_PRESSED_ID));
    buttonWithLabel_EnableParameter.setLabelText(TypedText(T_SINGLEUSEID195));
    buttonWithLabel_EnableParameter.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_EnableParameter.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_EnableParameter.setAction(buttonCallback);

    textArea_Parameter9.setXY(0, 393);
    textArea_Parameter9.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter9.setLinespacing(0);
    textArea_Parameter9.setTypedText(TypedText(T_SINGLEUSEID248));

    textArea_Parameter10.setXY(0, 433);
    textArea_Parameter10.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter10.setLinespacing(0);
    textArea_Parameter10.setTypedText(TypedText(T_SINGLEUSEID249));

    radioButtonParameter9.setXY(62, 393);
    radioButtonParameter9.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter9.setSelected(false);
    radioButtonParameter9.setDeselectionEnabled(false);

    radioButtonParameter10.setXY(62, 433);
    radioButtonParameter10.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter10.setSelected(false);
    radioButtonParameter10.setDeselectionEnabled(false);

    buttonWithLabel_DisableParameter.setXY(150, 145);
    buttonWithLabel_DisableParameter.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_PRESSED_ID));
    buttonWithLabel_DisableParameter.setLabelText(TypedText(T_SINGLEUSEID250));
    buttonWithLabel_DisableParameter.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_DisableParameter.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_DisableParameter.setAction(buttonCallback);

    add(backgroundBox_Black);
    add(buttonWithLabel_SetValue);
    add(slider_Value);
    add(radioButtonParameter2);
    add(textArea_Parameter2);
    add(radioButtonParameter1);
    add(textArea_Parameter1);
    add(textArea_ValueToSet);
    add(textArea_ParameterToSet);
    add(textArea_Title);
    add(textArea_Parameter3);
    add(textArea_Parameter4);
    add(radioButtonParameter3);
    add(radioButtonParameter4);
    add(buttonWithLabel_Back);
    add(textArea_CPU_Usage);
    add(textArea_Parameter5);
    add(textArea_Parameter6);
    add(textArea_Parameter7);
    add(textArea_Parameter8);
    add(radioButtonParameter5);
    add(radioButtonParameter6);
    add(radioButtonParameter7);
    add(radioButtonParameter8);
    add(line1);
    add(buttonWithLabel_EnableParameter);
    add(textArea_Parameter9);
    add(textArea_Parameter10);
    add(radioButtonParameter9);
    add(radioButtonParameter10);
    add(buttonWithLabel_DisableParameter);
    radioButtonGroup.add(radioButtonParameter2);
    radioButtonGroup.add(radioButtonParameter1);
    radioButtonGroup.add(radioButtonParameter3);
    radioButtonGroup.add(radioButtonParameter4);
    radioButtonGroup.add(radioButtonParameter5);
    radioButtonGroup.add(radioButtonParameter6);
    radioButtonGroup.add(radioButtonParameter7);
    radioButtonGroup.add(radioButtonParameter8);
    radioButtonGroup.add(radioButtonParameter9);
    radioButtonGroup.add(radioButtonParameter10);
}

void Screen_Module1_SettingsViewBase::setupScreen()
{

}

void Screen_Module1_SettingsViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel_SetValue)
    {
        //Interaction_SetValueButtonPushed
        //When buttonWithLabel_SetValue clicked call virtual function
        //Call setNewValue
        setNewValue();
    }
    else if (&src == &buttonWithLabel_Back)
    {
        //Interaction_GoBack
        //When buttonWithLabel_Back clicked change screen to Screen_Module1_Data
        //Go to Screen_Module1_Data with no screen transition
        application().gotoScreen_Module1_DataScreenNoTransition();
    }
    else if (&src == &buttonWithLabel_EnableParameter)
    {
        //Interaction_EnableParameterButtonPushed
        //When buttonWithLabel_EnableParameter clicked call virtual function
        //Call enableParameterButtonPushed
        enableParameterButtonPushed();
    }
    else if (&src == &buttonWithLabel_DisableParameter)
    {
        //Interaction_DisableParameterButtonPushed
        //When buttonWithLabel_DisableParameter clicked call virtual function
        //Call disableParameterButtonPushed
        disableParameterButtonPushed();
    }
}

void Screen_Module1_SettingsViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider_Value)
    {
        //Interaction_UpdateValueToSet
        //When slider_Value value changed call virtual function
        //Call updateValueToSet
        updateValueToSet(value);
    }
}
