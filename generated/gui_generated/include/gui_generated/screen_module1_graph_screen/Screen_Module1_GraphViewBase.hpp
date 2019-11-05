/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN_MODULE1_GRAPHVIEWBASE_HPP
#define SCREEN_MODULE1_GRAPHVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

class Screen_Module1_GraphViewBase : public touchgfx::View<Screen_Module1_GraphPresenter>
{
public:
    Screen_Module1_GraphViewBase();
    virtual ~Screen_Module1_GraphViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box backgroundBox_Black;
    touchgfx::TextAreaWithOneWildcard textArea_CPU_Usage;
    touchgfx::ButtonWithLabel buttonWithLabel_Back;
    touchgfx::TextAreaWithOneWildcard textArea_GraphRangeTop;
    touchgfx::TextAreaWithOneWildcard textArea_GraphRangeBottom;
    touchgfx::Line line_VericalAxis;
    touchgfx::PainterRGB565 line_VericalAxisPainter;
    touchgfx::TextAreaWithOneWildcard textArea_GraphRangeLeft;
    touchgfx::TextAreaWithOneWildcard textArea_GraphRangeRight;
    touchgfx::ButtonWithLabel buttonWithLabel_Signals;
    touchgfx::Line line_HorizontalAxis_1;
    touchgfx::PainterRGB565 line_HorizontalAxis_1Painter;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA_CPU_USAGE_SIZE = 6;
    touchgfx::Unicode::UnicodeChar textArea_CPU_UsageBuffer[TEXTAREA_CPU_USAGE_SIZE];
    static const uint16_t TEXTAREA_GRAPHRANGETOP_SIZE = 11;
    touchgfx::Unicode::UnicodeChar textArea_GraphRangeTopBuffer[TEXTAREA_GRAPHRANGETOP_SIZE];
    static const uint16_t TEXTAREA_GRAPHRANGEBOTTOM_SIZE = 12;
    touchgfx::Unicode::UnicodeChar textArea_GraphRangeBottomBuffer[TEXTAREA_GRAPHRANGEBOTTOM_SIZE];
    static const uint16_t TEXTAREA_GRAPHRANGELEFT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea_GraphRangeLeftBuffer[TEXTAREA_GRAPHRANGELEFT_SIZE];
    static const uint16_t TEXTAREA_GRAPHRANGERIGHT_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea_GraphRangeRightBuffer[TEXTAREA_GRAPHRANGERIGHT_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen_Module1_GraphViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 24000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

};

#endif // SCREEN_MODULE1_GRAPHVIEWBASE_HPP
