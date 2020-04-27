#include <touchgfx/hal/HAL.hpp>
#include "stm32f4xx_hal_uart.h"
#include "stm32469i_discovery.h"
#include "uart_packet.h"

/* FreeRTOS Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define UART_TX_WAITING 50
#define NO_WAITING 0

extern UART_HandleTypeDef huart6;
extern UartPacket uartPacket;
extern xSemaphoreHandle uartRxSemaphore;
extern xSemaphoreHandle uartTxSemaphore;
extern xQueueHandle msgQueueUartRx;
extern xQueueHandle msgQueueUartTx;

void guiTask(void* params)
{
  printf("GUI task initialized\n");
  touchgfx::HAL::getInstance()->taskEntry();
}

void uartRxTask(void* params)
{
  /*Start receiving*/
  HAL_UART_Receive_IT(&huart6, static_cast<uint8_t*>(uartPacket) , PACKET_SIZE);
  
  printf("RX task initialized\n");
  
  while(true)
  {   
    /*Check if interrupt occured so there is new data in uartPacket table*/
    if(xSemaphoreTake(uartRxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Ensure that there is no context switch during packet processing*/
      taskENTER_CRITICAL();
      
      if(uartPacket.CheckCrc32() == true)
      {
        /*Packet is correct and can be further processed*/
        printf("Rx packet:\n");
        uartPacket.PrintPacket(false);
        
        xQueueSendToBack(msgQueueUartRx, &uartPacket, NO_WAITING);
      }
      else
      {
        /*Packet is invalid and will not be further processed*/
        
        printf("WRONG CRC\n");
        uartPacket.PrintPacket(true);
        
        /*Turn on red LED*/
        BSP_LED_On(LED3);
      }
      
      taskEXIT_CRITICAL();
    }
  }
}

void uartTxTask(void* params)
{
  printf("TX task initialized\n");
  
  while(true)
  {
    /*Take TxSemaphore*/
    if(xSemaphoreTake(uartTxSemaphore, portMAX_DELAY) == pdPASS)
    {
      taskENTER_CRITICAL();
      
      UartPacket uartTxPacket;
      
      xQueueReceive(msgQueueUartTx, &uartTxPacket, NO_WAITING);
      
      printf("Tx packet:\n");
      uartTxPacket.PrintPacket(false);
      
      uartTxPacket.AppendCrcToPacket();
      
      /*Toggle blue LED*/
      BSP_LED_Toggle(LED4);
      
      HAL_UART_Transmit(&huart6, static_cast<uint8_t*>(uartTxPacket), PACKET_SIZE, UART_TX_WAITING);
      
      taskEXIT_CRITICAL();
    }
  }
}