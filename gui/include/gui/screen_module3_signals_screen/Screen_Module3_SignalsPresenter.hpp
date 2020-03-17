#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_SignalsView;

class Screen_Module3_SignalsPresenter : public Presenter, public ModelListener
{
public:
  Screen_Module3_SignalsPresenter(Screen_Module3_SignalsView& v);
  virtual ~Screen_Module3_SignalsPresenter() override {};
  
  void NotifyNewCpuUsageValue(uint8_t value);
  
private:
  Screen_Module3_SignalsPresenter();
  
  Screen_Module3_SignalsView& view;
};