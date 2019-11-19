#ifndef SCREEN_MODULE3_DATAPRESENTER_HPP
#define SCREEN_MODULE3_DATAPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_DataView;

class Screen_Module3_DataPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module3_DataPresenter(Screen_Module3_DataView& v);

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

    virtual ~Screen_Module3_DataPresenter() {};

private:
    Screen_Module3_DataPresenter();

    Screen_Module3_DataView& view;
};


#endif // SCREEN_MODULE3_DATAPRESENTER_HPP
