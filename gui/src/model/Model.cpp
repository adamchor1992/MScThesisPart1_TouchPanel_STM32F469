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
  connectionState = UNCONNECTED;
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
    
    if(connectionState == CONNECTED)
    {
      if(s_UARTFrame.function == '1') //data type frame
      {
        modelListener->notifyNewUART_RX_ParsedFrame(s_UARTFrame);
      }
      else if(s_UARTFrame.function == '3') //deinit connection
      {
        DebugPrint("Deinit frame received\n");
        
        /*Set no active modules*/
        activeModule = 0;
        /*Go back to main menu screen*/
        static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen_MainScreenNoTransition();
        
        connectionState = UNCONNECTED;
      }
      else
      {
        DebugPrint("Wrong frame type in CONNECTED state");
      }
    }
    else if(connectionState == UNCONNECTED)
    {
      if(s_UARTFrame.function == '2') //init type frame
      {
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
                memcpy(m_initParameter1Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter1NameStringLength = s_UARTFrame.length;
                DebugPrint("Case a finished\n");
                break;
                
              case 'b':
                DebugPrint("Case b\n");
                memcpy(m_initParameter2Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter2NameStringLength = s_UARTFrame.length;
                DebugPrint("Case b finished\n");
                break;
                
              case 'c':
                DebugPrint("Case c\n");
                memcpy(m_initParameter3Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter3NameStringLength = s_UARTFrame.length;
                DebugPrint("Case c finished\n");
                break;
                
              case 'd':
                DebugPrint("Case d\n");
                memcpy(m_initParameter4Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter4NameStringLength = s_UARTFrame.length;
                DebugPrint("Case d finished\n");
                break;
                
              case 'e':
                DebugPrint("Case e\n");
                memcpy(m_initParameter5Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter5NameStringLength = s_UARTFrame.length;
                DebugPrint("Case e finished\n");
                break;
                
              case 'f':
                DebugPrint("Case f\n");
                memcpy(m_initParameter1Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter1ValueStringLength = s_UARTFrame.length;
                DebugPrint("Case f finished\n");
                break;
                
              case 'g':
                DebugPrint("Case g\n");
                memcpy(m_initParameter2Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter2ValueStringLength = s_UARTFrame.length;
                DebugPrint("Case g finished\n");
                break;
                
              case 'h':
                DebugPrint("Case h\n");
                memcpy(m_initParameter3Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter3ValueStringLength = s_UARTFrame.length;
                DebugPrint("Case h finished\n");
                break;
                
              case 'i':
                DebugPrint("Case i\n");
                memcpy(m_initParameter4Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter4ValueStringLength = s_UARTFrame.length;
                DebugPrint("Case i finished\n");
                break;
                
              case 'j':
                DebugPrint("Case j\n");
                memcpy(m_initParameter5Value, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_initParameter5ValueStringLength = s_UARTFrame.length;
                DebugPrint("Case j finished\n");
                break;
                
              case 'k':
                DebugPrint("Case k\n");
                memcpy(m_parameter1Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter1NameLength = s_UARTFrame.length;
                DebugPrint("Case k finished\n");
                break;
                
              case 'l':
                DebugPrint("Case l\n");
                memcpy(m_parameter2Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter2NameLength = s_UARTFrame.length;
                DebugPrint("Case l finished\n");
                break;
                
              case 'm':
                DebugPrint("Case m\n");
                memcpy(m_parameter3Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter3NameLength = s_UARTFrame.length;
                DebugPrint("Case m finished\n");
                break;
                
              case 'n':
                DebugPrint("Case n\n");
                memcpy(m_parameter4Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_parameter4NameLength = s_UARTFrame.length;
                DebugPrint("Case n finished\n");
                break;
                
              case 'o':
                DebugPrint("Case o\n");
                memcpy(m_settableParameter1Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter1NameLength = s_UARTFrame.length;
                DebugPrint("Case o finished\n");
                break;
                
              case 'p':
                DebugPrint("Case p\n");
                memcpy(m_settableParameter2Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter2NameLength = s_UARTFrame.length;
                DebugPrint("Case p finished\n");
                break;
                
              case 'q':
                DebugPrint("Case q\n");
                memcpy(m_settableParameter3Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter3NameLength = s_UARTFrame.length;
                DebugPrint("Case q finished\n");
                break;
                
              case 'r':
                DebugPrint("Case r\n");
                memcpy(m_settableParameter4Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter4NameLength = s_UARTFrame.length;
                DebugPrint("Case r finished\n");
                break;
                
              case 's':
                DebugPrint("Case s\n");
                memcpy(m_settableParameter5Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter5NameLength = s_UARTFrame.length;
                DebugPrint("Case s finished\n");
                break;
                
              case 't':
                DebugPrint("Case t\n");
                memcpy(m_settableParameter6Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter6NameLength = s_UARTFrame.length;
                DebugPrint("Case t finished\n");
                break;
                
              case 'u':
                DebugPrint("Case u\n");
                memcpy(m_settableParameter7Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter7NameLength = s_UARTFrame.length;
                DebugPrint("Case u finished\n");
                break;
                
              case 'v':
                DebugPrint("Case v\n");
                memcpy(m_settableParameter8Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter8NameLength = s_UARTFrame.length;
                DebugPrint("Case v finished\n");
                break;
                
              case 'w':
                DebugPrint("Case w\n");
                memcpy(m_settableParameter9Name, s_UARTFrame.payload, PAYLOAD_SIZE);
                m_settableParameter9NameLength = s_UARTFrame.length;
                DebugPrint("Case w finished\n");
                break;
                
              case 'x':
                DebugPrint("Case x\n");
                memcpy(m_settableParameter10Name, s_UARTFrame.payload, PAYLOAD_SIZE);
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
                connectionState = CONNECTED;
                DebugPrint("Received 24 init frames\n");
                modelListener->notifyInitFrame(s_UARTFrame); 
                
                /*Set initFrameCount back to 0 to make another connection initialization possible after connection deinitialization*/
                initFrameCount = 0;
              }
            }
          }
          else
          {
            DebugPrint("Skipping frame init due to some module is already active\n");
          }
        }
      }
      else
      {
        DebugPrint("Wrong frame type in UNCONNECTED state");
      }
    }
    else
    {
      DebugPrint("Wrong state in Model.cpp");
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
