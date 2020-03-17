#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1_DataView;

class Screen_Module1_DataPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen_Module1_DataPresenter(Screen_Module1_DataView& v);
    
    virtual void NotifyNewUartRxParsedPacket(UartPacket& uartPacket); 
    void NotifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module1_DataPresenter() override {};

private:
    Screen_Module1_DataPresenter();

    Screen_Module1_DataView& view;
};