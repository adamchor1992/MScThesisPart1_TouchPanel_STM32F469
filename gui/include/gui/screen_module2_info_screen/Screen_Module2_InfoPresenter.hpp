#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_InfoView;

class Screen_Module2_InfoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module2_InfoPresenter(Screen_Module2_InfoView& v);

    void NotifyNewCpuUsageValue(uint8_t value);
    
    virtual ~Screen_Module2_InfoPresenter() override {};

private:
    Screen_Module2_InfoPresenter();

    Screen_Module2_InfoView& view;
};