#include <gui/screen_uart_screen/Screen_UARTView.hpp>
#include "string.h"
#include <stdlib.h>
#include <touchgfx/Unicode.hpp>

Screen_UARTView::Screen_UARTView()
{
  char UART_String_copy[10] = " Hello ";
	
	extern UART_HandleTypeDef huart6;
  
  strncpy(UART_String, UART_String_copy, 8);
  
	m_huart6 = huart6;
}

void Screen_UARTView::setupScreen()
{
  Screen_UARTViewBase::setupScreen();
}

void Screen_UARTView::tearDownScreen()
{
  Screen_UARTViewBase::tearDownScreen();
}

void Screen_UARTView::sendUARTHello()
{
  HAL_UART_Transmit(&m_huart6, (unsigned char*)UART_String, 7, 5);
	updateUART_TX((unsigned char*)UART_String);
}

void Screen_UARTView::updateUART_RX(uint8_t *value)
{	
	uint16_t stringToDisplay[11] = {0,0,0,0,0,0,0,0,0,0,0};
	
	for(int i=0; i<10;i++)
	{
		*(stringToDisplay+i) = *(value+i);
	}

	Unicode::snprintf(textArea_UartRXBuffer, TEXTAREA_UARTRX_SIZE, "%s", stringToDisplay);
	textArea_UartRX.invalidate();
}

void Screen_UARTView::updateUART_TX(uint8_t *value)
{	
	uint16_t stringToDisplay[11] = {0,0,0,0,0,0,0,0,0,0,0};
	
	for(int i=0; i<10;i++)
	{
		*(stringToDisplay+i) = *(value+i);
	}

	Unicode::snprintf(textArea_UartTXBuffer, TEXTAREA_UARTTX_SIZE, "%s", stringToDisplay);
	textArea_UartTX.invalidate();
}

void Screen_UARTView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}