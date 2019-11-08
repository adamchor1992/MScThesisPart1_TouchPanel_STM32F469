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

    virtual void notifyNewUART_RX_ParsedFrame(UARTFrameStruct_t & s_UARTFrame);
    virtual void notifyNewGraphRange(UARTFrameStruct_t & s_UARTFrame);
      
    void notifyNewCpuUsageValue(uint8_t value);
    
    virtual void activate();
    virtual void deactivate();

    virtual ~Screen_Module1_GraphPresenter() {};

private:
    Screen_Module1_GraphPresenter();

    Screen_Module1_GraphView& view;
};

#endif // SCREEN_MODULE1_GRAPH_PRESENTER_HPP
