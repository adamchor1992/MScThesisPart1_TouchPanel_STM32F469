#pragma once

#include <gui_generated/screen_module2_data_screen/Screen_Module2_DataViewBase.hpp>
#include <gui/screen_module2_data_screen/Screen_Module2_DataPresenter.hpp>

class Screen_Module2_DataView : public Screen_Module2_DataViewBase
{
public:
  Screen_Module2_DataView();
  virtual ~Screen_Module2_DataView() override {}
  virtual void setupScreen() override;
  
  // Declaring callback handler
  void TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& e);
  
  void UpdateGuiPacketData(UartPacket& uartPacket);
  void UpdateCpuUsage(uint8_t value);
  
  // Show all text areas again
  void ShowAll() override;
  
protected:
  // Declaring callback type of TextAreaWithOneWildcard and clickEvent
  Callback<Screen_Module2_DataView, const TextAreaWithOneWildcard&, const ClickEvent&> TextAreaClickedCallback;
};