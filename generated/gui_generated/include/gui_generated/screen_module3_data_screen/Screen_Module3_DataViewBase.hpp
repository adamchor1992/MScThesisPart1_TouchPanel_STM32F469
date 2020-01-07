/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN_MODULE3_DATAVIEWBASE_HPP
#define SCREEN_MODULE3_DATAVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_module3_data_screen/Screen_Module3_DataPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>

#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/mixins/ClickListener.hpp>
class Screen_Module3_DataViewBase : public touchgfx::View<Screen_Module3_DataPresenter>
{
public:
    Screen_Module3_DataViewBase();
    virtual ~Screen_Module3_DataViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void showAll()
    {
        // Override and implement this function in Screen_Module3_Data
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box backgroundBox_Black;
    touchgfx::TextAreaWithOneWildcard textArea_CPU_Usage;
    touchgfx::ButtonWithLabel buttonWithLabel_GoToMainMenu;
    touchgfx::ButtonWithLabel buttonWithLabel_Graph;
    touchgfx::ButtonWithLabel buttonWithLabel_Settings;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::Container textAreaContainer;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter1Name;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter2Name;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter3Name;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter4Name;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter1Value;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter2Value;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter3Value;
    touchgfx::ClickListener< touchgfx::TextAreaWithOneWildcard > textArea_Parameter4Value;
    touchgfx::ClickListener< touchgfx::TextArea > textArea_ShowAll;

    touchgfx::TextArea textArea_Title;
    touchgfx::Button button1_ShowAll;
    touchgfx::ButtonWithLabel buttonWithLabel_Info;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA_CPU_USAGE_SIZE = 6;
    touchgfx::Unicode::UnicodeChar textArea_CPU_UsageBuffer[TEXTAREA_CPU_USAGE_SIZE];
    static const uint16_t TEXTAREA_PARAMETER1NAME_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter1NameBuffer[TEXTAREA_PARAMETER1NAME_SIZE];
    static const uint16_t TEXTAREA_PARAMETER2NAME_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter2NameBuffer[TEXTAREA_PARAMETER2NAME_SIZE];
    static const uint16_t TEXTAREA_PARAMETER3NAME_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter3NameBuffer[TEXTAREA_PARAMETER3NAME_SIZE];
    static const uint16_t TEXTAREA_PARAMETER4NAME_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter4NameBuffer[TEXTAREA_PARAMETER4NAME_SIZE];
    static const uint16_t TEXTAREA_PARAMETER1VALUE_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter1ValueBuffer[TEXTAREA_PARAMETER1VALUE_SIZE];
    static const uint16_t TEXTAREA_PARAMETER2VALUE_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter2ValueBuffer[TEXTAREA_PARAMETER2VALUE_SIZE];
    static const uint16_t TEXTAREA_PARAMETER3VALUE_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter3ValueBuffer[TEXTAREA_PARAMETER3VALUE_SIZE];
    static const uint16_t TEXTAREA_PARAMETER4VALUE_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_Parameter4ValueBuffer[TEXTAREA_PARAMETER4VALUE_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen_Module3_DataViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 12000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

};

#endif // SCREEN_MODULE3_DATAVIEWBASE_HPP
