#ifndef SCREEN_MODULE1_INFO_PRESENTER_HPP
#define SCREEN_MODULE1_INFO_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1_InfoView;

class Screen_Module1_InfoPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module1_InfoPresenter(Screen_Module1_InfoView& v);
    
    void notifyNewCpuUsageValue(uint8_t value);

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

    virtual ~Screen_Module1_InfoPresenter() {};

private:
    Screen_Module1_InfoPresenter();

    Screen_Module1_InfoView& view;
};


#endif // SCREEN_MODULE1_INFO_PRESENTER_HPP
