#pragma once

#include <gui_generated/screen_module2_info_screen/Screen_Module2_InfoViewBase.hpp>
#include <gui/screen_module2_info_screen/Screen_Module2_InfoPresenter.hpp>

class Screen_Module2_InfoView : public Screen_Module2_InfoViewBase
{
public:
    Screen_Module2_InfoView();
    virtual ~Screen_Module2_InfoView() override {}
    
    void UpdateCpuUsage(uint8_t value);
};