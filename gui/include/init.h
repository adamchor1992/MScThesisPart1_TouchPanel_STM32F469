#ifndef INIT_H
#define INIT_H

#include "stm32f4xx_hal_uart.h"
#include "stm32469i_discovery.h" //for led driving

void MX_USART3_UART_Init(UART_HandleTypeDef *huart);
void MX_USART6_UART_Init(UART_HandleTypeDef *huart);
void Error_Handler(void);
#endif