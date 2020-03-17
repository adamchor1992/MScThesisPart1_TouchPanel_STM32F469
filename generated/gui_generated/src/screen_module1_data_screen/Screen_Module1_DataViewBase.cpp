/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_module1_data_screen/Screen_Module1_DataViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

Screen_Module1_DataViewBase::Screen_Module1_DataViewBase() :
    buttonCallback(this, &Screen_Module1_DataViewBase::buttonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    backgroundBox_Black.setPosition(0, 0, 800, 480);
    backgroundBox_Black.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));

    textArea_CPU_Usage.setPosition(618, 451, 182, 29);
    textArea_CPU_Usage.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_CPU_Usage.setLinespacing(0);
    Unicode::snprintf(textArea_CPU_UsageBuffer, TEXTAREA_CPU_USAGE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID70).getText());
    textArea_CPU_Usage.setWildcard(textArea_CPU_UsageBuffer);
    textArea_CPU_Usage.setTypedText(touchgfx::TypedText(T_SINGLEUSEID69));

    buttonWithLabel_GoToMainMenu.setXY(340, 421);
    buttonWithLabel_GoToMainMenu.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_GoToMainMenu.setLabelText(touchgfx::TypedText(T_SINGLEUSEID66));
    buttonWithLabel_GoToMainMenu.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_GoToMainMenu.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_GoToMainMenu.setAction(buttonCallback);

    buttonWithLabel_Graph.setXY(170, 421);
    buttonWithLabel_Graph.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_Graph.setLabelText(touchgfx::TypedText(T_SINGLEUSEID165));
    buttonWithLabel_Graph.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Graph.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Graph.setAction(buttonCallback);

    buttonWithLabel_Settings.setXY(0, 421);
    buttonWithLabel_Settings.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_Settings.setLabelText(touchgfx::TypedText(T_SINGLEUSEID141));
    buttonWithLabel_Settings.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Settings.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Settings.setAction(buttonCallback);

    line1.setPosition(248, 55, 15, 323);
    line1Painter.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    line1.setPainter(line1Painter);
    line1.setStart(5, 5);
    line1.setEnd(5, 317);
    line1.setLineWidth(5);
    line1.setLineEndingStyle(touchgfx::Line::ROUND_CAP_ENDING);

    textAreaContainer.setPosition(-1, 65, 683, 298);

    textArea_Parameter1Name.setPosition(0, 9, 249, 49);
    textArea_Parameter1Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter1Name.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter1NameBuffer, TEXTAREA_PARAMETER1NAME_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID305).getText());
    textArea_Parameter1Name.setWildcard(textArea_Parameter1NameBuffer);
    textArea_Parameter1Name.setTypedText(touchgfx::TypedText(T_SINGLEUSEID79));
    textAreaContainer.add(textArea_Parameter1Name);

    textArea_Parameter2Name.setPosition(0, 57, 249, 49);
    textArea_Parameter2Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter2Name.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter2NameBuffer, TEXTAREA_PARAMETER2NAME_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID307).getText());
    textArea_Parameter2Name.setWildcard(textArea_Parameter2NameBuffer);
    textArea_Parameter2Name.setTypedText(touchgfx::TypedText(T_SINGLEUSEID306));
    textAreaContainer.add(textArea_Parameter2Name);

    textArea_Parameter3Name.setPosition(0, 106, 249, 49);
    textArea_Parameter3Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter3Name.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter3NameBuffer, TEXTAREA_PARAMETER3NAME_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID309).getText());
    textArea_Parameter3Name.setWildcard(textArea_Parameter3NameBuffer);
    textArea_Parameter3Name.setTypedText(touchgfx::TypedText(T_SINGLEUSEID308));
    textAreaContainer.add(textArea_Parameter3Name);

    textArea_Parameter4Name.setPosition(0, 155, 249, 49);
    textArea_Parameter4Name.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter4Name.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter4NameBuffer, TEXTAREA_PARAMETER4NAME_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID311).getText());
    textArea_Parameter4Name.setWildcard(textArea_Parameter4NameBuffer);
    textArea_Parameter4Name.setTypedText(touchgfx::TypedText(T_SINGLEUSEID310));
    textAreaContainer.add(textArea_Parameter4Name);

    textArea_Parameter1Value.setPosition(264, 9, 249, 49);
    textArea_Parameter1Value.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter1Value.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter1ValueBuffer, TEXTAREA_PARAMETER1VALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID313).getText());
    textArea_Parameter1Value.setWildcard(textArea_Parameter1ValueBuffer);
    textArea_Parameter1Value.setTypedText(touchgfx::TypedText(T_SINGLEUSEID312));
    textAreaContainer.add(textArea_Parameter1Value);

    textArea_Parameter2Value.setPosition(264, 57, 249, 49);
    textArea_Parameter2Value.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter2Value.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter2ValueBuffer, TEXTAREA_PARAMETER2VALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID315).getText());
    textArea_Parameter2Value.setWildcard(textArea_Parameter2ValueBuffer);
    textArea_Parameter2Value.setTypedText(touchgfx::TypedText(T_SINGLEUSEID314));
    textAreaContainer.add(textArea_Parameter2Value);

    textArea_Parameter3Value.setPosition(264, 106, 249, 49);
    textArea_Parameter3Value.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter3Value.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter3ValueBuffer, TEXTAREA_PARAMETER3VALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID317).getText());
    textArea_Parameter3Value.setWildcard(textArea_Parameter3ValueBuffer);
    textArea_Parameter3Value.setTypedText(touchgfx::TypedText(T_SINGLEUSEID316));
    textAreaContainer.add(textArea_Parameter3Value);

    textArea_Parameter4Value.setPosition(264, 155, 249, 49);
    textArea_Parameter4Value.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Parameter4Value.setLinespacing(0);
    Unicode::snprintf(textArea_Parameter4ValueBuffer, TEXTAREA_PARAMETER4VALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID319).getText());
    textArea_Parameter4Value.setWildcard(textArea_Parameter4ValueBuffer);
    textArea_Parameter4Value.setTypedText(touchgfx::TypedText(T_SINGLEUSEID318));
    textAreaContainer.add(textArea_Parameter4Value);

    textArea_ShowAll.setXY(598, 100);
    textArea_ShowAll.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_ShowAll.setLinespacing(0);
    textArea_ShowAll.setTypedText(touchgfx::TypedText(T_SINGLEUSEID9581));
    textAreaContainer.add(textArea_ShowAll);

    textArea_Title.setXY(309, 0);
    textArea_Title.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea_Title.setLinespacing(0);
    textArea_Title.setTypedText(touchgfx::TypedText(T_SINGLEUSEID63));

    button1_ShowAll.setXY(609, 190);
    button1_ShowAll.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_ICON_BUTTON_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_ICON_BUTTON_PRESSED_ID));
    button1_ShowAll.setAction(buttonCallback);

    buttonWithLabel_Info.setXY(630, 0);
    buttonWithLabel_Info.setBitmaps(touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID), touchgfx::Bitmap(BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    buttonWithLabel_Info.setLabelText(touchgfx::TypedText(T_SINGLEUSEID251));
    buttonWithLabel_Info.setLabelColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Info.setLabelColorPressed(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    buttonWithLabel_Info.setAction(buttonCallback);

    add(backgroundBox_Black);
    add(textArea_CPU_Usage);
    add(buttonWithLabel_GoToMainMenu);
    add(buttonWithLabel_Graph);
    add(buttonWithLabel_Settings);
    add(line1);
    add(textAreaContainer);
    add(textArea_Title);
    add(button1_ShowAll);
    add(buttonWithLabel_Info);
}

void Screen_Module1_DataViewBase::setupScreen()
{

}

void Screen_Module1_DataViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonWithLabel_GoToMainMenu)
    {
        //Interaction_GoBackToMainMenu
        //When buttonWithLabel_GoToMainMenu clicked change screen to Screen_Main
        //Go to Screen_Main with no screen transition
        application().gotoScreen_MainScreenNoTransition();
    }
    else if (&src == &buttonWithLabel_Graph)
    {
        //Interaction_GoToGraphScreen
        //When buttonWithLabel_Graph clicked change screen to Screen_Module1_Graph
        //Go to Screen_Module1_Graph with no screen transition
        application().gotoScreen_Module1_GraphScreenNoTransition();
    }
    else if (&src == &buttonWithLabel_Settings)
    {
        //Interaction_GoToSettingsScreen
        //When buttonWithLabel_Settings clicked change screen to Screen_Module1_Settings
        //Go to Screen_Module1_Settings with no screen transition
        application().gotoScreen_Module1_SettingsScreenNoTransition();
    }
    else if (&src == &button1_ShowAll)
    {
        //Interaction_ShowAll
        //When button1_ShowAll clicked call virtual function
        //Call ShowAll
        ShowAll();
    }
    else if (&src == &buttonWithLabel_Info)
    {
        //Interaction_GoToInfoScreen
        //When buttonWithLabel_Info clicked change screen to Screen_Module1_Info
        //Go to Screen_Module1_Info with no screen transition
        application().gotoScreen_Module1_InfoScreenNoTransition();
    }
}
