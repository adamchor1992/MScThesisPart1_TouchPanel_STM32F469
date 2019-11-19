#ifndef SCREEN_MODULE3_INFOPRESENTER_HPP
#define SCREEN_MODULE3_INFOPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_InfoView;

class Screen_Module3_InfoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module3_InfoPresenter(Screen_Module3_InfoView& v);

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

    virtual ~Screen_Module3_InfoPresenter() {};

private:
    Screen_Module3_InfoPresenter();

    Screen_Module3_InfoView& view;
};


#endif // SCREEN_MODULE3_INFOPRESENTER_HPP
