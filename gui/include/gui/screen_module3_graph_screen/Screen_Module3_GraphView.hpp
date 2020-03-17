#pragma once

#include <mvp/View.hpp>
#include <gui_generated/screen_module3_graph_screen/Screen_Module3_GraphViewBase.hpp>
#include <gui/screen_module3_graph_screen/Screen_Module3_GraphPresenter.hpp>
#include <gui/common/Graph.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

#include <gui/screen_module3_signals_screen/Screen_Module3_SignalsView.hpp>

using namespace touchgfx;

class Screen_Module3_GraphView : public Screen_Module3_GraphViewBase
{
  friend class Screen_Module3_SignalsView;

public:
  Screen_Module3_GraphView();
  virtual ~Screen_Module3_GraphView() override {}
  virtual void setupScreen() override;
  virtual void handleTickEvent() override;
  
  virtual void AddNewValueToGraphFromUart(UartPacket& uartPacket);
  void SetNewGraphRange(UartPacket& uartPacket);
  
  uint8_t ActiveSignalsCount();
  void UpdateCpuUsage(uint8_t value);
  
  void SetGraphRangeTextAreas(long long int bottom, long long int top, int right);
  static void SetGraphRanges(long long int bottom, long long int top, int right);

  void ResetGraph();
  
  static long long int GetGraphRangeBottom() { return m_GraphRangeBottom; }
  static long long int GetGraphRangeTop() { return m_GraphRangeTop; }
  
private:
  int m_TimeBase;
  
  Image m_Background;
  Graph m_GraphYellow;
  Graph m_GraphRed;
  Graph m_GraphBlue;
  Graph m_GraphGreen;
  Graph* m_Graphs[4];
      
  int m_PreviousYellow_X;
  int m_PreviousRed_X;
  int m_PreviousBlue_X;
  int m_PreviousGreen_X;
  
  static bool m_Parameter1GraphEnabled;
  static bool m_Parameter2GraphEnabled;
  static bool m_Parameter3GraphEnabled;
  static bool m_Parameter4GraphEnabled;

  static bool m_AutoRangeEnabled;
  
  static long long int m_GraphRangeBottom;
  static long long int m_GraphRangeTop;
  static int m_GraphRangeRight;
};