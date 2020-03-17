#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_MainView;

class Screen_MainPresenter : public Presenter, public ModelListener
{
public:
  Screen_MainPresenter(Screen_MainView& v);
  virtual ~Screen_MainPresenter() override {};
  
  void NotifyNewCpuUsageValue(uint8_t value);
  void NotifyAllInitPacketsReceived(UartPacket& uartPacket);
  
private:
  Screen_MainPresenter();
  
  Screen_MainView& view;
};