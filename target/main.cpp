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
#define FRAME_NO_CRC FRAME_SIZE-4
#define QUEUES_SIZE 1
#define DEBUG_UART_WAITING 50
#define UART_TX_WAITING 50
#define NO_WAITING 0
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3
#define DEBUG

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

void DebugPrint(const char* ch)
{
  HAL_UART_Transmit(&huart3, (uint8_t*)ch, strlen(ch), DEBUG_UART_WAITING);
}

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
  
  /*Debugging*/
  //vQueueAddToRegistry(  msgQueueUARTReceive, "msgQueueUARTReceive");
  //vQueueAddToRegistry(  msgQueueUARTTransmit, "msgQueueUARTTransmit");
  
  /*Create UART semaphore*/
  UART_RxSemaphore = xSemaphoreCreateBinary();
  UART_TxSemaphore = xSemaphoreCreateBinary();
  
  /*Initialize LEDS for debugging purposes*/
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  
  DebugPrint("System initialized, starting FreeRTOS Scheduler\n");

  vTaskStartScheduler();
  
  /*Control never reaches here*/
  return 0;
}

/* Task definitions begin */
static void GUI_Task(void* params)
{
  DebugPrint("GUI task initialized\n");
  touchgfx::HAL::getInstance()->taskEntry();
}

static void UART_RxTask(void* params)
{  
  /*Structure to which UART task writes processed UART frame*/
  UARTFrameStruct_t s_UARTFrame;
  
  /*Start receiving*/
  HAL_UART_Receive_IT(&huart6, UART_ReceivedFrame, FRAME_SIZE);
  
  DebugPrint("RX task initialized\n");
  
  while(1)
  {   
    /*Check if interrupt occured so there is new data in UART_ReceivedFrame table*/
    if(xSemaphoreTake(UART_RxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Ensure that there is no context switch during frame processing*/
      taskENTER_CRITICAL();
      
#ifdef DEBUG
      //DebugPrint("RX processing\n");
#endif
      
      //CRC check
      if(checkCRC(UART_ReceivedFrame) == false)
      {
        DebugPrint("WRONG CRC");
        /*Frame is corrupted and should be discarded*/
        BSP_LED_On(LED1);
        BSP_LED_On(LED2);
        BSP_LED_On(LED3);
        BSP_LED_On(LED4);
        
        /*Stop processing corrupted frame*/
        continue;
      }
      /*Frame is correct and can be further processed*/
            
      /*Frame parsing to structure*/  
      convertFrameTableToUARTstruct(UART_ReceivedFrame, s_UARTFrame);
            
      xQueueSendToBack(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, NO_WAITING);
            
      taskEXIT_CRITICAL();
    }
  }
}

static void UART_TxTask(void* params)
{
  uint8_t UART_MessageToTransmit[FRAME_SIZE] = {0};
  
  DebugPrint("TX task initialized\n");

  while(1)
  {  
    /*Take TxSemaphore*/
    if(xSemaphoreTake(UART_TxSemaphore, portMAX_DELAY) == pdPASS)
    {
        taskENTER_CRITICAL(); 
        
#ifdef DEBUG
        DebugPrint("TX processing\n");
#endif
        
        xQueueReceive(msgQueueUARTTransmit, UART_MessageToTransmit, NO_WAITING);                  
        appendCRCtoFrame(UART_MessageToTransmit);
        
#ifdef DEBUG
        DebugPrint("TX Frame is: ");
        char frame[FRAME_NO_CRC + 1];
        memcpy(frame,UART_MessageToTransmit,FRAME_NO_CRC);
        frame[16] = '\n'; //line feed at the end of frame data
        HAL_UART_Transmit(&huart3, (uint8_t*)frame, FRAME_NO_CRC + 1, DEBUG_UART_WAITING);
#endif
        
        HAL_UART_Transmit(&huart6, UART_MessageToTransmit, FRAME_SIZE, UART_TX_WAITING); //show table contents
        
        taskEXIT_CRITICAL(); 
    }
  }
}
/* Task definitions end */