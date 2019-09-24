#ifndef SCREEN_MODULE1_GRAPH_VIEW_HPP
#define SCREEN_MODULE1_GRAPH_VIEW_HPP

#include <mvp/View.hpp>
#include <gui_generated/screen_module1_graph_screen/Screen_Module1_GraphViewBase.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphPresenter.hpp>
#include <gui/common/Graph.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsView.hpp>

using namespace touchgfx;

class Screen_Module1_GraphView : public Screen_Module1_GraphViewBase
{
	friend class Screen_Module1_SignalsView;
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
  int value;

  Image background;
  Graph graphYellow;
  Graph graphRed;
  Graph graphBlue;
  Graph graphGreen;

  static bool voltageGraphEnabled;
  static bool currentGraphEnabled;
  static bool frequencyGraphEnabled;
  static bool powerGraphEnabled;
};

#endif // SCREEN_MODULE1_GRAPH_VIEW_HPP