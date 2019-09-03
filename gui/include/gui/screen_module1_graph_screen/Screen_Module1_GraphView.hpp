#ifndef SCREEN_MODULE1_GRAPH_VIEW_HPP
#define SCREEN_MODULE1_GRAPH_VIEW_HPP

#include <mvp/View.hpp>
#include <gui_generated/screen_module1_graph_screen/Screen_Module1_GraphViewBase.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphPresenter.hpp>
#include <gui/common/Graph.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

using namespace touchgfx;

class Screen_Module1_GraphView : public Screen_Module1_GraphViewBase
{
public:
  Screen_Module1_GraphView();
  virtual ~Screen_Module1_GraphView() {}
  virtual void setupScreen();
  virtual void tearDownScreen();
  
  virtual void handleTickEvent();
  virtual void addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame);
  void updateCpuUsage(uint8_t value);
  
private:
  int tickCounter;
  uint8_t length_int;
  int16_t value_int;
  bool isNegative;
  
  Image background;
  Graph graph;
};

#endif // SCREEN_MODULE1_GRAPH_VIEW_HPP