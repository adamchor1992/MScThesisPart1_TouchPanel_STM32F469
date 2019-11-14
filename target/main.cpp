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

xQueueHandle msgQueueUartRx;
xQueueHandle msgQueueUartTx;

xSemaphoreHandle uartRxSemaphore;
xSemaphoreHandle uartTxSemaphore;
xSemaphoreHandle uartMutex;

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

/*Object to which UART interrupt writes*/
UartPacket uartPacket;
/* General stuff end*/

/*UART receive interrupt callback function*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
  BSP_LED_Toggle(LED4);
  signed long xHigherPriorityTaskWoken;
  
  /*Enable interrupt listening again*/
  HAL_UART_Receive_IT(&huart6, uartPacket.getPacketTable(), PACKET_SIZE);
  
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
  msgQueueUartRx = xQueueCreate(QUEUES_SIZE, sizeof(UartPacket));
  msgQueueUartTx = xQueueCreate(QUEUES_SIZE, sizeof(UartPacket));
  
  /*Create UART semaphore*/
  uartRxSemaphore = xSemaphoreCreateBinary();
  uartTxSemaphore = xSemaphoreCreateBinary();
  uartMutex = xSemaphoreCreateMutex();
  
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
  /*Start receiving*/
  HAL_UART_Receive_IT(&huart6, uartPacket.getPacketTable(), PACKET_SIZE);
  
  printf("RX task initialized\n");
  
  while(true)
  {   
    /*Check if interrupt occured so there is new data in uartPacket table*/
    if(xSemaphoreTake(uartRxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Check if UART mutex is available to take. Wait 10 ticks*/
      if( xSemaphoreTake( uartMutex, NO_WAITING) == pdTRUE )
      {
        /*Ensure that there is no context switch during packet processing*/
        taskENTER_CRITICAL();
       
        //CRC check
        if(uartPacket.checkCrc32() == true)
        {
          /*Packet is correct and can be further processed*/
          
          uartPacket.updateFields();
          
#ifdef DEBUG
          printf("Rx packet:\n");
          uartPacket.printPacket();
#endif
          
          xQueueSendToBack(msgQueueUartRx, &uartPacket, NO_WAITING);
          
          /*Reset packet to all zeroes*/
          uartPacket.clearPacket();
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
          uartPacket.clearPacket();
        }
        
        /*Give back mutex*/
        xSemaphoreGive(uartMutex);
        
        taskEXIT_CRITICAL();
      }
      else
      {
        printf("MUTEX RX: Nie udalo sie pobrac mutexa\n");
      }
    }
  }
}

static void uartTxTask(void* params)
{
  printf("TX task initialized\n");
  
  while(true)
  {  
    /*Take TxSemaphore*/
    if(xSemaphoreTake(uartTxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Check if UART mutex is available to take. Wait 10 ticks*/
      if( xSemaphoreTake( uartMutex, NO_WAITING) == pdTRUE )
      {
        taskENTER_CRITICAL();
        
        UartPacket uartTxPacket;
        
        xQueueReceive(msgQueueUartTx, &uartTxPacket, NO_WAITING);
        
#ifdef DEBUG
        printf("Tx packet:\n");
        uartTxPacket.printPacket();
#endif
        
        uartTxPacket.updatePacketTable();
        uartTxPacket.appendCrcToPacket();
        
        HAL_UART_Transmit(&huart6, static_cast<uint8_t*>(uartTxPacket), PACKET_SIZE, UART_TX_WAITING);
        
        /*Give back mutex*/
        xSemaphoreGive(uartMutex);
        
        taskEXIT_CRITICAL();
      } 
      else
      {
        printf("MUTEX TX: Nie udalo sie pobrac mutexa\n");
      }
    }
  }
}
/* Task definitions end */