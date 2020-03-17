#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_SettingsView;

class Screen_Module3_SettingsPresenter : public Presenter, public ModelListener
{
public:
  Screen_Module3_SettingsPresenter(Screen_Module3_SettingsView& v);
  
  virtual void NotifyNewValueToSet(UartPacket& uartPacket);
  void NotifyNewCpuUsageValue(uint8_t value);
  
  virtual ~Screen_Module3_SettingsPresenter() override {};
  
private:
  Screen_Module3_SettingsPresenter();
  
  Screen_Module3_SettingsView& view;
};