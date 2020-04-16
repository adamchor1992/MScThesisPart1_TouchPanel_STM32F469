#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <gui/common/FrontendApplication.hpp>

#ifndef SIMULATOR
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "string.h"
#include "uart_packet.h"

extern xQueueHandle msgQueueUartRx;
extern xQueueHandle msgQueueUartTx;
extern xSemaphoreHandle uartTxSemaphore;

extern UART_HandleTypeDef huart6;
UART_HandleTypeDef* Model::m_pHuart6 = &huart6;
#endif

#define NO_WAITING 0

uint8_t Model::m_InitParametersModule1[INIT_PACKETS_COUNT][PAYLOAD_SIZE] = {{0}};
uint8_t Model::m_InitParametersModule2[INIT_PACKETS_COUNT][PAYLOAD_SIZE] = {{0}};
uint8_t Model::m_InitParametersModule3[INIT_PACKETS_COUNT][PAYLOAD_SIZE] = {{0}};

bool Model::module1Connected = false;
bool Model::module2Connected = false;
bool Model::module3Connected = false;

Model::Model() : m_ModelListener(0)
{
#ifndef SIMULATOR
  m_ReceivedInitPacketCount = 0;
#endif
}

void Model::tick()
{
#ifndef SIMULATOR
  //get new UART message from message queue (if any)
  if (uxQueueMessagesWaiting(msgQueueUartRx) > 0)
  {    
    UartPacket uartPacket;
    
    /*Packet is validated at this point and can be directly recovered from queue and copied to local uartPacket structure*/    
    xQueueReceive(msgQueueUartRx, &uartPacket, 0);
    
    ModuleID module = uartPacket.GetModule();
    
    switch(module)
    {
    case ModuleID::MODULE1:
      ProcessPacket(uartPacket, ModuleID::MODULE1);
      break;
      
    case ModuleID::MODULE2:
      ProcessPacket(uartPacket, ModuleID::MODULE2);
      break;
      
    case ModuleID::MODULE3:
      ProcessPacket(uartPacket, ModuleID::MODULE3);
      break;
      
    default:
      printf("Unsupported module %c in Model.cpp\n", module);
      printf("Unsupported module %d in Model.cpp\n", module);
    }
  }
  m_ModelListener->NotifyNewCpuUsageValue(touchgfx::HAL::getInstance()->getMCULoadPct());
#endif
}

void Model::ProcessPacket(UartPacket& uartPacket, ModuleID module)
{
#ifndef SIMULATOR
  Function function = uartPacket.GetFunction();
  
  if(IsModuleActive(module) == true)
  {
    if(function == Function::DATA_PACKET)
    {
      m_ModelListener->NotifyNewUartRxParsedPacket(uartPacket);
    }
    else if(function == Function::DEINIT_PACKET)
    {
      printf("Deinit packet received\n");
      
      DeactivateModule(module);
      
      /*Go back to main menu screen*/
      static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen_MainScreenNoTransition();
    }
    else if(function == Function::SET_GRAPH_RANGE_MIN)
    {
      printf("Set graph range minimum packet received\n");
      m_ModelListener->NotifyNewGraphRange(uartPacket);
    }
    else if(function == Function::SET_GRAPH_RANGE_MAX)
    {
      printf("Set graph range maximum packet received\n");
      m_ModelListener->NotifyNewGraphRange(uartPacket);
    }
    else if(function == Function::SET_GRAPH_TIME_RANGE)
    {
      printf("Set graph time range packet received\n");
      m_ModelListener->NotifyNewGraphRange(uartPacket);
    }
    else
    {
      printf("Wrong packet function for module %c in active state\n", module);
    }
  }
  /*Module inactive*/
  else
  {
    if(function == Function::INIT_PACKET)
    {
      if(m_ReceivedInitPacketCount < INIT_PACKETS_COUNT)
      {
        uint8_t lengthInt = uartPacket.GetLength();
        
        if(module == ModuleID::MODULE1)
        {
          /*Clear buffer before writing new values*/
          memset(m_InitParametersModule1[m_ReceivedInitPacketCount], 0, PAYLOAD_SIZE);

          memcpy(m_InitParametersModule1[m_ReceivedInitPacketCount], uartPacket.GetPayload(), lengthInt);
        }
        else if(module == ModuleID::MODULE2)
        {
          /*Clear buffer before writing new values*/
          memset(m_InitParametersModule2[m_ReceivedInitPacketCount], 0, PAYLOAD_SIZE);

          memcpy(m_InitParametersModule2[m_ReceivedInitPacketCount], uartPacket.GetPayload(), lengthInt);
        }
        else if(module == ModuleID::MODULE3)
        {
          /*Clear buffer before writing new values*/
          memset(m_InitParametersModule3[m_ReceivedInitPacketCount], 0, PAYLOAD_SIZE);

          memcpy(m_InitParametersModule3[m_ReceivedInitPacketCount], uartPacket.GetPayload(), lengthInt);
        }
        
        ++m_ReceivedInitPacketCount;
      }
      else
      {
        printf("Wrong module\n");
      }
      
      printf("Received %d out of %d required init packets\n", m_ReceivedInitPacketCount, INIT_PACKETS_COUNT);
      
      if(m_ReceivedInitPacketCount == INIT_PACKETS_COUNT)
      {
        printf("Received all of %d init packets\n", INIT_PACKETS_COUNT);
        m_ModelListener->NotifyAllInitPacketsReceived(uartPacket); 
        
        /*Set m_ReceivedInitPacketCount back to 0 to make another connection initialization possible after connection deinitialization*/
        m_ReceivedInitPacketCount = 0;
      }
    }
    else
    {
      printf("Wrong packet type for module %c in inactive state\n", module);
    }
  }
#endif
}

void Model::ActivateModule(ModuleID module)
{
  switch(module)
  {
  case ModuleID::MODULE1:
    module1Connected = true;
    printf("Module 1 activated\n");
    break;
    
  case ModuleID::MODULE2:
    module2Connected = true;
    printf("Module 2 activated\n");
    break;
    
  case ModuleID::MODULE3:
    module3Connected = true;
    printf("Module 3 activated\n");
    break;
    
  default:
    printf("BAD MODULE NUMBER\n");
  }
}

void Model::DeactivateModule(ModuleID module)
{
  switch(module)
  {
  case ModuleID::MODULE1:
    module1Connected = false;
    printf("Module 1 deactivated\n");
    break;
    
  case ModuleID::MODULE2:
    module2Connected = false;
    printf("Module 2 deactivated\n");
    break;
    
  case ModuleID::MODULE3:
    module3Connected = false;
    printf("Module 3 deactivated\n");
    break;
    
  default:
    printf("BAD MODULE NUMBER\n");
  }
}

bool Model::IsModuleActive(ModuleID module)
{
  switch(module)
  {
  case ModuleID::MODULE1:
    return module1Connected;
    break;
    
  case ModuleID::MODULE2:
    return module2Connected;
    break;
    
  case ModuleID::MODULE3:
    return module3Connected;
    break;
    
  default:
    printf("BAD GET MODULE STATE\n");
    return false;
  }
}

void Model::SetNewValueToSet(const UartPacket& uartPacket)
{
#ifndef SIMULATOR
  xQueueSendToBack(msgQueueUartTx, &uartPacket, NO_WAITING);
  
  /*Give semaphore to activate UART_Tx task*/
  xSemaphoreGive(uartTxSemaphore);
#endif
}