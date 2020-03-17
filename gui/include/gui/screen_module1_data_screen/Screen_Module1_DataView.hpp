#pragma once

#include <gui_generated/screen_module1_data_screen/Screen_Module1_DataViewBase.hpp>
#include <gui/screen_module1_data_screen/Screen_Module1_DataPresenter.hpp>

class Screen_Module1_DataView : public Screen_Module1_DataViewBase
{
public:
  Screen_Module1_DataView();
  virtual ~Screen_Module1_DataView() override {}
  virtual void setupScreen() override;
  
  // Declaring callback handler
  void TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& e);
  
  void UpdateGuiPacketData(UartPacket& uartPacket);
  void UpdateCpuUsage(uint8_t value);
  
  // Show all text areas again
  void ShowAll() override;
  
protected:
  // Declaring callback type of TextAreaWithOneWildcard and clickEvent
  Callback<Screen_Module1_DataView, const TextAreaWithOneWildcard&, const ClickEvent&> TextAreaClickedCallback;
};