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
protected:
};

#endif // SCREEN_MODULE1_SIGNALS_VIEW_HPP
