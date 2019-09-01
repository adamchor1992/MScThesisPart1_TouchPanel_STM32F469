/* General Includes. */
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include "stm32469i_discovery.h" //for led driving
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <crc32.h>
#include "string.h"
#include "UART_Frame_Struct.h"

/* FreeRTOS Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "portmacro.h"
#include "semphr.h"

/* Defines */
#define FRAME_SIZE 16
#define FRAME_NO_CRC 12
#define QUEUES_SIZE 1
#define DEBUG_UART_WAITING 50
#define NO_WAITING 0
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3
#define DEBUG

/* FreeRTOS stuff begin*/
#define configGUI_TASK_STK_SIZE ( 1200 )
#define CANVAS_BUFFER_SIZE (5000)

xQueueHandle msgQueueUARTReceive;
xQueueHandle msgQueueUARTTransmit;
xSemaphoreHandle UART_RxSemaphore;
xSemaphoreHandle UART_TxSemaphore;
xSemaphoreHandle UART_Mutex;

static void GUI_Task(void* params);
static void UART_RxTask(void* params);
static void UART_TxTask(void* params);
/* FreeRTOS stuff end*/

/* General stuff begin*/
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;

void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

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
  
  xTaskCreate(UART_RxTask, (TASKCREATE_NAME_TYPE)"UART_RxTask",
              200,
              NULL,
              MEDIUM_PRIORITY,
              NULL);
  
  xTaskCreate(UART_TxTask, (TASKCREATE_NAME_TYPE)"UART_TxTask",
              200,
              NULL,
              HIGH_PRIORITY,
              NULL);
  
  /*Create message queues for UART task*/
  msgQueueUARTReceive = xQueueCreate(QUEUES_SIZE, sizeof(UARTFrameStruct_t));
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
  
  char str[] = "System initialized, starting FreeRTOS Scheduler\n";
  HAL_UART_Transmit(&huart3, str, strlen(str), DEBUG_UART_WAITING);
  
  vTaskStartScheduler();
  
  /*Control never reaches here*/
  return 0;
}

/* Task definitions begin */
static void GUI_Task(void* params)
{
  touchgfx::HAL::getInstance()->taskEntry();
}

static void UART_RxTask(void* params)
{
  uint32_t CRC_Value_Calculated;
  uint8_t CRC_Value_Received_Raw_8Bit[4];
  uint32_t CRC_Value_Received;
  
  uint8_t length_int;
  
  /*Structure to which UART task writes processed UART frame*/
  UARTFrameStruct_t s_UARTFrame;
  
  while(1)
  {   
    /*Check if interrupt occured so there is new data in UART_ReceivedFrame table*/
    if(xSemaphoreTake(UART_RxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Take UART mutex*/
      if(xSemaphoreTake(UART_Mutex, portMAX_DELAY) == pdPASS)
      {
        /*Ensure that there is no context switch during frame processing*/
        taskENTER_CRITICAL();

        char str[] = "RX processing\n";
        HAL_UART_Transmit(&huart3, str, strlen(str), DEBUG_UART_WAITING);
        
        //CRC check will be performed here
        CRC_Value_Calculated = Calculate_CRC32((char*)UART_ReceivedFrame, 12);
        
        CRC_Value_Received_Raw_8Bit[0] = UART_ReceivedFrame[12];
        CRC_Value_Received_Raw_8Bit[1] = UART_ReceivedFrame[13];
        CRC_Value_Received_Raw_8Bit[2] = UART_ReceivedFrame[14];
        CRC_Value_Received_Raw_8Bit[3] = UART_ReceivedFrame[15];
        
        CRC_Value_Received = CRC_Value_Received_Raw_8Bit[3] | CRC_Value_Received_Raw_8Bit[2] << 8 | CRC_Value_Received_Raw_8Bit[1] << 16 | CRC_Value_Received_Raw_8Bit[0] << 24;
        
        if(CRC_Value_Calculated != CRC_Value_Received)
        {
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
        char str2[] = "Frame is: ";
        HAL_UART_Transmit(&huart3, str2, strlen(str2), DEBUG_UART_WAITING);

        
        char frame[FRAME_NO_CRC + 1];
        memcpy(frame,UART_ReceivedFrame,FRAME_NO_CRC);
        frame[12] = '\n'; //line feed at the end of frame data
        
        HAL_UART_Transmit(&huart3, frame, FRAME_NO_CRC + 1, DEBUG_UART_WAITING);
#endif
        
        /*Frame parsing to structure*/
        s_UARTFrame.source = UART_ReceivedFrame[0];
        s_UARTFrame.module = UART_ReceivedFrame[1];
        s_UARTFrame.parameter = UART_ReceivedFrame[2];
        s_UARTFrame.length = UART_ReceivedFrame[3];
        
        length_int = s_UARTFrame.length - '0';
        
        for(uint8_t i=0; i < length_int; i++)
        {
          s_UARTFrame.payload[i] = UART_ReceivedFrame[4+i]; //payload starts from 4th element up to [4 + length] element
        }
        
        //what about CRC? 
        
        xQueueSendToBack(msgQueueUARTReceive, &s_UARTFrame, NO_WAITING);
        
        /*Give back UART Mutex*/
        xSemaphoreGive(UART_Mutex);
        
        taskEXIT_CRITICAL();
      }
    }
  }
}

static void UART_TxTask(void* params)
{
  uint8_t UART_MessageToTransmit[FRAME_SIZE] = {0};
  uint32_t CRC_Value_Calculated;
  uint32_t* CRC_Address;
  uint8_t *p1, *p2, *p3, *p4;
  
  while(1)
  {  
    /*Take TxSempahore*/
    if(xSemaphoreTake(UART_TxSemaphore, portMAX_DELAY) == pdPASS)
    {
      /*Take UART mutex*/
      if(xSemaphoreTake(UART_Mutex, portMAX_DELAY) == pdPASS)
      {
        taskENTER_CRITICAL(); 
        
#ifdef DEBUG
        char str[] = "TX processing\n";
        HAL_UART_Transmit(&huart3, str, strlen(str), DEBUG_UART_WAITING);
#endif
        
        xQueueReceive(msgQueueUARTTransmit, UART_MessageToTransmit, NO_WAITING);
        
        //CRC calculation
        CRC_Value_Calculated = Calculate_CRC32((char*)UART_MessageToTransmit, 12);
        
        CRC_Address = &CRC_Value_Calculated;
        
        p1 = ((uint8_t*)CRC_Address);
        p2 = ((uint8_t*)CRC_Address + 1);
        p3 = ((uint8_t*)CRC_Address + 2);
        p4 = ((uint8_t*)CRC_Address + 3);
        
        UART_MessageToTransmit[15] = *p1;
        UART_MessageToTransmit[14] = *p2;
        UART_MessageToTransmit[13] = *p3;
        UART_MessageToTransmit[12] = *p4;
        
        HAL_UART_Transmit(&huart6, UART_MessageToTransmit, FRAME_SIZE, NO_WAITING); //show table contents
        
        /*Give back UART Mutex*/
        xSemaphoreGive(UART_Mutex);
        
        taskEXIT_CRITICAL(); 
      }
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
  BSP_LED_On(LED2); //in case of error turn on red LED
}
