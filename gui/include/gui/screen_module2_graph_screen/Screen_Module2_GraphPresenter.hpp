#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module2_GraphView;

class Screen_Module2_GraphPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module2_GraphPresenter(Screen_Module2_GraphView& v);

    virtual void NotifyNewUartRxParsedPacket(UartPacket& uartPacket);
    virtual void NotifyNewGraphRange(UartPacket& uartPacket);
      
    void NotifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module2_GraphPresenter() override {};

private:
    Screen_Module2_GraphPresenter();

    Screen_Module2_GraphView& view;
};