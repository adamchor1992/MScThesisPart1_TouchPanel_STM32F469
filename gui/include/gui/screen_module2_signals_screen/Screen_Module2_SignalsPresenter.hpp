#ifndef SCREEN_MODULE2_SIGNALS_PRESENTER_HPP
#define SCREEN_MODULE2_SIGNALS_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_SignalsView;

class Screen_Module2_SignalsPresenter : public Presenter, public ModelListener
{
public:
	Screen_Module2_SignalsPresenter(Screen_Module2_SignalsView& v);

	void notifyNewCpuUsageValue(uint8_t value);

	virtual ~Screen_Module2_SignalsPresenter() {};

private:
	Screen_Module2_SignalsPresenter();

	Screen_Module2_SignalsView& view;
};

#endif
