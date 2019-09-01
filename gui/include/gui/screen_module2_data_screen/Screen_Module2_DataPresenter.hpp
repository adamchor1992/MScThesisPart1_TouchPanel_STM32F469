#ifndef SCREEN_MODULE2_DATA_PRESENTER_HPP
#define SCREEN_MODULE2_DATA_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_DataView;

class Screen_Module2_DataPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module2_DataPresenter(Screen_Module2_DataView& v);

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

    virtual ~Screen_Module2_DataPresenter() {};

private:
    Screen_Module2_DataPresenter();

    Screen_Module2_DataView& view;
};


#endif // SCREEN_MODULE2_DATA_PRESENTER_HPP
