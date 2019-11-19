#ifndef SCREEN_MODULE2_GRAPH_VIEW_HPP
#define SCREEN_MODULE2_GRAPH_VIEW_HPP

#include <mvp/View.hpp>
#include <gui_generated/screen_module2_graph_screen/Screen_Module2_GraphViewBase.hpp>
#include <gui/screen_module2_graph_screen/Screen_Module2_GraphPresenter.hpp>
#include <gui/common/Graph.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

#include <gui/screen_module2_signals_screen/Screen_Module2_SignalsView.hpp>

using namespace touchgfx;

class Screen_Module2_GraphView : public Screen_Module2_GraphViewBase
{
	friend class Screen_Module2_SignalsView;

public:
	Screen_Module2_GraphView();
	virtual ~Screen_Module2_GraphView() {}
	virtual void setupScreen();

	virtual void handleTickEvent();
	virtual void addNewValueToGraphFromUart(UartPacket & uartPacket);
	void setNewGraphRange(UartPacket & uartPacket);

	uint8_t activeSignalsCount();
	void updateCpuUsage(uint8_t value);

	static void setGraphRanges(int bottom, int top, int right);

	void resetGraph();

	static int getGraphRangeBottom() { return m_GraphRangeBottom; }
	static int getGraphRangeTop() { return m_GraphRangeTop; }

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

	static int m_GraphRangeBottom;
	static int m_GraphRangeTop;
	static int m_GraphRangeRight;
};

#endif