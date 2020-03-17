#pragma once

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_GraphView;

class Screen_Module3_GraphPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module3_GraphPresenter(Screen_Module3_GraphView& v);

    virtual void NotifyNewUartRxParsedPacket(UartPacket& uartPacket);
    virtual void NotifyNewGraphRange(UartPacket& uartPacket);
      
    void NotifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module3_GraphPresenter() override {};

private:
    Screen_Module3_GraphPresenter();

    Screen_Module3_GraphView& view;
};