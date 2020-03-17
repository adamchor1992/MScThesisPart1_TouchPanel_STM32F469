#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_DataView;

class Screen_Module3_DataPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module3_DataPresenter(Screen_Module3_DataView& v);

    virtual void NotifyNewUartRxParsedPacket(UartPacket& uartPacket); 
    void NotifyNewCpuUsageValue(uint8_t value);
    
    virtual ~Screen_Module3_DataPresenter() override {};

private:
    Screen_Module3_DataPresenter();

    Screen_Module3_DataView& view;
};