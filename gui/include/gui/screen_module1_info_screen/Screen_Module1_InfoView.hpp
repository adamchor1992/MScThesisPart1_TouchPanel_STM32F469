#pragma once

#include <gui_generated/screen_module1_info_screen/Screen_Module1_InfoViewBase.hpp>
#include <gui/screen_module1_info_screen/Screen_Module1_InfoPresenter.hpp>

class Screen_Module1_InfoView : public Screen_Module1_InfoViewBase
{
public:
    Screen_Module1_InfoView();
    virtual ~Screen_Module1_InfoView() override {}
    
    void UpdateCpuUsage(uint8_t value);
};