/* General Includes. */
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include "stm32469i_discovery.h" //for led driving
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <crc32.h>
#include "string.h"
#include "UART_Frame_Struct.h"
#include <stdio.h>

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
#define configGUI_TASK_STK_SIZE ( 2000 )
#define CANVAS_BUFFER_SIZE (10000)

xQueueHandle msgQueueUARTReceive;
xQueueHandle msgQueueUARTTransmit;
xQueueHandle msgQueueUART_RX_ProcessedFrame;
xSemaphoreHandle UART_RxSemaphore;
xSemaphoreHandle UART_TxSemaphore;
xSemaphoreHandle UART_Mutex;

uint8_t activeModule = 0;

static void GUI_Task(void* params);
static void UART_InitConnectionTask(void* params);
static void UART_Task(void* params);
static void UART_TxTask(void* params);
/* FreeRTOS stuff end*/

/* General stuff begin*/
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

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
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  
  static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
  CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
  
  xTaskCreate(GUI_Task, (TASKCREATE_NAME_TYPE)"GUITask",
              configGUI_TASK_STK_SIZE-300,
              NULL,
              LOW_PRIORITY,
              NULL);
  xTaskCreate(UART_InitConnectionTask, (TASKCREATE_NAME_TYPE)"UART_InitConnectionTask",
              200,
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

  /*Create UART mutex*/
  UART_Mutex = xSemaphoreCreateMutex();
  
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

static void UART_InitConnectionTask(void* params)
{
  UARTFrameStruct_t s_UARTFrame;
  uint8_t length_int;
  
  HAL_UART_Receive_IT(&huart6, UART_ReceivedFrame, FRAME_SIZE);
  
  DebugPrint("Waiting for module to send connection request\n");
  
  while(1)
  {
    /*Check if interrupt occured so there is new data in UART_ReceivedFrame table*/
    if(xSemaphoreTake(UART_RxSemaphore, portMAX_DELAY) == pdPASS)
    {
      taskENTER_CRITICAL();
      
      /*Frame parsing to structure*/
      s_UARTFrame.source = UART_ReceivedFrame[0];
      s_UARTFrame.module = UART_ReceivedFrame[1];
      s_UARTFrame.function = UART_ReceivedFrame[2];
      s_UARTFrame.parameter = UART_ReceivedFrame[3];
      s_UARTFrame.sign = UART_ReceivedFrame[4];
      s_UARTFrame.length = UART_ReceivedFrame[5];
      
      length_int = s_UARTFrame.length - '0';
      
      for(uint8_t i=0; i < length_int; i++)
      {
        s_UARTFrame.payload[i] = UART_ReceivedFrame[6+i]; //payload starts from 6th element up to [6 + length] element
      }
      
      if(s_UARTFrame.function == '2') // Init type frame
      {
        DebugPrint("CONNECTED\n");
        
        xQueueSendToBack(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, NO_WAITING);
        
        /*Give GUI task time to process Init frame*/
        vTaskDelay(100);
        
        DebugPrint("Creating UART_Task\n");
        
        xTaskCreate(UART_Task, (TASKCREATE_NAME_TYPE)"UART_Task",
                    200,
                    NULL,
                    MEDIUM_PRIORITY,
                    NULL);
        
        DebugPrint("Creating UART_TxTask\n");
        
        xTaskCreate(UART_TxTask, (TASKCREATE_NAME_TYPE)"UART_TxTask",
                    200,
                    NULL,
                    HIGH_PRIORITY,
                    NULL);
        
        DebugPrint("Deleting connection initialization task\n");
        
        /*Task deletes itself*/
        vTaskDelete(NULL);
      }
      else
      {
        DebugPrint("BAD FRAME TYPE\n");
      }
      
      taskEXIT_CRITICAL();
    }
  }
}

static void UART_Task(void* params)
{
  uint32_t CRC_Value_Calculated;
  uint8_t CRC_Value_Received_Raw_8Bit[4];
  uint32_t CRC_Value_Received;
  
  uint8_t length_int;
  
  /*Structure to which UART task writes processed UART frame*/
  UARTFrameStruct_t s_UARTFrame;
  
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
      
      //CRC check will be performed here
      CRC_Value_Calculated = Calculate_CRC32((char*)UART_ReceivedFrame, 16);
      
      CRC_Value_Received_Raw_8Bit[0] = UART_ReceivedFrame[16];
      CRC_Value_Received_Raw_8Bit[1] = UART_ReceivedFrame[17];
      CRC_Value_Received_Raw_8Bit[2] = UART_ReceivedFrame[18];
      CRC_Value_Received_Raw_8Bit[3] = UART_ReceivedFrame[19];
      
      CRC_Value_Received = CRC_Value_Received_Raw_8Bit[3] | CRC_Value_Received_Raw_8Bit[2] << 8 | CRC_Value_Received_Raw_8Bit[1] << 16 | CRC_Value_Received_Raw_8Bit[0] << 24;
      
      if(CRC_Value_Calculated != CRC_Value_Received)
      {
        DebugPrint("WRONG CRC");
        /*Frame is corrupted and should be discarded*/
        BSP_LED_On(LED1);
        BSP_LED_On(LED2);
        BSP_LED_On(LED3);
        BSP_LED_On(LED4);
        
        //HAL_UART_STATE_RESET(); //reset UART buffer?
        
        continue;
      }
      
      /*Frame is correct and can be further processed*/
      
#ifdef DEBUG
      DebugPrint("Frame is: ");
      char frame[FRAME_NO_CRC + 1];
      memcpy(frame,UART_ReceivedFrame,FRAME_NO_CRC);
      frame[12] = '\n'; //line feed at the end of frame data
      HAL_UART_Transmit(&huart3, (uint8_t*)frame, FRAME_NO_CRC + 1, DEBUG_UART_WAITING);
#endif
      
      /*Frame parsing to structure*/        
      s_UARTFrame.source = UART_ReceivedFrame[0];
      s_UARTFrame.module = UART_ReceivedFrame[1];
      s_UARTFrame.function = UART_ReceivedFrame[2];
      s_UARTFrame.parameter = UART_ReceivedFrame[3];
      s_UARTFrame.sign = UART_ReceivedFrame[4];
      s_UARTFrame.length = UART_ReceivedFrame[5];
      
      length_int = s_UARTFrame.length - '0';
      
      for(uint8_t i=0; i < length_int; i++)
      {
        s_UARTFrame.payload[i] = UART_ReceivedFrame[6+i]; //payload starts from 6th element up to [6 + length] element
      }
      
      //what about CRC? 
      
      xQueueSendToBack(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, NO_WAITING);
            
      taskEXIT_CRITICAL();
    }
  }
}

static void UART_TxTask(void* params)
{
  uint8_t UART_MessageToTransmit[FRAME_SIZE] = {0};
  uint32_t CRC_Value_Calculated;
  uint32_t* CRC_Address;
  uint8_t *p1, *p2, *p3, *p4;
  
  DebugPrint("TX task initialized\n");

  while(1)
  {  
    /*Take TxSempahore*/
    if(xSemaphoreTake(UART_TxSemaphore, portMAX_DELAY) == pdPASS)
    {
        taskENTER_CRITICAL(); 
        
#ifdef DEBUG
        DebugPrint("TX processing\n");
#endif
        
        xQueueReceive(msgQueueUARTTransmit, UART_MessageToTransmit, NO_WAITING);
        
        //CRC calculation
        CRC_Value_Calculated = Calculate_CRC32((char*)UART_MessageToTransmit, 16);
        
        CRC_Address = &CRC_Value_Calculated;
        
        p1 = ((uint8_t*)CRC_Address);
        p2 = ((uint8_t*)CRC_Address + 1);
        p3 = ((uint8_t*)CRC_Address + 2);
        p4 = ((uint8_t*)CRC_Address + 3);
        
        UART_MessageToTransmit[19] = *p1;
        UART_MessageToTransmit[18] = *p2;
        UART_MessageToTransmit[17] = *p3;
        UART_MessageToTransmit[16] = *p4;
        
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

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART3_UART_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
* @brief USART6 Initialization Function
* @param None
* @retval None
*/
void MX_USART6_UART_Init(void)
{
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  DebugPrint("ERROR HANDLER INVOKED");
  BSP_LED_On(LED1);
  BSP_LED_On(LED2);
  BSP_LED_On(LED3);
  BSP_LED_On(LED4);; //in case of error turn on all LEDs
}
