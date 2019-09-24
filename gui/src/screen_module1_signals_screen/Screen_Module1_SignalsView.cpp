#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsView.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>

Screen_Module1_SignalsView::Screen_Module1_SignalsView()
{
  
}

void Screen_Module1_SignalsView::setupScreen()
{
  /*Initialize buttons' states*/
  toggleButton_Voltage.forceState(Screen_Module1_GraphView::voltageGraphEnabled);
  toggleButton_Current.forceState(Screen_Module1_GraphView::currentGraphEnabled);
  toggleButton_Frequency.forceState(Screen_Module1_GraphView::frequencyGraphEnabled);
  toggleButton_Power.forceState(Screen_Module1_GraphView::powerGraphEnabled);
  toggleButton_Auto_Y_Range.forceState(Screen_Module1_GraphView::autoRangeEnabled);
  
  /*Initialize sliders' values */
  slider_TimeRange.setValue(Screen_Module1_GraphView::m_graphRangeRight);
  Unicode::snprintf(textArea_TimeRangeBuffer,6,"%d", Screen_Module1_GraphView::m_graphRangeRight);
  textArea_TimeRange.invalidate();
  
  slider_Y_AxisMin.setValue(Screen_Module1_GraphView::m_graphRangeBottom);
  Unicode::snprintf(textArea_Y_AxisMinBuffer,6,"%d", Screen_Module1_GraphView::m_graphRangeBottom);
  textArea_Y_AxisMin.invalidate();
  
  slider_Y_AxisMax.setValue(Screen_Module1_GraphView::m_graphRangeTop);
  Unicode::snprintf(textArea_Y_AxisMaxBuffer,6,"%d", Screen_Module1_GraphView::m_graphRangeTop);
  textArea_Y_AxisMax.invalidate();
  
  Screen_Module1_SignalsViewBase::setupScreen();
}

void Screen_Module1_SignalsView::tearDownScreen()
{
  Screen_Module1_GraphView::setGraphRanges(slider_Y_AxisMin.getValue(), slider_Y_AxisMax.getValue(), slider_TimeRange.getValue());
  
  Screen_Module1_SignalsViewBase::tearDownScreen();
}

void Screen_Module1_SignalsView::setVoltageGraphVisible()
{
  if (toggleButton_Voltage.getState() == true)
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
  if (toggleButton_Current.getState() == true)
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
  if (toggleButton_Frequency.getState() == true)
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
  if (toggleButton_Power.getState() == true)
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
  /*Negate value read from slider*/
  value = value * (-1);
  
  Unicode::snprintf(textArea_Y_AxisMinBuffer, 6, "%d", value);
  textArea_Y_AxisMin.invalidate();
}

void Screen_Module1_SignalsView::updateY_AxisMax(int value)
{
  Unicode::snprintf(textArea_Y_AxisMaxBuffer, 6, "%d", value);
  textArea_Y_AxisMax.invalidate();
}

void Screen_Module1_SignalsView::pressedAutoRangeToggleButton()
{
  if(toggleButton_Auto_Y_Range.getState() == true)
  {
    Screen_Module1_GraphView::autoRangeEnabled = true; 
    
    textArea_Y_AxisMin.setVisible(false);
    textArea_Y_AxisMax.setVisible(false);
    slider_Y_AxisMin.setVisible(false);
    slider_Y_AxisMax.setVisible(false);
    
    textArea_Y_AxisMin.invalidate();
    textArea_Y_AxisMax.invalidate();
    slider_Y_AxisMin.invalidate();
    slider_Y_AxisMax.invalidate();
  }
  else
  {
    Screen_Module1_GraphView::autoRangeEnabled = false;
    
    textArea_Y_AxisMin.setVisible(true);
    textArea_Y_AxisMax.setVisible(true);
    slider_Y_AxisMin.setVisible(true);
    slider_Y_AxisMax.setVisible(true);
    
    textArea_Y_AxisMin.invalidate();
    textArea_Y_AxisMax.invalidate();
    slider_Y_AxisMin.invalidate();
    slider_Y_AxisMax.invalidate();
  }
}
