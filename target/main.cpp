/* General Includes. */
#include "init.h"
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include "string.h"
#include "uart_packet.h"
#include <stdio.h>
#include "utilities.h"

/* FreeRTOS Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "portmacro.h"
#include "semphr.h"

/* Defines */
#define QUEUES_SIZE 1
#define DEBUG_UART_WAITING 50
#define UART_TX_WAITING 50
#define NO_WAITING 0
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3
#define DEBUG 1

/* FreeRTOS stuff begin*/
#define GUI_TASK_STACK_SIZE 1700
#define UART_TASK_STACK_SIZE 200

#define CANVAS_BUFFER_SIZE 10000

xQueueHandle msgQueueUartReceive;
xQueueHandle msgQueueUartTransmit;
xQueueHandle msgQueueUartRxProcessedPacket;
xSemaphoreHandle uartRxSemaphore;
xSemaphoreHandle uartTxSemaphore;

static void guiTask(void* params);
static void uartRxTask(void* params);
static void uartTxTask(void* params);
/* FreeRTOS stuff end*/

/* General stuff begin*/
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

void MX_USART3_UART_Init(UART_HandleTypeDef *huart);
void MX_USART6_UART_Init(UART_HandleTypeDef *huart);

void Error_Handler(void);

/*Table to which UART interrupt writes*/
uint8_t uartReceivedPacket[PACKET_SIZE] = {0};
/* General stuff end*/

/*UART receive interrupt callback function*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
  BSP_LED_Toggle(LED4);
  signed long xHigherPriorityTaskWoken;
  
  /*Insert uartReceivedPacket table filled by UART interrupt to queue for UART task to process*/
  xQueueSendToBackFromISR(msgQueueUartReceive, uartReceivedPacket, &xHigherPriorityTaskWoken); 
  
  /*Enable interrupt listening again*/
  HAL_UART_Receive_IT(&huart6, uartReceivedPacket, PACKET_SIZE);
  
  /*Give semaphore to activate UART_Rx task*/
  xSemaphoreGiveFromISR(uartRxSemaphore, &xHigherPriorityTaskWoken);
}

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

using namespace touchgfx;

int main(void)
{
  hw_init();
  touchgfx_init();
  
  /*UART init*/
  MX_USART3_UART_Init(&huart3);
  MX_USART6_UART_Init(&huart6);
  
  static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
  CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
  
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
  msgQueueUartReceive = xQueueCreate(QUEUES_SIZE, sizeof(UartPacket));
  msgQueueUartRxProcessedPacket = xQueueCreate(QUEUES_SIZE, sizeof(UartPacket));
  msgQueueUartTransmit = xQueueCreate(QUEUES_SIZE, PACKET_SIZE * sizeof(uint8_t));
  
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

/* Task definitions begin */
static void guiTask(void* params)
{
  printf("GUI task initialized\n");
  touchgfx::HAL::getInstance()->taskEntry();
}

static void uartRxTask(void* params)
{  
  /*Structure to which UART task writes processed UART packet*/
  UartPacket uartPacket = {0};
  
  /*Start receiving*/
  HAL_UART_Receive_IT(&huart6, uartReceivedPacket, PACKET_SIZE);
  
  printf("RX task initialized\n");
  
  while(true)
  {   
    /*Check if interrupt occured so there is new data in uartReceivedPacket table*/
    if(xSemaphoreTake(uartRxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Ensure that there is no context switch during packet processing*/
      taskENTER_CRITICAL();
      
      //CRC check
      if(checkCrc32(uartReceivedPacket) == true)
      {
        /*Packet is correct and can be further processed*/
        
        /*Packet parsing to structure*/  
        convertUartPacketTableToUartStructure(uartReceivedPacket, uartPacket);
        
        xQueueSendToBack(msgQueueUartRxProcessedPacket, &uartPacket, NO_WAITING);
        
        /*Reset packet table to all zeroes*/
        clearPacketTable(uartReceivedPacket);
        
        /*Reset packet structure to all zeroes*/
        clearPacket(uartPacket);
      }
      else
      {
        /*Packet is corrupted and will not be further processed*/
        
        printf("WRONG CRC\n");
        
        BSP_LED_On(LED1);
        BSP_LED_On(LED2);
        BSP_LED_On(LED3);
        BSP_LED_On(LED4);
        
        /*Reset packet to all zeroes*/
        clearPacketTable(uartReceivedPacket);
        
        /*Reset packet structure to all zeroes*/
        clearPacket(uartPacket);
      }
      
      taskEXIT_CRITICAL();
    }
  }
}

static void uartTxTask(void* params)
{
  uint8_t uartMessageToTransmit[PACKET_SIZE] = {0};
  
  printf("TX task initialized\n");
  
  while(true)
  {  
    /*Take TxSemaphore*/
    if(xSemaphoreTake(uartTxSemaphore, portMAX_DELAY) == pdPASS)
    {
      taskENTER_CRITICAL(); 
      
      xQueueReceive(msgQueueUartTransmit, uartMessageToTransmit, NO_WAITING);                  
      appendCrcToPacket(uartMessageToTransmit);
      
      printf("TX Packet is: %.16s\n", uartMessageToTransmit);
      
      HAL_UART_Transmit(&huart6, uartMessageToTransmit, PACKET_SIZE, UART_TX_WAITING);
      
      taskEXIT_CRITICAL(); 
    }
  }
}
/* Task definitions end */