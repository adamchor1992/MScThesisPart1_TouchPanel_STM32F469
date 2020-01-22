#ifndef SCREEN_MODULE2_DATA_VIEW_HPP
#define SCREEN_MODULE2_DATA_VIEW_HPP

#include <gui_generated/screen_module2_data_screen/Screen_Module2_DataViewBase.hpp>
#include <gui/screen_module2_data_screen/Screen_Module2_DataPresenter.hpp>

class Screen_Module2_DataView : public Screen_Module2_DataViewBase
{
public:
  Screen_Module2_DataView();
  virtual ~Screen_Module2_DataView() {}
  virtual void setupScreen();
  
  // Declaring callback handler
  void TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& e);
  
  void updateGuiPacketData(UartPacket& uartPacket);
  void updateCpuUsage(uint8_t value);
  
  // Show all text areas again
  void showAll();
  
protected:
  // Declaring callback type of TextAreaWithOneWildcard and clickEvent
  Callback<Screen_Module2_DataView, const TextAreaWithOneWildcard&, const ClickEvent&> TextAreaClickedCallback;
};

#endif
