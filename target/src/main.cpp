/*TouchGFX includes*/
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>

/*STM32 includes*/
#include "stm32f4xx_hal_uart.h"
#include "stm32469i_discovery.h"

/*FreeRTOS Kernel includes*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/*User includes*/
#include "init.h"
#include "uart_packet.h"
#include "tasks.h"

xQueueHandle msgQueueUartRx;
xQueueHandle msgQueueUartTx;

xSemaphoreHandle uartRxSemaphore;
xSemaphoreHandle uartTxSemaphore;

UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

/*Object to which UART interrupt writes*/
UartPacket uartPacket;

/*UART receive interrupt callback function*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
  /*Toggle green LED after RX interrupt*/
  BSP_LED_Toggle(LED1);
  signed long xHigherPriorityTaskWoken;
  
  /*Enable interrupt listening again*/
  HAL_UART_Receive_IT(&huart6, static_cast<uint8_t*>(uartPacket), PACKET_SIZE);
  
  /*Give semaphore to activate UART_Rx task*/
  xSemaphoreGiveFromISR(uartRxSemaphore, &xHigherPriorityTaskWoken);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  printf("-----------------------UART ERROR CALLBACK-----------------------\n");
  Error_Handler();
}

int main(void)
{
  touchgfx::hw_init();
  touchgfx::touchgfx_init();
  
  /*UART init*/
  MX_USART3_UART_Init(&huart3);
  MX_USART6_UART_Init(&huart6);
  
  static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
  touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
  
  xTaskCreate(guiTask, 
              (TASKCREATE_NAME_TYPE)"GuiTask",
              GUI_TASK_STACK_SIZE,
              NULL,
              LOW_PRIORITY,
              NULL);
  
  xTaskCreate(uartRxTask, 
              (TASKCREATE_NAME_TYPE)"UartRxTask",
              UART_TASK_STACK_SIZE,
              NULL,
              MEDIUM_PRIORITY,
              NULL);
  
  xTaskCreate(uartTxTask, 
              (TASKCREATE_NAME_TYPE)"UartTxTask",
              UART_TASK_STACK_SIZE,
              NULL,
              HIGH_PRIORITY,
              NULL);
  
  /*Create message queues for UART task*/
  msgQueueUartRx = xQueueCreate(QUEUES_SIZE, sizeof(UartPacket));
  msgQueueUartTx = xQueueCreate(QUEUES_SIZE, sizeof(UartPacket));
  
  /*Create UART semaphore*/
  uartRxSemaphore = xSemaphoreCreateBinary();
  uartTxSemaphore = xSemaphoreCreateBinary();
  
  /*Initialize LEDS for debugging purposes*/
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  printf("System initialized, starting FreeRTOS Scheduler\n");
  
  vTaskStartScheduler();
  
  /*Control never reaches here*/
  return 0;
}