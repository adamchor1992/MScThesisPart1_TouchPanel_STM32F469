#ifndef SCREEN_MODULE1_GRAPH_VIEW_HPP
#define SCREEN_MODULE1_GRAPH_VIEW_HPP

#include <gui_generated/screen_module1_graph_screen/Screen_Module1_GraphViewBase.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphPresenter.hpp>

class Screen_Module1_GraphView : public Screen_Module1_GraphViewBase
{
public:
    Screen_Module1_GraphView();
    virtual ~Screen_Module1_GraphView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_MODULE1_GRAPH_VIEW_HPP
