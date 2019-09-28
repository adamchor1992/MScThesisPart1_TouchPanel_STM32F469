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
  uint8_t activeSignalsCount();
  void updateCpuUsage(uint8_t value);
  
  static void setGraphRanges(int bottom, int top, int right);
  
private:
  int m_tickCounter;
  int m_value;
  
  Image m_background;
  Graph m_graphYellow;
  Graph m_graphRed;
  Graph m_graphBlue;
  Graph m_graphGreen;
  Graph* m_graphs[4];
  
  bool m_graphRangeBottomChangedFlag;
  bool m_graphRangeTopChangedFlag;
    
  int m_PreviousYellow_X;
  int m_PreviousRed_X;
  int m_PreviousBlue_X;
  int m_PreviousGreen_X;
  
  static bool m_parameter1GraphEnabled;
  static bool m_parameter2GraphEnabled;
  static bool m_parameter3GraphEnabled;
  static bool m_parameter4GraphEnabled;
  static bool m_autoRangeEnabled;
  
  static int m_graphRangeBottom;
  static int m_graphRangeTop;
  static int m_graphRangeRight;
};

#endif // SCREEN_MODULE1_GRAPH_VIEW_HPP