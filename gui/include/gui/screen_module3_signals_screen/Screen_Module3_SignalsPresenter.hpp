#ifndef SCREEN_MODULE3_SIGNALS_PRESENTER_HPP
#define SCREEN_MODULE3_SIGNALS_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_SignalsView;

class Screen_Module3_SignalsPresenter : public Presenter, public ModelListener
{
public:
	Screen_Module3_SignalsPresenter(Screen_Module3_SignalsView& v);

	void notifyNewCpuUsageValue(uint8_t value);

	virtual ~Screen_Module3_SignalsPresenter() {};

private:
	Screen_Module3_SignalsPresenter();

	Screen_Module3_SignalsView& view;
};

#endif
