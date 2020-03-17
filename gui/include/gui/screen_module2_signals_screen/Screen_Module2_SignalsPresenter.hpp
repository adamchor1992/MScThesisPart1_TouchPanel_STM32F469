#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_SignalsView;

class Screen_Module2_SignalsPresenter : public Presenter, public ModelListener
{
public:
  Screen_Module2_SignalsPresenter(Screen_Module2_SignalsView& v);
  virtual ~Screen_Module2_SignalsPresenter() override {};
  
  void NotifyNewCpuUsageValue(uint8_t value);
  
private:
  Screen_Module2_SignalsPresenter();
  
  Screen_Module2_SignalsView& view;
};