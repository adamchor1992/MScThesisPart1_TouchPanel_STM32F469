#include "stm32f4xx_hal_uart.h"

void MX_USART3_UART_Init(UART_HandleTypeDef *huart);
void MX_USART6_UART_Init(UART_HandleTypeDef *huart);
void Error_Handler(void);

#define DEBUG 1
#define QUEUES_SIZE 1
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3
#define GUI_TASK_STACK_SIZE 1700
#define UART_TASK_STACK_SIZE 200
#define CANVAS_BUFFER_SIZE 10000
#define UART_TX_WAITING 50