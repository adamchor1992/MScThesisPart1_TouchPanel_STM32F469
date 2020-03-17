#pragma once

#include <gui_generated/screen_module3_info_screen/Screen_Module3_InfoViewBase.hpp>
#include <gui/screen_module3_info_screen/Screen_Module3_InfoPresenter.hpp>

class Screen_Module3_InfoView : public Screen_Module3_InfoViewBase
{
public:
    Screen_Module3_InfoView();
    virtual ~Screen_Module3_InfoView() override {}
    
    void UpdateCpuUsage(uint8_t value);
};