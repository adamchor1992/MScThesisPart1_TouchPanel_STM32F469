#ifndef SCREEN_MODULE2_GRAPH_VIEW_HPP
#define SCREEN_MODULE2_GRAPH_VIEW_HPP

#include <gui_generated/screen_module2_graph_screen/Screen_Module2_GraphViewBase.hpp>
#include <gui/screen_module2_graph_screen/Screen_Module2_GraphPresenter.hpp>

class Screen_Module2_GraphView : public Screen_Module2_GraphViewBase
{
public:
    Screen_Module2_GraphView();
    virtual ~Screen_Module2_GraphView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_MODULE2_GRAPH_VIEW_HPP
