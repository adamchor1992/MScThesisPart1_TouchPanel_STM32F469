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

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen_Module1_SignalsPresenter() {};

private:
    Screen_Module1_SignalsPresenter();

    Screen_Module1_SignalsView& view;
};


#endif // SCREEN_MODULE1_SIGNALS_PRESENTER_HPP
