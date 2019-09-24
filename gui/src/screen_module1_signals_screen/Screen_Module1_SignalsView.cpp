#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsView.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>

Screen_Module1_SignalsView::Screen_Module1_SignalsView()
{

}

void Screen_Module1_SignalsView::setupScreen()
{
    Screen_Module1_SignalsViewBase::setupScreen();
}

void Screen_Module1_SignalsView::tearDownScreen()
{
    Screen_Module1_SignalsViewBase::tearDownScreen();
}

void Screen_Module1_SignalsView::setVoltageGraphVisible()
{
	if (toggleButton_Voltage.getState())
	{
		Screen_Module1_GraphView::voltageGraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::voltageGraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::setCurrentGraphVisible()
{
	if (toggleButton_Current.getState())
	{
		Screen_Module1_GraphView::currentGraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::currentGraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::setFrequencyGraphVisible()
{
	if (toggleButton_Frequency.getState())
	{
		Screen_Module1_GraphView::frequencyGraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::frequencyGraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::setPowerGraphVisible()
{
	if (toggleButton_Power.getState())
	{
		Screen_Module1_GraphView::powerGraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::powerGraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::updateTimeRange(int value)
{
	Unicode::snprintf(textArea_TimeRangeBuffer, 6, "%d", value);
	textArea_TimeRange.invalidate();
}

void Screen_Module1_SignalsView::updateY_AxisMin(int value)
{
	float float_value = float(value) * 0.1;
	Unicode::snprintfFloat(textArea_Y_AxisMinBuffer, 6, "%.1f", float_value);
	textArea_Y_AxisMin.invalidate();
}

void Screen_Module1_SignalsView::updateY_AxisMax(int value)
{
	float float_value = float(value) * 0.1;
	Unicode::snprintfFloat(textArea_Y_AxisMaxBuffer, 6, "%.1f", float_value);
	textArea_Y_AxisMax.invalidate();
}
