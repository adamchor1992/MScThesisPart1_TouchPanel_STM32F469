#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/screen_module1_graph_screen/Screen_Module1_GraphView.hpp>
#include <string>
#include <cmath>

#ifndef SIMULATOR
#include "stm32469i_discovery.h" //for led driving
#include <stdlib.h>
void DebugPrint(const char* ch);
#endif

#ifdef SIMULATOR
#include <iostream>
using namespace std;
#endif

//using System.Diagnostics;

#define INITIAL_GRAPH_RANGE_BOTTOM -1000
#define INITIAL_GRAPH_RANGE_TOP 1000
#define INITIAL_GRAPH_RANGE_LEFT 0
#define INITIAL_GRAPH_RANGE_RIGHT 720

#define GRAPHS_COUNT 4
#define SCALE_FACTOR 1000

bool Screen_Module1_GraphView::m_parameter1GraphEnabled = true;
bool Screen_Module1_GraphView::m_parameter2GraphEnabled = true;
bool Screen_Module1_GraphView::m_parameter3GraphEnabled = true;
bool Screen_Module1_GraphView::m_parameter4GraphEnabled = true;
bool Screen_Module1_GraphView::m_autoRangeEnabled = false;

int Screen_Module1_GraphView::m_graphRangeBottom = INITIAL_GRAPH_RANGE_BOTTOM;
int Screen_Module1_GraphView::m_graphRangeTop = INITIAL_GRAPH_RANGE_TOP;
int Screen_Module1_GraphView::m_graphRangeRight = INITIAL_GRAPH_RANGE_RIGHT;

void Screen_Module1_GraphView::setGraphRanges(int bottom, int top, int right)
{
	m_graphRangeBottom = bottom;
	m_graphRangeTop = top;
	m_graphRangeRight = right;
}

Screen_Module1_GraphView::Screen_Module1_GraphView()
{
	m_graphRangeBottomChangedFlag = false;
	m_graphRangeTopChangedFlag = false;

	m_PreviousYellow_X = 0;
	m_PreviousRed_X = 0;
	m_PreviousBlue_X = 0;
	m_PreviousGreen_X = 0;

	m_tickCounter = 0;

	m_graphs[0] = &m_graphYellow;
	m_graphs[1] = &m_graphRed;
	m_graphs[2] = &m_graphBlue;
	m_graphs[3] = &m_graphGreen;
}

void Screen_Module1_GraphView::setupScreen()
{
	m_tickCounter = 0;

	// Set the outer dimensions and color of the graphs
	m_graphYellow.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), m_graphRangeBottom, m_graphRangeTop);
	m_graphRed.setup(745, 385, Color::getColorFrom24BitRGB(0xFF, 0x00, 0x00), m_graphRangeBottom, m_graphRangeTop);
	m_graphBlue.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0x00, 0xFF), m_graphRangeBottom, m_graphRangeTop);
	m_graphGreen.setup(745, 385, Color::getColorFrom24BitRGB(0x00, 0xFF, 0x00), m_graphRangeBottom, m_graphRangeTop);

	// Initialize graphs
	for (int i = 0; i < GRAPHS_COUNT; i++)
	{
		// Place graphs on the screen
		m_graphs[i]->setXY(55, 0);
		// Set the ranges for the x and y axis of the graphs
		m_graphs[i]->setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
		// Set line width of the graphs
		m_graphs[i]->setLineWidth(1);
	}

	/*Initialize graph ranges text areas */
	Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", m_graphRangeTop / SCALE_FACTOR);
	textArea_GraphRangeTop.invalidate();

	Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", m_graphRangeBottom / SCALE_FACTOR);
	textArea_GraphRangeBottom.invalidate();

	Unicode::snprintf(textArea_GraphRangeRightBuffer, 6, "%d", m_graphRangeRight);
	textArea_GraphRangeBottom.invalidate();

	add(m_graphYellow);
	add(m_graphRed);
	add(m_graphBlue);
	add(m_graphGreen);

	Screen_Module1_GraphViewBase::setupScreen();
}

void Screen_Module1_GraphView::tearDownScreen()
{
	Screen_Module1_GraphViewBase::tearDownScreen();
}

void Screen_Module1_GraphView::handleTickEvent()
{
	if (m_autoRangeEnabled == true)
	{
		for (int i = 0; i < GRAPHS_COUNT; i++)
		{
			/*Check if value is higher than any graph's top range*/
			if (m_value > m_graphs[i]->getRangeTop())
			{
				m_graphRangeTopChangedFlag = true;
				m_graphRangeTop = m_value;
			}
			/*Check if value is lower than graph bottom range*/
			else if (m_value < m_graphs[i]->getRangeBottom())
			{
				m_graphRangeBottomChangedFlag = true;
				m_graphRangeBottom = m_value;
			}
		}
	}

	if (m_autoRangeEnabled == true)
	{
		if (m_graphRangeBottomChangedFlag)
		{
			m_graphYellow.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
			m_graphRed.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
			m_graphBlue.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
			m_graphGreen.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);

			Unicode::snprintf(textArea_GraphRangeBottomBuffer, 6, "%d", m_graphRangeBottom / SCALE_FACTOR);
			textArea_GraphRangeBottom.invalidate();

			/*Reset flag*/
			m_graphRangeBottomChangedFlag = false;
		}

		if (m_graphRangeTopChangedFlag)
		{
			m_graphYellow.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
			m_graphRed.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
			m_graphBlue.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);
			m_graphGreen.setRange(INITIAL_GRAPH_RANGE_LEFT, m_graphRangeRight, m_graphRangeBottom, m_graphRangeTop);

			Unicode::snprintf(textArea_GraphRangeTopBuffer, 6, "%d", m_graphRangeTop / SCALE_FACTOR);
			textArea_GraphRangeTop.invalidate();

			/*Reset flag*/
			m_graphRangeTopChangedFlag = false;
		}
	}

#ifdef SIMULATOR
	static int value1 = INITIAL_GRAPH_RANGE_BOTTOM;
	static int value2 = INITIAL_GRAPH_RANGE_BOTTOM + 40;
	static int value3 = INITIAL_GRAPH_RANGE_BOTTOM + 80;
	static int value4 = INITIAL_GRAPH_RANGE_BOTTOM + 120;
	
	static bool rising = true;

	static int multiplier = 1;

	const static int increment = 10;

	if (rising)
	{
		value1 = value1 + increment;
	}
	else
	{
		value1 = value1 - increment;
	}

	if (value1 >= 1000)
	{
		rising = false;
	}
	else if(value1 <= -1000)
	{
		rising = true;
	}

	m_tickCounter += 1;

	//value1 = multiplier * sin(m_tickCounter * 3.14159/180) * 100.0;

	value2 = value2 + increment;
	value3 = value3 + increment;
	value4 = value4 + increment;

	if (m_tickCounter >= m_graphRangeRight)
	{
		m_graphYellow.clear();
		m_graphYellow.invalidate();

		m_graphRed.clear();
		m_graphRed.invalidate();

		m_graphBlue.clear();
		m_graphBlue.invalidate();

		m_graphGreen.clear();
		m_graphGreen.invalidate();

		m_PreviousYellow_X = 0;
		m_PreviousRed_X = 0;
		m_PreviousBlue_X = 0;
		m_PreviousGreen_X = 0;

		m_tickCounter = 0;
	}
	
	char text_buffer1[40] = { 0 }; //temporary buffer
	sprintf(text_buffer1, "Graph bottom range %d\n", m_graphRangeBottom); // convert
	OutputDebugString(text_buffer1); // print
	char text_buffer11[40] = { 0 }; //temporary buffer
	sprintf(text_buffer11, "Graph bottom range %d\n", m_graphYellow.getRangeBottom()); // convert
	OutputDebugString(text_buffer11); // print

	char text_buffer2[40] = { 0 }; //temporary buffer
	sprintf(text_buffer2, "Graph top range %d\n", m_graphRangeTop); // convert
	OutputDebugString(text_buffer2); // print
	char text_buffer22[40] = { 0 }; //temporary buffer
	sprintf(text_buffer22, "Graph top range %d\n", m_graphYellow.getRangeTop()); // convert
	OutputDebugString(text_buffer22); // print

	char text_buffer3[40] = { 0 }; //temporary buffer
	sprintf(text_buffer3, "Value1 after scaling %d\n", value1); // convert
	OutputDebugString(text_buffer3); // print
	//char text_buffer33[40] = { 0 }; //temporary buffer
	//sprintf(text_buffer33, "Value1 after scaling %d\n", graphYellow.getRangeBottom()); // convert
	//OutputDebugString(text_buffer33); // print

	//cout << "Graph bottom range :" << m_graphRangeBottom << endl;
	//cout << "Graph top range :" << m_graphRangeTop << endl;
	//cout << "nValue after scaling :" << value << endl;

	if (m_parameter1GraphEnabled == true)
	{
		if (m_PreviousYellow_X == m_tickCounter)
		{
			++m_tickCounter;
			m_PreviousYellow_X = m_tickCounter;
		}
		else
		{
			m_PreviousYellow_X = m_tickCounter;
		}
		m_graphYellow.addValue(m_tickCounter, value1);
	}

	if (m_parameter2GraphEnabled == true)
	{
		if (m_PreviousRed_X == m_tickCounter)
		{
			++m_tickCounter;
			m_PreviousRed_X = m_tickCounter;
		}
		else
		{
			m_PreviousRed_X = m_tickCounter;
		}
		m_graphRed.addValue(m_tickCounter, value2);
	}

	if (m_parameter3GraphEnabled == true)
	{
		if (m_PreviousBlue_X == m_tickCounter)
		{
			++m_tickCounter;
			m_PreviousBlue_X = m_tickCounter;
		}
		else
		{
			m_PreviousBlue_X = m_tickCounter;
		}
		m_graphBlue.addValue(m_tickCounter, value3);
	}

	if (m_parameter4GraphEnabled == true)
	{
		if (m_PreviousGreen_X == m_tickCounter)
		{
			++m_tickCounter;
			m_PreviousGreen_X = m_tickCounter;
		}
		else
		{
			m_PreviousGreen_X = m_tickCounter;
		}
		m_graphGreen.addValue(m_tickCounter, value4);
	}
#endif
}

void Screen_Module1_GraphView::addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
	BSP_LED_Toggle(LED3);

	m_value = int(std::stof((char*)(s_UARTFrame.payload)) * SCALE_FACTOR); //scale by 1000

	if (s_UARTFrame.sign == '2')
	{
		/*Make value_int negative*/
		m_value = m_value * (-1);
	}

	//char str8[5];   
	//snprintf(str8, sizeof(uint8_t), "%f", value_float);   // convert uint8_t to string 
	//DebugPrint("\nRamka graphu ma wartosc: \n");
	//DebugPrint(str8);

	if (m_autoRangeEnabled == true)
	{
		for (int i = 0; i < GRAPHS_COUNT; i++)
		{
			/*Check if value is higher than any graph's top range*/
			if (m_value > m_graphs[i]->getRangeTop())
			{
				m_graphRangeTopChangedFlag = true;
				m_graphRangeTop = m_value;
			}
			/*Check if value is lower than graph bottom range*/
			else if (m_value < m_graphs[i]->getRangeBottom())
			{
				m_graphRangeBottomChangedFlag = true;
				m_graphRangeBottom = m_value;
			}
		}
	}

	if (m_tickCounter >= m_graphRangeRight)
	{
		m_graphYellow.clear();
		m_graphYellow.invalidate();

		m_graphRed.clear();
		m_graphRed.invalidate();

		m_graphBlue.clear();
		m_graphBlue.invalidate();

		m_graphGreen.clear();
		m_graphGreen.invalidate();

		m_PreviousYellow_X = 0;
		m_PreviousRed_X = 0;
		m_PreviousBlue_X = 0;
		m_PreviousGreen_X = 0;

		m_tickCounter = 0;
	}

	char str_bottom[10] = { '\0' };
	snprintf(str_bottom, 3 * sizeof(int), "%d", m_graphRangeBottom);   // convert uint8_t to string 
	DebugPrint("\nGraph bottom range: ");
	DebugPrint(str_bottom);
	DebugPrint("\n");

	char str_top[10] = { '\0' };
	snprintf(str_top, 3 * sizeof(int), "%d", m_graphRangeTop);   // convert uint8_t to string 
	DebugPrint("\nGraph top range: ");
	DebugPrint(str_top);
	DebugPrint("\n");

	char str_value[10] = { '\0' };
	snprintf(str_value, 3 * sizeof(int), "%d", m_value);   // convert uint8_t to string 
	DebugPrint("\nValue after scaling: ");
	DebugPrint(str_value);
	DebugPrint("\n");

	switch (s_UARTFrame.parameter)
	{
	case 'v':
		if (m_parameter1GraphEnabled == true)
		{
			if (m_PreviousYellow_X == m_tickCounter)
			{
				++m_tickCounter;
				m_PreviousYellow_X = m_tickCounter;
			}
			else
			{
				m_PreviousYellow_X = m_tickCounter;
			}
			m_graphYellow.addValue(m_tickCounter, m_value);
		}
		break;
	case 'c':
		if (m_parameter2GraphEnabled == true)
		{
			if (m_PreviousRed_X == m_tickCounter)
			{
				++m_tickCounter;
				m_PreviousRed_X = m_tickCounter;
			}
			else
			{
				m_PreviousRed_X = m_tickCounter;
			}
			m_graphRed.addValue(m_tickCounter, m_value);
		}
		break;
	case 'f':
		if (m_parameter3GraphEnabled == true)
		{
			if (m_PreviousBlue_X == m_tickCounter)
			{
				++m_tickCounter;
				m_PreviousBlue_X = m_tickCounter;
			}
			else
			{
				m_PreviousBlue_X = m_tickCounter;
			}
			m_graphBlue.addValue(m_tickCounter, m_value);
		}
		break;
	case 'p':
		if (m_parameter4GraphEnabled == true)
		{
			if (m_PreviousGreen_X == m_tickCounter)
			{
				++m_tickCounter;
				m_PreviousGreen_X = m_tickCounter;
			}
			else
			{
				m_PreviousGreen_X = m_tickCounter;
			}
			m_graphGreen.addValue(m_tickCounter, m_value);
		}
		break;
	}
#endif
}

uint8_t Screen_Module1_GraphView::activeSignalsCount()
{
	/*How many signals active/visible?*/
	uint8_t activeSignals = 0;

	if (m_parameter1GraphEnabled == true)
		++activeSignals;
	if (m_parameter2GraphEnabled == true)
		++activeSignals;
	if (m_parameter3GraphEnabled == true)
		++activeSignals;
	if (m_parameter4GraphEnabled == true)
		++activeSignals;

	return activeSignals;
}

void Screen_Module1_GraphView::updateCpuUsage(uint8_t value)
{
	Unicode::snprintf(textArea_CPU_UsageBuffer, 4, "%d", value);
	textArea_CPU_Usage.invalidate();
}