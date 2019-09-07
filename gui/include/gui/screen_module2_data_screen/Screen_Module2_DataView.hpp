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
    virtual void tearDownScreen();
    
    void updateGUIFrameData(UARTFrameStruct_t & s_UARTFrame);
    
protected:
};

#endif // SCREEN_MODULE2_DATA_VIEW_HPP
