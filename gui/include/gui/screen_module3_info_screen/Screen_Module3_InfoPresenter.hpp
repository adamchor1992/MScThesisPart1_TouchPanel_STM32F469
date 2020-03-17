#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_InfoView;

class Screen_Module3_InfoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module3_InfoPresenter(Screen_Module3_InfoView& v);

    void NotifyNewCpuUsageValue(uint8_t value);
    
    virtual ~Screen_Module3_InfoPresenter() override {};

private:
    Screen_Module3_InfoPresenter();

    Screen_Module3_InfoView& view;
};