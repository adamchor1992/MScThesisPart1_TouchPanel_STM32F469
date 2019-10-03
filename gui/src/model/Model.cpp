#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui_generated/common/FrontendApplicationBase.hpp>

#ifndef SIMULATOR
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "string.h"
#include "UART_Frame_Struct.h"
#include "../utilities.h"

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

uint8_t activeModule = 0;

/*Structure to which UART task writes processed UART frame*/
UARTFrameStruct_t s_UARTFrame;
#endif

Model::Model() : modelListener(0)
{
#ifndef SIMULATOR
  extern UART_HandleTypeDef huart6;
  m_huart6 = huart6;
  m_receivedInitFrameCount = 0;
  m_connectionState = UNCONNECTED;
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
    
    if(m_connectionState == CONNECTED)
    {
      if(s_UARTFrame.function == '1') //data type frame
      {
        modelListener->notifyNewUART_RX_ParsedFrame(s_UARTFrame);
      }
      else if(s_UARTFrame.function == '3') //deinit connection
      {
        printf("Deinit frame received\n");
        
        /*Set no active modules*/
        activeModule = 0;
        /*Go back to main menu screen*/
        static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen_MainScreenNoTransition();
        
        m_connectionState = UNCONNECTED;
      }
      else
      {
        printf("Wrong frame type in CONNECTED state\n");
      }
    }
    else if(m_connectionState == UNCONNECTED)
    {
      if(s_UARTFrame.function == '2') //init type frame
      {
        {
          /*Skip if any module is already active*/
          if(activeModule == 0)
          {
            if(m_receivedInitFrameCount < INIT_FRAME_COUNT)
            {
              switch(s_UARTFrame.parameter)
              {
              case 'a':
                memcpy(m_initParameter1Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter1NameStringLength = s_UARTFrame.length;
                break;
                
              case 'b':
                memcpy(m_initParameter2Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter2NameStringLength = s_UARTFrame.length;
                break;
                
              case 'c':
                memcpy(m_initParameter3Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter3NameStringLength = s_UARTFrame.length;
                break;
                
              case 'd':
                memcpy(m_initParameter4Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter4NameStringLength = s_UARTFrame.length;
                break;
                
              case 'e':
                memcpy(m_initParameter5Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter5NameStringLength = s_UARTFrame.length;
                break;
                
              case 'f':
                memcpy(m_initParameter1Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter1ValueStringLength = s_UARTFrame.length;
                break;
                
              case 'g':
                memcpy(m_initParameter2Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter2ValueStringLength = s_UARTFrame.length;
                break;
                
              case 'h':
                memcpy(m_initParameter3Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter3ValueStringLength = s_UARTFrame.length;
                break;
                
              case 'i':
                memcpy(m_initParameter4Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter4ValueStringLength = s_UARTFrame.length;
                break;
                
              case 'j':
                memcpy(m_initParameter5Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter5ValueStringLength = s_UARTFrame.length;
                break;
                
              case 'k':
                memcpy(m_parameter1Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter1NameLength = s_UARTFrame.length;
                break;
                
              case 'l':
                memcpy(m_parameter2Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter2NameLength = s_UARTFrame.length;
                break;
                
              case 'm':
                memcpy(m_parameter3Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter3NameLength = s_UARTFrame.length;
                break;
                
              case 'n':
                memcpy(m_parameter4Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter4NameLength = s_UARTFrame.length;
                break;
                
              case 'o':
                memcpy(m_settableParameter1Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter1NameLength = s_UARTFrame.length;
                break;
                
              case 'p':
                memcpy(m_settableParameter2Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter2NameLength = s_UARTFrame.length;
                break;
                
              case 'q':
                memcpy(m_settableParameter3Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter3NameLength = s_UARTFrame.length;
                break;
                
              case 'r':
                memcpy(m_settableParameter4Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter4NameLength = s_UARTFrame.length;
                break;
                
              case 's':
                memcpy(m_settableParameter5Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter5NameLength = s_UARTFrame.length;
                break;
                
              case 't':
                memcpy(m_settableParameter6Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter6NameLength = s_UARTFrame.length;
                break;
                
              case 'u':
                memcpy(m_settableParameter7Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter7NameLength = s_UARTFrame.length;
                break;
                
              case 'v':
                memcpy(m_settableParameter8Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter8NameLength = s_UARTFrame.length;
                break;
                
              case 'w':
                memcpy(m_settableParameter9Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter9NameLength = s_UARTFrame.length;
                break;
                
              case 'x':
                memcpy(m_settableParameter10Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter10NameLength = s_UARTFrame.length;
                break;
                
              default:
                printf("UNSUPPORTED INIT FRAME\n");
              }
              
              ++m_receivedInitFrameCount;
              
              printf("Received %d out of %d required init frames\n", m_receivedInitFrameCount, INIT_FRAME_COUNT);
              
              if(m_receivedInitFrameCount == INIT_FRAME_COUNT)
              {
                m_connectionState = CONNECTED;
                printf("Received %d init frames\n", m_receivedInitFrameCount);
                modelListener->notifyInitFrame(s_UARTFrame); 
                
                /*Set m_receivedInitFrameCount back to 0 to make another connection initialization possible after connection deinitialization*/
                m_receivedInitFrameCount = 0;
              }
            }
          }
          else
          {
            printf("Skipping frame init due to some module is already active\n");
          }
        }
      }
      else
      {
        printf("Wrong frame type in UNCONNECTED state\n");
      }
    }
    else
    {
      printf("Wrong state in Model.cpp\n");
    }
    
    modelListener->notifyNewCpuUsageValue(touchgfx::HAL::getInstance()->getMCULoadPct());
  }
#endif
}

void Model::setNewValueToSet(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
  uint8_t UART_ValueToTransmit[FRAME_SIZE] = {0};
  
  convertUARTstructToFrameTable(s_UARTFrame, UART_ValueToTransmit);
  
  xQueueSendToBack(msgQueueUARTTransmit, UART_ValueToTransmit, 0);
  
  /*Give semaphore to activate UART_Tx task*/
  xSemaphoreGive(UART_TxSemaphore);
#endif
}
