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

/*Data needed to initialize Info screen specifications*/
uint8_t Model::m_vendor[PAYLOAD_SIZE] = {0};
uint8_t Model::m_type[PAYLOAD_SIZE] = {0};
uint8_t Model::m_model[PAYLOAD_SIZE] = {0};
uint8_t Model::m_speed[PAYLOAD_SIZE] = {0};
uint8_t Model::m_version[PAYLOAD_SIZE] = {0};

uint8_t Model::m_vendorStringLength = 0;
uint8_t Model::m_typeStringLength = 0;
uint8_t Model::m_modelStringLength = 0;
uint8_t Model::m_speedStringLength = 0;
uint8_t Model::m_versionStringLength = 0;

/*Parameter names*/
uint8_t Model::m_parameter1Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_parameter2Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_parameter3Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_parameter4Name[PAYLOAD_SIZE] = {0};

uint8_t Model::m_parameter1NameLength = 0;
uint8_t Model::m_parameter2NameLength = 0;
uint8_t Model::m_parameter3NameLength = 0;
uint8_t Model::m_parameter4NameLength = 0;

void DebugPrint(const char* ch);

/*Structure to which UART task writes processed UART frame*/
UARTFrameStruct_t s_UARTFrame;

#endif

Model::Model() : modelListener(0)
{
#ifndef SIMULATOR
  extern UART_HandleTypeDef huart6;
  m_huart6 = huart6;
  initFrameCount = 0;
#endif
}

void Model::tick()
{
#ifndef SIMULATOR
  //get new UART message from message queue (if any)
  if (uxQueueMessagesWaiting(msgQueueUART_RX_ProcessedFrame) > 0)
  {
    /*Clear frame payload*/
    for(int i=0; i<PAYLOAD_SIZE;i++)
    {
      s_UARTFrame.payload[i] = '\0';
    }

    /*Frame is validated at this point and can be directly recovered from queue and copied to local s_UARTFrame structure*/    
    xQueueReceive(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, 0);
    
    if(s_UARTFrame.function == '1') //data type frame
    {
      modelListener->notifyNewUART_RX_ParsedFrame(s_UARTFrame);
    }
    else if(s_UARTFrame.function == '2') //init type frame
    {
      /*Skip if any module is already active*/
      if(activeModule == 0)
      {
        if(initFrameCount < 9)
        {
          DebugPrint("Init frame count less than 9\n");
          switch(s_UARTFrame.parameter)
          {
          case '1':
            DebugPrint("Case 1\n");
            strncpy(m_vendor, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_vendorStringLength = s_UARTFrame.length;
            DebugPrint("Case 1 finished\n");
            break;
          case '2':
            DebugPrint("Case 2\n");
            strncpy(m_type, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_typeStringLength = s_UARTFrame.length;
            DebugPrint("Case 2 finished\n");
            break;
          case '3':
            DebugPrint("Case 3\n");
            strncpy(m_model, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_modelStringLength = s_UARTFrame.length;
            DebugPrint("Case 3 finished\n");
            break;
          case '4':
            DebugPrint("Case 4\n");
            strncpy(m_speed, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_speedStringLength = s_UARTFrame.length;
            DebugPrint("Case 4 finished\n");
            break;
          case '5':
            DebugPrint("Case 5\n");
            strncpy(m_version, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_versionStringLength = s_UARTFrame.length;
            DebugPrint("Case 5 finished\n");
            break;
          case '6':
            DebugPrint("Case 6\n");
            strncpy(m_parameter1Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter1NameLength = s_UARTFrame.length;
            DebugPrint("Case 6 finished\n");
            break;
          case '7':
            DebugPrint("Case 7\n");
            strncpy(m_parameter2Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter2NameLength = s_UARTFrame.length;
            DebugPrint("Case 7 finished\n");
            break;
          case '8':
            DebugPrint("Case 8\n");
            strncpy(m_parameter3Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter3NameLength = s_UARTFrame.length;
            DebugPrint("Case 8 finished\n");
            break;
          case '9':
            DebugPrint("Case 9\n");
            strncpy(m_parameter4Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter4NameLength = s_UARTFrame.length;
            DebugPrint("Case 9 finished\n");
            break;
          default:
            DebugPrint("Case default\n");
          }
          DebugPrint("Increasing init frame count\n");
          ++initFrameCount;
          
          if(initFrameCount == 9)
          {
            DebugPrint("Received 9 init frames\n");
            modelListener->notifyInitFrame(s_UARTFrame); 
          }
        }
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
