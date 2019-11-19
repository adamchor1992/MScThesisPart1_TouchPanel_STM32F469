#ifndef SCREEN_MODULE2_INFO_VIEW_HPP
#define SCREEN_MODULE2_INFO_VIEW_HPP

#include <gui_generated/screen_module2_info_screen/Screen_Module2_InfoViewBase.hpp>
#include <gui/screen_module2_info_screen/Screen_Module2_InfoPresenter.hpp>

class Screen_Module2_InfoView : public Screen_Module2_InfoViewBase
{
public:
    Screen_Module2_InfoView();
    virtual ~Screen_Module2_InfoView() {}
    
    void updateCpuUsage(uint8_t value);
};

#endif
