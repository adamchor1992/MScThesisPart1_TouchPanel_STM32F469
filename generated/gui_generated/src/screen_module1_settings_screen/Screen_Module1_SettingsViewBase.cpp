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

    radioButtonParameter2.setXY(250, 106);
    radioButtonParameter2.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter2.setSelected(false);
    radioButtonParameter2.setDeselectionEnabled(false);

    radioButtonParameter1.setXY(250, 66);
    radioButtonParameter1.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter1.setSelected(true);
    radioButtonParameter1.setDeselectionEnabled(false);

    textArea_SettableParameter1Name.setPosition(0, 65, 250, 49);
    textArea_SettableParameter1Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter1Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter1NameBuffer, TEXTAREA_SETTABLEPARAMETER1NAME_SIZE, "%s", TypedText(T_SINGLEUSEID356).getText());
    textArea_SettableParameter1Name.setWildcard(textArea_SettableParameter1NameBuffer);
    textArea_SettableParameter1Name.setTypedText(TypedText(T_SINGLEUSEID133));

    textArea_ValueToSet.setPosition(402, 209, 398, 49);
    textArea_ValueToSet.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_ValueToSet.setLinespacing(0);
    Unicode::snprintf(textArea_ValueToSetBuffer, TEXTAREA_VALUETOSET_SIZE, "%s", TypedText(T_SINGLEUSEID135).getText());
    textArea_ValueToSet.setWildcard(textArea_ValueToSetBuffer);
    textArea_ValueToSet.setTypedText(TypedText(T_SINGLEUSEID134));

    textArea_ParameterToSet.setPosition(0, 41, 106, 24);
    textArea_ParameterToSet.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_ParameterToSet.setLinespacing(0);
    textArea_ParameterToSet.setTypedText(TypedText(T_SINGLEUSEID136));

    textArea_Title.setXY(219, 0);
    textArea_Title.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Title.setLinespacing(0);
    textArea_Title.setTypedText(TypedText(T_SINGLEUSEID137));

    radioButtonParameter3.setXY(250, 146);
    radioButtonParameter3.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter3.setSelected(false);
    radioButtonParameter3.setDeselectionEnabled(false);

    radioButtonParameter4.setXY(250, 186);
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

    radioButtonParameter5.setXY(250, 226);
    radioButtonParameter5.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter5.setSelected(false);
    radioButtonParameter5.setDeselectionEnabled(false);

    radioButtonParameter6.setXY(250, 266);
    radioButtonParameter6.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter6.setSelected(false);
    radioButtonParameter6.setDeselectionEnabled(false);

    radioButtonParameter7.setXY(250, 306);
    radioButtonParameter7.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter7.setSelected(false);
    radioButtonParameter7.setDeselectionEnabled(false);

    radioButtonParameter8.setXY(250, 346);
    radioButtonParameter8.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter8.setSelected(false);
    radioButtonParameter8.setDeselectionEnabled(false);

    line1.setPosition(292, 47, 8, 432);
    line1Painter.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(4, 5);
    line1.setEnd(4, 429);
    line1.setLineWidth(4);
    line1.setLineEndingStyle(Line::ROUND_CAP_ENDING);

    buttonWithLabel_EnableParameter.setXY(450, 65);
    buttonWithLabel_EnableParameter.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_PRESSED_ID));
    buttonWithLabel_EnableParameter.setLabelText(TypedText(T_SINGLEUSEID195));
    buttonWithLabel_EnableParameter.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_EnableParameter.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_EnableParameter.setAction(buttonCallback);

    radioButtonParameter9.setXY(250, 386);
    radioButtonParameter9.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter9.setSelected(false);
    radioButtonParameter9.setDeselectionEnabled(false);

    radioButtonParameter10.setXY(250, 426);
    radioButtonParameter10.setBitmaps(Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), Bitmap(BITMAP_BLUE_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButtonParameter10.setSelected(false);
    radioButtonParameter10.setDeselectionEnabled(false);

    buttonWithLabel_DisableParameter.setXY(450, 145);
    buttonWithLabel_DisableParameter.setBitmaps(Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_ID), Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_MEDIUM_PRESSED_ID));
    buttonWithLabel_DisableParameter.setLabelText(TypedText(T_SINGLEUSEID250));
    buttonWithLabel_DisableParameter.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_DisableParameter.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_DisableParameter.setAction(buttonCallback);

    textArea_SettableParameter2Name.setPosition(0, 105, 250, 49);
    textArea_SettableParameter2Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter2Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter2NameBuffer, TEXTAREA_SETTABLEPARAMETER2NAME_SIZE, "%s", TypedText(T_SINGLEUSEID358).getText());
    textArea_SettableParameter2Name.setWildcard(textArea_SettableParameter2NameBuffer);
    textArea_SettableParameter2Name.setTypedText(TypedText(T_SINGLEUSEID357));

    textArea_SettableParameter3Name.setPosition(0, 145, 250, 49);
    textArea_SettableParameter3Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter3Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter3NameBuffer, TEXTAREA_SETTABLEPARAMETER3NAME_SIZE, "%s", TypedText(T_SINGLEUSEID360).getText());
    textArea_SettableParameter3Name.setWildcard(textArea_SettableParameter3NameBuffer);
    textArea_SettableParameter3Name.setTypedText(TypedText(T_SINGLEUSEID359));

    textArea_SettableParameter4Name.setPosition(0, 185, 250, 49);
    textArea_SettableParameter4Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter4Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter4NameBuffer, TEXTAREA_SETTABLEPARAMETER4NAME_SIZE, "%s", TypedText(T_SINGLEUSEID362).getText());
    textArea_SettableParameter4Name.setWildcard(textArea_SettableParameter4NameBuffer);
    textArea_SettableParameter4Name.setTypedText(TypedText(T_SINGLEUSEID361));

    textArea_SettableParameter5Name.setPosition(0, 225, 250, 49);
    textArea_SettableParameter5Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter5Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter5NameBuffer, TEXTAREA_SETTABLEPARAMETER5NAME_SIZE, "%s", TypedText(T_SINGLEUSEID364).getText());
    textArea_SettableParameter5Name.setWildcard(textArea_SettableParameter5NameBuffer);
    textArea_SettableParameter5Name.setTypedText(TypedText(T_SINGLEUSEID363));

    textArea_SettableParameter6Name.setPosition(0, 265, 250, 49);
    textArea_SettableParameter6Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter6Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter6NameBuffer, TEXTAREA_SETTABLEPARAMETER6NAME_SIZE, "%s", TypedText(T_SINGLEUSEID366).getText());
    textArea_SettableParameter6Name.setWildcard(textArea_SettableParameter6NameBuffer);
    textArea_SettableParameter6Name.setTypedText(TypedText(T_SINGLEUSEID365));

    textArea_SettableParameter7Name.setPosition(0, 305, 250, 49);
    textArea_SettableParameter7Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter7Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter7NameBuffer, TEXTAREA_SETTABLEPARAMETER7NAME_SIZE, "%s", TypedText(T_SINGLEUSEID368).getText());
    textArea_SettableParameter7Name.setWildcard(textArea_SettableParameter7NameBuffer);
    textArea_SettableParameter7Name.setTypedText(TypedText(T_SINGLEUSEID367));

    textArea_SettableParameter8Name.setPosition(0, 345, 250, 49);
    textArea_SettableParameter8Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter8Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter8NameBuffer, TEXTAREA_SETTABLEPARAMETER8NAME_SIZE, "%s", TypedText(T_SINGLEUSEID370).getText());
    textArea_SettableParameter8Name.setWildcard(textArea_SettableParameter8NameBuffer);
    textArea_SettableParameter8Name.setTypedText(TypedText(T_SINGLEUSEID369));

    textArea_SettableParameter9Name.setPosition(0, 385, 250, 49);
    textArea_SettableParameter9Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter9Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter9NameBuffer, TEXTAREA_SETTABLEPARAMETER9NAME_SIZE, "%s", TypedText(T_SINGLEUSEID372).getText());
    textArea_SettableParameter9Name.setWildcard(textArea_SettableParameter9NameBuffer);
    textArea_SettableParameter9Name.setTypedText(TypedText(T_SINGLEUSEID371));

    textArea_SettableParameter10Name.setPosition(0, 425, 250, 49);
    textArea_SettableParameter10Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_SettableParameter10Name.setLinespacing(0);
    Unicode::snprintf(textArea_SettableParameter10NameBuffer, TEXTAREA_SETTABLEPARAMETER10NAME_SIZE, "%s", TypedText(T_SINGLEUSEID374).getText());
    textArea_SettableParameter10Name.setWildcard(textArea_SettableParameter10NameBuffer);
    textArea_SettableParameter10Name.setTypedText(TypedText(T_SINGLEUSEID373));

    add(backgroundBox_Black);
    add(buttonWithLabel_SetValue);
    add(slider_Value);
    add(radioButtonParameter2);
    add(radioButtonParameter1);
    add(textArea_SettableParameter1Name);
    add(textArea_ValueToSet);
    add(textArea_ParameterToSet);
    add(textArea_Title);
    add(radioButtonParameter3);
    add(radioButtonParameter4);
    add(buttonWithLabel_Back);
    add(textArea_CPU_Usage);
    add(radioButtonParameter5);
    add(radioButtonParameter6);
    add(radioButtonParameter7);
    add(radioButtonParameter8);
    add(line1);
    add(buttonWithLabel_EnableParameter);
    add(radioButtonParameter9);
    add(radioButtonParameter10);
    add(buttonWithLabel_DisableParameter);
    add(textArea_SettableParameter2Name);
    add(textArea_SettableParameter3Name);
    add(textArea_SettableParameter4Name);
    add(textArea_SettableParameter5Name);
    add(textArea_SettableParameter6Name);
    add(textArea_SettableParameter7Name);
    add(textArea_SettableParameter8Name);
    add(textArea_SettableParameter9Name);
    add(textArea_SettableParameter10Name);
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
