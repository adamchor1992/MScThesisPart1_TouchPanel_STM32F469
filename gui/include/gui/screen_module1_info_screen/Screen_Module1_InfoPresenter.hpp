#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1_InfoView;

class Screen_Module1_InfoPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module1_InfoPresenter(Screen_Module1_InfoView& v);
    
    void NotifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module1_InfoPresenter() override {};

private:
    Screen_Module1_InfoPresenter();

    Screen_Module1_InfoView& view;
};