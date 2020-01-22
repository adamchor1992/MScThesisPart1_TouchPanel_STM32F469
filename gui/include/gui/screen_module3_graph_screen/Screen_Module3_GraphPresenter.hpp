#ifndef SCREEN_MODULE3_GRAPH_PRESENTER_HPP
#define SCREEN_MODULE3_GRAPH_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module3_GraphView;

class Screen_Module3_GraphPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module3_GraphPresenter(Screen_Module3_GraphView& v);

    virtual void notifyNewUartRxParsedPacket(UartPacket& uartPacket);
    virtual void notifyNewGraphRange(UartPacket& uartPacket);
      
    void notifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module3_GraphPresenter() {};

private:
    Screen_Module3_GraphPresenter();

    Screen_Module3_GraphView& view;
};

#endif
