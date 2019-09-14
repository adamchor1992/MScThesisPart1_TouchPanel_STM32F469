#ifndef SCREEN_MODULE1_DATA_VIEW_HPP
#define SCREEN_MODULE1_DATA_VIEW_HPP

#include <gui_generated/screen_module1_data_screen/Screen_Module1_DataViewBase.hpp>
#include <gui/screen_module1_data_screen/Screen_Module1_DataPresenter.hpp>

class Screen_Module1_DataView : public Screen_Module1_DataViewBase
{
public:
  Screen_Module1_DataView();
  virtual ~Screen_Module1_DataView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  // Declaring callback handler for HiddenBox
  void TextAreaClickHandler(const TextAreaWithOneWildcard& b, const ClickEvent& e);
  
  void updateGUIFrameData(UARTFrameStruct_t & s_UARTFrame);
  void updateCpuUsage(uint8_t value);
  
  // Show all text areas again
  void showAll();
  
protected:
  // Declaring callback type of TextAreaWithOneWildcard and clickEvent
  Callback<Screen_Module1_DataView, const TextAreaWithOneWildcard&, const ClickEvent&> TextAreaClickedCallback;
};

#endif // SCREEN_MODULE1_DATA_VIEW_HPP
