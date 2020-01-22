#ifndef SCREEN_MODULE3_DATA_VIEW_HPP
#define SCREEN_MODULE3_DATA_VIEW_HPP

#include <gui_generated/screen_module3_data_screen/Screen_Module3_DataViewBase.hpp>
#include <gui/screen_module3_data_screen/Screen_Module3_DataPresenter.hpp>

class Screen_Module3_DataView : public Screen_Module3_DataViewBase
{
public:
  Screen_Module3_DataView();
  virtual ~Screen_Module3_DataView() {}
  virtual void setupScreen();
  
  // Declaring callback handler
  void TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& e);
  
  void updateGuiPacketData(UartPacket& uartPacket);
  void updateCpuUsage(uint8_t value);
  
  // Show all text areas again
  void showAll();
  
protected:
  // Declaring callback type of TextAreaWithOneWildcard and clickEvent
  Callback<Screen_Module3_DataView, const TextAreaWithOneWildcard&, const ClickEvent&> TextAreaClickedCallback;
};

#endif
