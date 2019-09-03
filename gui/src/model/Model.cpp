#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "string.h"
#include "UART_Frame_Struct.h"

extern xQueueHandle msgQueueUART_RX_ProcessedFrame;
extern xQueueHandle msgQueueUARTTransmit;
extern xSemaphoreHandle UART_TxSemaphore;

uint8_t value = 0; 

/*Structure to which UART task writes processed UART frame*/
UARTFrameStruct_t s_UARTFrame;

Model::Model() : modelListener(0)
{
  extern UART_HandleTypeDef huart6;
  m_huart6 = huart6;
}

void Model::tick()
{
  //get new UART message from message queue (if any)
  if (uxQueueMessagesWaiting(msgQueueUART_RX_ProcessedFrame) > 0)
  {
    /*Frame is validated at this point and can be directly recovered from queue and copied to local s_UARTFrame structure*/    
    xQueueReceive(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, 0);
    
    if(s_UARTFrame.type == '1') //control type frame
    {
      modelListener->notifyNewControlFrame(s_UARTFrame);
    }
    else if(s_UARTFrame.type == '2') //data type frame
    {
      modelListener->notifyNewUART_RX_Parsed_Frame_Graph(s_UARTFrame);
      modelListener->notifyNewUART_RX_Value(s_UARTFrame); //notify GUI of something new RECEIVED
    }
    
    //modelListener->notifyNewUART_TX_Value(UART_ReceivedValue); //notify GUI of something new to TRANSMIT
    
    //xQueueSendToBack(msgQueueUARTTransmit, UART_ReceivedValue, 0);
  }
  
  modelListener->notifyNewCpuUsageValue(touchgfx::HAL::getInstance()->getMCULoadPct());
}

void Model::setNewValueToSet(UARTFrameStruct_t & s_UARTFrame)
{
  uint8_t UART_ValueToTransmit[FRAME_SIZE] = {0};
  
  UART_ValueToTransmit[0] = s_UARTFrame.source;
  UART_ValueToTransmit[1] = s_UARTFrame.module;
  UART_ValueToTransmit[2] = s_UARTFrame.parameter;
  UART_ValueToTransmit[3] = s_UARTFrame.length;
  
  s_UARTFrame.length = s_UARTFrame.length - '0'; //convert to int
  
  for (int i = 0; i < s_UARTFrame.length; i++)
  {
    UART_ValueToTransmit[4 + i] = *(s_UARTFrame.payload + i);
  }
  
  xQueueSendToBack(msgQueueUARTTransmit, UART_ValueToTransmit, 0);
  
  /*Give semaphore to activate UART_Tx task*/
  xSemaphoreGive(UART_TxSemaphore);
}
