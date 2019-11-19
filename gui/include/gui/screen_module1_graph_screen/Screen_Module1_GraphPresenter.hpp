#ifndef SCREEN_MODULE1_GRAPH_PRESENTER_HPP
#define SCREEN_MODULE1_GRAPH_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen_Module1_GraphView;

class Screen_Module1_GraphPresenter : public Presenter, public ModelListener
{
public:
    Screen_Module1_GraphPresenter(Screen_Module1_GraphView& v);

    virtual void notifyNewUartRxParsedPacket(UartPacket & uartPacket);
    virtual void notifyNewGraphRange(UartPacket & uartPacket);
      
    void notifyNewCpuUsageValue(uint8_t value);

    virtual ~Screen_Module1_GraphPresenter() {};

private:
    Screen_Module1_GraphPresenter();

    Screen_Module1_GraphView& view;
};

#endif
