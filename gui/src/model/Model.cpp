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

/*Module initialization parameter names*/
uint8_t Model::m_initParameter1Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter2Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter3Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter4Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter5Name[PAYLOAD_SIZE] = {0};

uint8_t Model::m_initParameter1NameStringLength = 0;
uint8_t Model::m_initParameter2NameStringLength = 0;
uint8_t Model::m_initParameter3NameStringLength = 0;
uint8_t Model::m_initParameter4NameStringLength = 0;
uint8_t Model::m_initParameter5NameStringLength = 0;

/*Module initialization parameter values*/
uint8_t Model::m_initParameter1Value[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter2Value[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter3Value[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter4Value[PAYLOAD_SIZE] = {0};
uint8_t Model::m_initParameter5Value[PAYLOAD_SIZE] = {0};

uint8_t Model::m_initParameter1ValueStringLength = 0;
uint8_t Model::m_initParameter2ValueStringLength = 0;
uint8_t Model::m_initParameter3ValueStringLength = 0;
uint8_t Model::m_initParameter4ValueStringLength = 0;
uint8_t Model::m_initParameter5ValueStringLength = 0;

/*Custom parameter names*/
uint8_t Model::m_parameter1Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_parameter2Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_parameter3Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_parameter4Name[PAYLOAD_SIZE] = {0};

uint8_t Model::m_parameter1NameLength = 0;
uint8_t Model::m_parameter2NameLength = 0;
uint8_t Model::m_parameter3NameLength = 0;
uint8_t Model::m_parameter4NameLength = 0;

/*Settable parameter names*/
uint8_t Model::m_settableParameter1Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter2Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter3Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter4Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter5Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter6Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter7Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter8Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter9Name[PAYLOAD_SIZE] = {0};
uint8_t Model::m_settableParameter10Name[PAYLOAD_SIZE] = {0};

uint8_t Model::m_settableParameter1NameLength = 0;
uint8_t Model::m_settableParameter2NameLength = 0;
uint8_t Model::m_settableParameter3NameLength = 0;
uint8_t Model::m_settableParameter4NameLength = 0;
uint8_t Model::m_settableParameter5NameLength = 0;
uint8_t Model::m_settableParameter6NameLength = 0;
uint8_t Model::m_settableParameter7NameLength = 0;
uint8_t Model::m_settableParameter8NameLength = 0;
uint8_t Model::m_settableParameter9NameLength = 0;
uint8_t Model::m_settableParameter10NameLength = 0;

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
    for(int i=0; i < PAYLOAD_SIZE; i++)
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
        if(initFrameCount < INIT_FRAME_COUNT)
        {
          DebugPrint("Init frame count less than 24\n");
          
          switch(s_UARTFrame.parameter)
          {
          case 'a':
            DebugPrint("Case a\n");
            strncpy(m_initParameter1Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter1NameStringLength = s_UARTFrame.length;
            DebugPrint("Case a finished\n");
            break;
            
          case 'b':
            DebugPrint("Case b\n");
            strncpy(m_initParameter2Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter2NameStringLength = s_UARTFrame.length;
            DebugPrint("Case b finished\n");
            break;
            
          case 'c':
            DebugPrint("Case c\n");
            strncpy(m_initParameter3Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter3NameStringLength = s_UARTFrame.length;
            DebugPrint("Case c finished\n");
            break;
            
          case 'd':
            DebugPrint("Case d\n");
            strncpy(m_initParameter4Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter4NameStringLength = s_UARTFrame.length;
            DebugPrint("Case d finished\n");
            break;
            
          case 'e':
            DebugPrint("Case e\n");
            strncpy(m_initParameter5Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter5NameStringLength = s_UARTFrame.length;
            DebugPrint("Case e finished\n");
            break;
            
          case 'f':
            DebugPrint("Case f\n");
            strncpy(m_initParameter1Value, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter1ValueStringLength = s_UARTFrame.length;
            DebugPrint("Case f finished\n");
            break;
            
          case 'g':
            DebugPrint("Case g\n");
            strncpy(m_initParameter2Value, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter2ValueStringLength = s_UARTFrame.length;
            DebugPrint("Case g finished\n");
            break;
            
          case 'h':
            DebugPrint("Case h\n");
            strncpy(m_initParameter3Value, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter3ValueStringLength = s_UARTFrame.length;
            DebugPrint("Case h finished\n");
            break;
            
          case 'i':
            DebugPrint("Case i\n");
            strncpy(m_initParameter4Value, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter4ValueStringLength = s_UARTFrame.length;
            DebugPrint("Case i finished\n");
            break;
            
          case 'j':
            DebugPrint("Case j\n");
            strncpy(m_initParameter5Value, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_initParameter5ValueStringLength = s_UARTFrame.length;
            DebugPrint("Case j finished\n");
            break;
            
          case 'k':
            DebugPrint("Case k\n");
            strncpy(m_parameter1Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter1NameLength = s_UARTFrame.length;
            DebugPrint("Case k finished\n");
            break;
            
          case 'l':
            DebugPrint("Case l\n");
            strncpy(m_parameter2Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter2NameLength = s_UARTFrame.length;
            DebugPrint("Case l finished\n");
            break;
            
          case 'm':
            DebugPrint("Case m\n");
            strncpy(m_parameter3Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter3NameLength = s_UARTFrame.length;
            DebugPrint("Case m finished\n");
            break;
            
          case 'n':
            DebugPrint("Case n\n");
            strncpy(m_parameter4Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_parameter4NameLength = s_UARTFrame.length;
            DebugPrint("Case n finished\n");
            break;
            
          case 'o':
            DebugPrint("Case o\n");
            strncpy(m_settableParameter1Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter1NameLength = s_UARTFrame.length;
            DebugPrint("Case o finished\n");
            break;
            
          case 'p':
            DebugPrint("Case p\n");
            strncpy(m_settableParameter2Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter2NameLength = s_UARTFrame.length;
            DebugPrint("Case p finished\n");
            break;
            
          case 'q':
            DebugPrint("Case q\n");
            strncpy(m_settableParameter3Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter3NameLength = s_UARTFrame.length;
            DebugPrint("Case q finished\n");
            break;
            
          case 'r':
            DebugPrint("Case r\n");
            strncpy(m_settableParameter4Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter4NameLength = s_UARTFrame.length;
            DebugPrint("Case r finished\n");
            break;
            
          case 's':
            DebugPrint("Case s\n");
            strncpy(m_settableParameter5Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter5NameLength = s_UARTFrame.length;
            DebugPrint("Case s finished\n");
            break;
            
          case 't':
            DebugPrint("Case t\n");
            strncpy(m_settableParameter6Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter6NameLength = s_UARTFrame.length;
            DebugPrint("Case t finished\n");
            break;
            
          case 'u':
            DebugPrint("Case u\n");
            strncpy(m_settableParameter7Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter7NameLength = s_UARTFrame.length;
            DebugPrint("Case u finished\n");
            break;
            
          case 'v':
            DebugPrint("Case v\n");
            strncpy(m_settableParameter8Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter8NameLength = s_UARTFrame.length;
            DebugPrint("Case v finished\n");
            break;
            
          case 'w':
            DebugPrint("Case w\n");
            strncpy(m_settableParameter9Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter9NameLength = s_UARTFrame.length;
            DebugPrint("Case w finished\n");
            break;
            
          case 'x':
            DebugPrint("Case x\n");
            strncpy(m_settableParameter10Name, (const char*)s_UARTFrame.payload, PAYLOAD_SIZE);
            m_settableParameter10NameLength = s_UARTFrame.length;
            DebugPrint("Case x finished\n");
            break;
            
          default:
            DebugPrint("Case default\n");
          }
          
          DebugPrint("Increasing init frame count\n");
          ++initFrameCount;
          
          if(initFrameCount == INIT_FRAME_COUNT)
          {
            DebugPrint("Received 24 init frames\n");
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
