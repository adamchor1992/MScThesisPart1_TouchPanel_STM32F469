#include <gui/screen_module1_signals_screen/Screen_Module1_SignalsView.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <gui/model/Model.hpp>

#define SINE_PERIOD_DEGREES 360

Screen_Module1_SignalsView::Screen_Module1_SignalsView()
{
#ifndef SIMULATOR     
	uint16_t parameterStringDisplay[CUSTOM_PARAMETER_NAME_COUNT][PAYLOAD_SIZE] = { 0 };

	for (int i = 0; i < CUSTOM_PARAMETER_NAME_COUNT; i++)
	{
		for (int character = 0; character < PAYLOAD_SIZE; character++)
		{
			parameterStringDisplay[i][character] = Model::m_InitParametersModule1[i + CUSTOM_PARAMETER_NAME_OFFSET][character];
		}
	}

	Unicode::snprintf(textArea_Parameter1NameBuffer, TEXTAREA_PARAMETER1NAME_SIZE, "%s", parameterStringDisplay[0]);
	textArea_Parameter1Name.invalidate();

	Unicode::snprintf(textArea_Parameter2NameBuffer, TEXTAREA_PARAMETER2NAME_SIZE, "%s", parameterStringDisplay[1]);
	textArea_Parameter2Name.invalidate();

	Unicode::snprintf(textArea_Parameter3NameBuffer, TEXTAREA_PARAMETER3NAME_SIZE, "%s", parameterStringDisplay[2]);
	textArea_Parameter3Name.invalidate();

	Unicode::snprintf(textArea_Parameter4NameBuffer, TEXTAREA_PARAMETER4NAME_SIZE, "%s", parameterStringDisplay[3]);
	textArea_Parameter4Name.invalidate();
#endif

	int bottom = Screen_Module1_GraphView::m_GraphRangeBottom; //make bottom value positive for sake of calculations
	
	if (bottom < 0)
	{
		bottom = bottom * (-1); //make bottom value positive for sake of calculations
		setSignMin(Sign::NEGATIVE);
	}
	else
	{
		setSignMin(Sign::POSITIVE);
	}
	
	int top = Screen_Module1_GraphView::m_GraphRangeTop;

	if (top < 0)
	{
		top = top * (-1); //make top value positive for sake of calculations
		setSignMax(Sign::NEGATIVE);
	}
	else
	{
		setSignMax(Sign::POSITIVE);
	}

	setMinScrollWheelValues(bottom);
	setMaxScrollWheelValues(top);

	initializeScrollWheels();
}

void Screen_Module1_SignalsView::setupScreen()
{
#ifndef SIMULATOR
	NVIC_DisableIRQ(USART6_IRQn);
#endif

	/*Initialize buttons' states*/
	toggleButton_Parameter1.forceState(Screen_Module1_GraphView::m_Parameter1GraphEnabled);
	toggleButton_Parameter2.forceState(Screen_Module1_GraphView::m_Parameter2GraphEnabled);
	toggleButton_Parameter3.forceState(Screen_Module1_GraphView::m_Parameter3GraphEnabled);
	toggleButton_Parameter4.forceState(Screen_Module1_GraphView::m_Parameter4GraphEnabled);
	toggleButton_Auto_Y_Range.forceState(Screen_Module1_GraphView::m_AutoRangeEnabled);

	/*Initialize sliders' values */
	slider_TimeRange.setValue(Screen_Module1_GraphView::m_GraphRangeRight / SINE_PERIOD_DEGREES);
	Unicode::snprintf(textArea_TimeRangeBuffer, 6, "%d", Screen_Module1_GraphView::m_GraphRangeRight);
	textArea_TimeRange.invalidate();
}

void Screen_Module1_SignalsView::tearDownScreen()
{
#ifndef SIMULATOR
	/*Restart UART RX*/
	extern uint8_t UART_ReceivedFrame[FRAME_SIZE];

	HAL_UART_DeInit(Model::m_pHuart6);
	HAL_UART_Init(Model::m_pHuart6);

	NVIC_EnableIRQ(USART6_IRQn);

	HAL_UART_Receive_IT(Model::m_pHuart6, UART_ReceivedFrame, FRAME_SIZE);
#endif
}

void Screen_Module1_SignalsView::setRanges()
{
	int minRangeValues[PAYLOAD_SIZE] = { 0 };
	int maxRangeValues[PAYLOAD_SIZE] = { 0 };

	getScrollWheelMinValues(minRangeValues);
	getScrollWheelMaxValues(maxRangeValues);

	translateScrollWheelValues(minRangeValues);
	translateScrollWheelValues(maxRangeValues);

	int minRangeValue = processScrollWheelValues(minRangeValues);
	int maxRangeValue = processScrollWheelValues(maxRangeValues);

	if (getSignMin() == Sign::NEGATIVE)
	{
		minRangeValue = minRangeValue * (-1);
	}

	if (getSignMax() == Sign::NEGATIVE)
	{
		maxRangeValue = maxRangeValue * (-1);
	}

	if (minRangeValue >= maxRangeValue)
	{
		return;
	}
	else
	{
		Screen_Module1_GraphView::setGraphRanges(minRangeValue, maxRangeValue, slider_TimeRange.getValue() * SINE_PERIOD_DEGREES);
	}
}

void Screen_Module1_SignalsView::initializeScrollWheels()
{
	scrollWheel_MinDigit1.initialize();
	scrollWheel_MinDigit2.initialize();
	scrollWheel_MinDigit3.initialize();
	scrollWheel_MinDigit4.initialize();
	scrollWheel_MinDigit5.initialize();
	scrollWheel_MinDigit6.initialize();
	scrollWheel_MinDigit7.initialize();
	scrollWheel_MinDigit8.initialize();
	scrollWheel_MinDigit9.initialize();
	scrollWheel_MinDigit10.initialize();

	scrollWheel_MaxDigit1.initialize();
	scrollWheel_MaxDigit2.initialize();
	scrollWheel_MaxDigit3.initialize();
	scrollWheel_MaxDigit4.initialize();
	scrollWheel_MaxDigit5.initialize();
	scrollWheel_MaxDigit6.initialize();
	scrollWheel_MaxDigit7.initialize();
	scrollWheel_MaxDigit8.initialize();
	scrollWheel_MaxDigit9.initialize();
	scrollWheel_MaxDigit10.initialize();
}

void Screen_Module1_SignalsView::setMinScrollWheelValues(int bottom)
{
	int rest = 0;

	rest = bottom % 10;
	scrollWheel_MinDigit1.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit2.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit3.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit4.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit5.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit6.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit7.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit8.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit9.animateToItem(rest);
	bottom = bottom / 10;

	rest = bottom % 10;
	scrollWheel_MinDigit10.animateToItem(rest);
}

void Screen_Module1_SignalsView::setMaxScrollWheelValues(int top)
{
	int rest = 0;

	rest = top % 10;
	scrollWheel_MaxDigit1.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit2.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit3.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit4.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit5.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit6.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit7.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit8.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit9.animateToItem(rest);
	top = top / 10;

	rest = top % 10;
	scrollWheel_MaxDigit10.animateToItem(rest);
}

void Screen_Module1_SignalsView::getScrollWheelMinValues(int values[])
{
	values[9] = scrollWheel_MinDigit1.getSelectedItem();
	values[8] = scrollWheel_MinDigit2.getSelectedItem();
	values[7] = scrollWheel_MinDigit3.getSelectedItem();
	values[6] = scrollWheel_MinDigit4.getSelectedItem();
	values[5] = scrollWheel_MinDigit5.getSelectedItem();
	values[4] = scrollWheel_MinDigit6.getSelectedItem();
	values[3] = scrollWheel_MinDigit7.getSelectedItem();
	values[2] = scrollWheel_MinDigit8.getSelectedItem();
	values[1] = scrollWheel_MinDigit9.getSelectedItem();
	values[0] = scrollWheel_MinDigit10.getSelectedItem();
}

void Screen_Module1_SignalsView::getScrollWheelMaxValues(int values[])
{
	values[9] = scrollWheel_MaxDigit1.getSelectedItem();
	values[8] = scrollWheel_MaxDigit2.getSelectedItem();
	values[7] = scrollWheel_MaxDigit3.getSelectedItem();
	values[6] = scrollWheel_MaxDigit4.getSelectedItem();
	values[5] = scrollWheel_MaxDigit5.getSelectedItem();
	values[4] = scrollWheel_MaxDigit6.getSelectedItem();
	values[3] = scrollWheel_MaxDigit7.getSelectedItem();
	values[2] = scrollWheel_MaxDigit8.getSelectedItem();
	values[1] = scrollWheel_MaxDigit9.getSelectedItem();
	values[0] = scrollWheel_MaxDigit10.getSelectedItem();
}

void Screen_Module1_SignalsView::translateScrollWheelValues(int values[])
{
	for (int i = 0; i < PAYLOAD_SIZE; i++)
	{
		switch (values[i])
		{
		case 0:
			values[i] = '0';
			break;
		case 1:
			values[i] = '1';
			break;
		case 2:
			values[i] = '2';
			break;
		case 3:
			values[i] = '3';
			break;
		case 4:
			values[i] = '4';
			break;
		case 5:
			values[i] = '5';
			break;
		case 6:
			values[i] = '6';
			break;
		case 7:
			values[i] = '7';
			break;
		case 8:
			values[i] = '8';
			break;
		case 9:
			values[i] = '9';
			break;
		}
	}
}

int Screen_Module1_SignalsView::processScrollWheelValues(const int values[])
{
	char asciiScrollWheelValues[PAYLOAD_SIZE + 1];

	for (int i = 0; i < PAYLOAD_SIZE; i++)
	{
		asciiScrollWheelValues[i] = values[i];
	}

	asciiScrollWheelValues[PAYLOAD_SIZE] = '\0';

	return atoi(asciiScrollWheelValues);
}

void Screen_Module1_SignalsView::setParameter1GraphVisible()
{
	if (toggleButton_Parameter1.getState() == true)
	{
		Screen_Module1_GraphView::m_Parameter1GraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::m_Parameter1GraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::setParameter2GraphVisible()
{
	if (toggleButton_Parameter2.getState() == true)
	{
		Screen_Module1_GraphView::m_Parameter2GraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::m_Parameter2GraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::setParameter3GraphVisible()
{
	if (toggleButton_Parameter3.getState() == true)
	{
		Screen_Module1_GraphView::m_Parameter3GraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::m_Parameter3GraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::setParameter4GraphVisible()
{
	if (toggleButton_Parameter4.getState() == true)
	{
		Screen_Module1_GraphView::m_Parameter4GraphEnabled = true;
	}
	else
	{
		Screen_Module1_GraphView::m_Parameter4GraphEnabled = false;
	}
}

void Screen_Module1_SignalsView::updateTimeRange(int value)
{
	Unicode::snprintf(textArea_TimeRangeBuffer, 6, "%d", value * SINE_PERIOD_DEGREES);
	textArea_TimeRange.invalidate();
}

void Screen_Module1_SignalsView::pressedAutoRangeToggleButton()
{
	if (toggleButton_Auto_Y_Range.getState() == true)
	{
		Screen_Module1_GraphView::m_AutoRangeEnabled = true;

		textArea_Y_AxisMin.setVisible(false);
		textArea_Y_AxisMax.setVisible(false);

		textArea_Y_AxisMin.invalidate();
		textArea_Y_AxisMax.invalidate();
	}
	else
	{
		Screen_Module1_GraphView::m_AutoRangeEnabled = false;

		textArea_Y_AxisMin.setVisible(true);
		textArea_Y_AxisMax.setVisible(true);

		textArea_Y_AxisMin.invalidate();
		textArea_Y_AxisMax.invalidate();
	}
}

void Screen_Module1_SignalsView::setSignMin(Sign sign)
{
	if (sign == Sign::POSITIVE)
	{
		toggleButton_SignMin.forceState(true);
	}
	else if(sign == Sign::NEGATIVE)
	{
		toggleButton_SignMin.forceState(false);
	}
}

void Screen_Module1_SignalsView::setSignMax(Sign sign)
{
	if (sign == Sign::POSITIVE)
	{
		toggleButton_SignMax.forceState(true);
	}
	else if (sign == Sign::NEGATIVE)
	{
		toggleButton_SignMax.forceState(false);
	}
}

Screen_Module1_SignalsView::Sign Screen_Module1_SignalsView::getSignMin()
{
	if (toggleButton_SignMin.getState() == true)
	{
		return Sign::POSITIVE;
	}
	else
	{
		return Sign::NEGATIVE;
	}
}

Screen_Module1_SignalsView::Sign Screen_Module1_SignalsView::getSignMax()
{
	if (toggleButton_SignMax.getState() == true)
	{
		return Sign::POSITIVE;
	}
	else
	{
		return Sign::NEGATIVE;
	}
}

void Screen_Module1_SignalsView::updateCpuUsage(uint8_t value)
{
	Unicode::snprintf(textArea_CPU_UsageBuffer, 4, "%d", value);
	textArea_CPU_Usage.invalidate();
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit1UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit2UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit3UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit4UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit5UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit6UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit7UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit8UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit9UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MinDigit10UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit1UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit2UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit3UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit4UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit5UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit6UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit7UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit8UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit9UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}

void Screen_Module1_SignalsView::scrollWheel_MaxDigit10UpdateItem(DigitTemplate & item, int16_t itemIndex)
{
	item.setDigitWithoutComma(itemIndex);
}