#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_DataView;

class Screen_Module2_DataPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module2_DataPresenter(Screen_Module2_DataView& v);

    virtual void NotifyNewUartRxParsedPacket(UartPacket& uartPacket); 
    void NotifyNewCpuUsageValue(uint8_t value);
    
    virtual ~Screen_Module2_DataPresenter() override {};

private:
    Screen_Module2_DataPresenter();

    Screen_Module2_DataView& view;
};