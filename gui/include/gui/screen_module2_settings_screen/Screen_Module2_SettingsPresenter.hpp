#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_SettingsView;

class Screen_Module2_SettingsPresenter : public Presenter, public ModelListener
{
public:
  Screen_Module2_SettingsPresenter(Screen_Module2_SettingsView& v);
  
  virtual void NotifyNewValueToSet(UartPacket& uartPacket);
  void NotifyNewCpuUsageValue(uint8_t value);
  
  virtual ~Screen_Module2_SettingsPresenter() override {};
  
private:
  Screen_Module2_SettingsPresenter();
  
  Screen_Module2_SettingsView& view;
};