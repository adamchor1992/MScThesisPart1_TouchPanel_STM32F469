#ifndef SIMULATOR

#include "stm32f4xx_hal_uart.h"
#include "stm32469i_discovery.h"

extern UART_HandleTypeDef huart3;

#if DEBUG == 1
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t*)&ch, 1, DEBUG_UART_WAITING);
  
  return ch;
}
#else
int fputc(int ch, FILE *f)
{
  return 0;
}
#endif

void Error_Handler(void)
{
  /*In case of error turn on all LEDs*/
  BSP_LED_On(LED1);
  BSP_LED_On(LED2);
  BSP_LED_On(LED3);
  BSP_LED_On(LED4);
  
  printf("ERROR HANDLER INVOKED\n");
}

void MX_USART3_UART_Init(UART_HandleTypeDef *huart)
{
  huart->Instance = USART3;
  huart->Init.BaudRate = 115200;
  huart->Init.WordLength = UART_WORDLENGTH_8B;
  huart->Init.StopBits = UART_STOPBITS_1;
  huart->Init.Parity = UART_PARITY_NONE;
  huart->Init.Mode = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(huart) != HAL_OK)
  {
    Error_Handler();
  }
}

void MX_USART6_UART_Init(UART_HandleTypeDef *huart)
{
  huart->Instance = USART6;
  huart->Init.BaudRate = 115200;
  huart->Init.WordLength = UART_WORDLENGTH_8B;
  huart->Init.StopBits = UART_STOPBITS_1;
  huart->Init.Parity = UART_PARITY_NONE;
  huart->Init.Mode = UART_MODE_TX_RX;
  huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart->Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(huart) != HAL_OK)
  {
    Error_Handler();
  }
}
#endif