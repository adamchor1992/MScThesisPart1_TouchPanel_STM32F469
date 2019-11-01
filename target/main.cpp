/* General Includes. */
#include "init.h"
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include "string.h"
#include "UART_Frame_Struct.h"
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

xQueueHandle msgQueueUARTReceive;
xQueueHandle msgQueueUARTTransmit;
xQueueHandle msgQueueUART_RX_ProcessedFrame;
xSemaphoreHandle UART_RxSemaphore;
xSemaphoreHandle UART_TxSemaphore;

static void GUI_Task(void* params);
static void UART_RxTask(void* params);
static void UART_TxTask(void* params);
/* FreeRTOS stuff end*/

/* General stuff begin*/
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

void MX_USART3_UART_Init(UART_HandleTypeDef *huart);
void MX_USART6_UART_Init(UART_HandleTypeDef *huart);

void Error_Handler(void);

/*Table to which UART interrupt writes*/
uint8_t UART_ReceivedFrame[FRAME_SIZE] = {0};
/* General stuff end*/

/*UART receive interrupt callback function*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
  BSP_LED_Toggle(LED4);
  signed long xHigherPriorityTaskWoken;
  
  /*Insert UART_ReceivedFrame table filled by UART interrupt to queue for UART task to process*/
  xQueueSendToBackFromISR(msgQueueUARTReceive, UART_ReceivedFrame, &xHigherPriorityTaskWoken); 
  
  /*Enable interrupt listening again*/
  HAL_UART_Receive_IT(&huart6, UART_ReceivedFrame, FRAME_SIZE);
  
  /*Give semaphore to activate UART_Rx task*/
  xSemaphoreGiveFromISR(UART_RxSemaphore, &xHigherPriorityTaskWoken);
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
  
  xTaskCreate(GUI_Task, (TASKCREATE_NAME_TYPE)"GUITask",
              GUI_TASK_STACK_SIZE,
              NULL,
              LOW_PRIORITY,
              NULL);
  
  xTaskCreate(UART_RxTask, (TASKCREATE_NAME_TYPE)"UARTRxTask",
              UART_TASK_STACK_SIZE,
              NULL,
              MEDIUM_PRIORITY,
              NULL);
  
  xTaskCreate(UART_TxTask, (TASKCREATE_NAME_TYPE)"UART_TxTask",
              UART_TASK_STACK_SIZE,
              NULL,
              HIGH_PRIORITY,
              NULL);
  
  /*Create message queues for UART task*/
  msgQueueUARTReceive = xQueueCreate(QUEUES_SIZE, sizeof(UARTFrameStruct_t));
  msgQueueUART_RX_ProcessedFrame = xQueueCreate(QUEUES_SIZE, sizeof(UARTFrameStruct_t));
  msgQueueUARTTransmit = xQueueCreate(QUEUES_SIZE, FRAME_SIZE * sizeof(uint8_t));
  
  /*Create UART semaphore*/
  UART_RxSemaphore = xSemaphoreCreateBinary();
  UART_TxSemaphore = xSemaphoreCreateBinary();
  
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
static void GUI_Task(void* params)
{
  printf("GUI task initialized\n");
  touchgfx::HAL::getInstance()->taskEntry();
}

static void UART_RxTask(void* params)
{  
  /*Structure to which UART task writes processed UART frame*/
  UARTFrameStruct_t s_UARTFrame = {0};
  
  /*Start receiving*/
  HAL_UART_Receive_IT(&huart6, UART_ReceivedFrame, FRAME_SIZE);
  
  printf("RX task initialized\n");
  
  while(true)
  {   
    /*Check if interrupt occured so there is new data in UART_ReceivedFrame table*/
    if(xSemaphoreTake(UART_RxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Ensure that there is no context switch during frame processing*/
      taskENTER_CRITICAL();
      
      //CRC check
      if(checkCRC(UART_ReceivedFrame) == true)
      {
        /*Frame is correct and can be further processed*/
        
        /*Frame parsing to structure*/  
        convertFrameTableToUARTstruct(UART_ReceivedFrame, s_UARTFrame);
        
        xQueueSendToBack(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, NO_WAITING);
        
        /*Reset frame table to all zeroes*/
        clearFrameTable(UART_ReceivedFrame);
        
        /*Reset frame structure to all zeroes*/
        clearFrameStructure(s_UARTFrame);
      }
      else
      {
        /*Frame is corrupted and will not be further processed*/
        
        printf("WRONG CRC\n");
        
        BSP_LED_On(LED1);
        BSP_LED_On(LED2);
        BSP_LED_On(LED3);
        BSP_LED_On(LED4);
        
        /*Reset frame to all zeroes*/
        clearFrameTable(UART_ReceivedFrame);
        
        /*Reset frame structure to all zeroes*/
        clearFrameStructure(s_UARTFrame);
      }
      
      taskEXIT_CRITICAL();
    }
  }
}

static void UART_TxTask(void* params)
{
  uint8_t UART_MessageToTransmit[FRAME_SIZE] = {0};
  
  printf("TX task initialized\n");
  
  while(true)
  {  
    /*Take TxSemaphore*/
    if(xSemaphoreTake(UART_TxSemaphore, portMAX_DELAY) == pdPASS)
    {
      taskENTER_CRITICAL(); 
      
      xQueueReceive(msgQueueUARTTransmit, UART_MessageToTransmit, NO_WAITING);                  
      appendCRCtoFrame(UART_MessageToTransmit);
      
      printf("TX Frame is: %.16s\n", UART_MessageToTransmit);
      
      HAL_UART_Transmit(&huart6, UART_MessageToTransmit, FRAME_SIZE, UART_TX_WAITING); //show table contents
      
      taskEXIT_CRITICAL(); 
    }
  }
}
/* Task definitions end */