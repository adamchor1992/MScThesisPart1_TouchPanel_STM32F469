#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>

#ifndef SIMULATOR
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "string.h"
#include "UART_Frame_Struct.h"

extern xQueueHandle msgQueueUART_RX_ProcessedFrame;
extern xQueueHandle msgQueueUARTTransmit;
extern xSemaphoreHandle UART_TxSemaphore;
extern uint8_t activeModule;

uint8_t value = 0; 

void DebugPrint(const char* ch);

/*Structure to which UART task writes processed UART frame*/
UARTFrameStruct_t s_UARTFrame;

#endif

Model::Model() : modelListener(0)
{
	#ifndef SIMULATOR
  extern UART_HandleTypeDef huart6;
  m_huart6 = huart6;
  #endif
}

void Model::tick()
{
#ifndef SIMULATOR
  //get new UART message from message queue (if any)
  if (uxQueueMessagesWaiting(msgQueueUART_RX_ProcessedFrame) > 0)
  {
    /*Frame is validated at this point and can be directly recovered from queue and copied to local s_UARTFrame structure*/    
    xQueueReceive(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, 0);
    
    if(s_UARTFrame.function == '1') //data type frame
    {
      modelListener->notifyNewUART_RX_ParsedFrame(s_UARTFrame);
    }
    /*Skip if any module is already active*/
    else if(s_UARTFrame.function == '2') //init type frame
    {
      if(activeModule == 0)
      {
        modelListener->notifyInitFrame(s_UARTFrame);
      }
      else
      {
        DebugPrint("Skipping frame init due to some module is already active\n");
      }
    }
    else
    {
      DebugPrint("Wrong frame type in Model.cpp\n");
    }
    
    //modelListener->notifyNewUART_TX_Value(UART_ReceivedValue); //notify GUI of something new to TRANSMIT
    //xQueueSendToBack(msgQueueUARTTransmit, UART_ReceivedValue, 0);
  }
  
  modelListener->notifyNewCpuUsageValue(touchgfx::HAL::getInstance()->getMCULoadPct());
  
#endif
}

void Model::setNewValueToSet(UARTFrameStruct_t & s_UARTFrame)
{
	#ifndef SIMULATOR
  uint8_t UART_ValueToTransmit[FRAME_SIZE] = {0};
  
  UART_ValueToTransmit[0] = s_UARTFrame.source;
  UART_ValueToTransmit[1] = s_UARTFrame.module;
  UART_ValueToTransmit[2] = s_UARTFrame.function;
  UART_ValueToTransmit[3] = s_UARTFrame.parameter;
  UART_ValueToTransmit[4] = s_UARTFrame.sign;
  UART_ValueToTransmit[5] = s_UARTFrame.length;
  
  uint8_t length_int = s_UARTFrame.length - '0'; //convert to int
  
  for (int i = 0; i < length_int; i++)
  {
    UART_ValueToTransmit[6 + i] = *(s_UARTFrame.payload + i);
  }
  
  xQueueSendToBack(msgQueueUARTTransmit, UART_ValueToTransmit, 0);
  
  /*Give semaphore to activate UART_Tx task*/
  xSemaphoreGive(UART_TxSemaphore);
  #endif
}
