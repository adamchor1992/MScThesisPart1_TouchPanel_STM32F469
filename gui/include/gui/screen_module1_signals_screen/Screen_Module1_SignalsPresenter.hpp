#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1_SignalsView;

class Screen_Module1_SignalsPresenter : public Presenter, public ModelListener
{
public:
  Screen_Module1_SignalsPresenter(Screen_Module1_SignalsView& v);
  virtual ~Screen_Module1_SignalsPresenter() override {};
  
  void NotifyNewCpuUsageValue(uint8_t value);
  
private:
  Screen_Module1_SignalsPresenter();
  
  Screen_Module1_SignalsView& view;
};