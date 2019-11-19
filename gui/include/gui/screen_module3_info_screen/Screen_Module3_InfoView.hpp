#ifndef SCREEN_MODULE3_INFO_VIEW_HPP
#define SCREEN_MODULE3_INFO_VIEW_HPP

#include <gui_generated/screen_module3_info_screen/Screen_Module3_InfoViewBase.hpp>
#include <gui/screen_module3_info_screen/Screen_Module3_InfoPresenter.hpp>

class Screen_Module3_InfoView : public Screen_Module3_InfoViewBase
{
public:
    Screen_Module3_InfoView();
    virtual ~Screen_Module3_InfoView() {}
    
    void updateCpuUsage(uint8_t value);
};

#endif
