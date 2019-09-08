/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN_UART_RX_DEBUG_VIEW_BASE_HPP
#define SCREEN_UART_RX_DEBUG_VIEW_BASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_uart_rx_debug_screen/Screen_UART_RX_DebugPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class Screen_UART_RX_DebugViewBase : public touchgfx::View<Screen_UART_RX_DebugPresenter>
{
public:
    Screen_UART_RX_DebugViewBase();
    virtual ~Screen_UART_RX_DebugViewBase() {}

    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box backgroundBox_Black;
    touchgfx::ButtonWithLabel buttonWithLabel_GoToMainMenu;
    touchgfx::TextAreaWithOneWildcard textArea_CPU_Usage;
    touchgfx::TextAreaWithOneWildcard textArea_Value;
    touchgfx::TextAreaWithOneWildcard textArea_ParameterID;
    touchgfx::TextAreaWithOneWildcard textArea_ModuleID;
    touchgfx::TextAreaWithOneWildcard textArea_SourceID;
    touchgfx::TextArea textArea_Title;
    touchgfx::TextAreaWithOneWildcard textArea_TypeID;
    touchgfx::TextAreaWithOneWildcard textArea_SignID;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA_CPU_USAGE_SIZE = 6;
    touchgfx::Unicode::UnicodeChar textArea_CPU_UsageBuffer[TEXTAREA_CPU_USAGE_SIZE];
    static const uint16_t TEXTAREA_VALUE_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_ValueBuffer[TEXTAREA_VALUE_SIZE];
    static const uint16_t TEXTAREA_PARAMETERID_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textArea_ParameterIDBuffer[TEXTAREA_PARAMETERID_SIZE];
    static const uint16_t TEXTAREA_MODULEID_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textArea_ModuleIDBuffer[TEXTAREA_MODULEID_SIZE];
    static const uint16_t TEXTAREA_SOURCEID_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textArea_SourceIDBuffer[TEXTAREA_SOURCEID_SIZE];
    static const uint16_t TEXTAREA_TYPEID_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textArea_TypeIDBuffer[TEXTAREA_TYPEID_SIZE];
    static const uint16_t TEXTAREA_SIGNID_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textArea_SignIDBuffer[TEXTAREA_SIGNID_SIZE];

private:

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen_UART_RX_DebugViewBase, const touchgfx::AbstractButton&> buttonCallback;

};

#endif // SCREEN_UART_RX_DEBUG_VIEW_BASE_HPP
