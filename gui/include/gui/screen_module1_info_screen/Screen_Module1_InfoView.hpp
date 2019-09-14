#ifndef SCREEN_MODULE1_INFO_VIEW_HPP
#define SCREEN_MODULE1_INFO_VIEW_HPP

#include <gui_generated/screen_module1_info_screen/Screen_Module1_InfoViewBase.hpp>
#include <gui/screen_module1_info_screen/Screen_Module1_InfoPresenter.hpp>

class Screen_Module1_InfoView : public Screen_Module1_InfoViewBase
{
public:
    Screen_Module1_InfoView();
    virtual ~Screen_Module1_InfoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    void updateCpuUsage(uint8_t value);
};

#endif // SCREEN_MODULE1_INFO_VIEW_HPP
