#ifndef SCREEN_MODULE1_SIGNALS_PRESENTER_HPP
#define SCREEN_MODULE1_SIGNALS_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1_SignalsView;

class Screen_Module1_SignalsPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module1_SignalsPresenter(Screen_Module1_SignalsView& v);
    
    void notifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module1_SignalsPresenter() {};

private:
    Screen_Module1_SignalsPresenter();

    Screen_Module1_SignalsView& view;
};

#endif
