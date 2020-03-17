#pragma once

#include <gui_generated/screen_module3_data_screen/Screen_Module3_DataViewBase.hpp>
#include <gui/screen_module3_data_screen/Screen_Module3_DataPresenter.hpp>

class Screen_Module3_DataView : public Screen_Module3_DataViewBase
{
public:
  Screen_Module3_DataView();
  virtual ~Screen_Module3_DataView() override {}
  virtual void setupScreen() override;
  
  // Declaring callback handler
  void TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& e);
  
  void UpdateGuiPacketData(UartPacket& uartPacket);
  void UpdateCpuUsage(uint8_t value);
  
  // Show all text areas again
  void ShowAll() override;
  
protected:
  // Declaring callback type of TextAreaWithOneWildcard and clickEvent
  Callback<Screen_Module3_DataView, const TextAreaWithOneWildcard&, const ClickEvent&> TextAreaClickedCallback;
};