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
#include "uart_packet.h"
#include "utilities.h"

extern xQueueHandle msgQueueUartRxProcessedPacket;
extern xQueueHandle msgQueueUartTransmit;
extern xSemaphoreHandle uartTxSemaphore;

extern UART_HandleTypeDef huart6;
UART_HandleTypeDef* Model::m_pHuart6 = &huart6;

/*Structure to which UART task writes processed UART packet*/
UartPacket uartPacket;
#endif

uint8_t Model::m_InitParametersModule1[INIT_PACKET_COUNT][PAYLOAD_SIZE] = {{0}};
uint8_t Model::m_InitParametersModule2[INIT_PACKET_COUNT][PAYLOAD_SIZE] = {{0}};
uint8_t Model::m_InitParametersModule3[INIT_PACKET_COUNT][PAYLOAD_SIZE] = {{0}};

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
  if (uxQueueMessagesWaiting(msgQueueUartRxProcessedPacket) > 0)
  {
    /*Reset packet to all zeroes*/
    clearPacket(uartPacket);
    
    /*Packet is validated at this point and can be directly recovered from queue and copied to local uartPacket structure*/    
    xQueueReceive(msgQueueUartRxProcessedPacket, &uartPacket, 0);
    
    switch(uartPacket.module)
    {
    case '1':
      processPacket(1);
      break;
      
    case '2':
      processPacket(2);
      break;
      
    case '3':
      processPacket(3);
      break;
      
    default:
      printf("Unsupported module in Model.cpp\n");
    }
    m_ModelListener->notifyNewCpuUsageValue(touchgfx::HAL::getInstance()->getMCULoadPct());
  }
#endif
}

void Model::processPacket(int module)
{
#ifndef SIMULATOR
  if(isModuleActive(module) == true)
  {
    if(uartPacket.function == '1') //data type packet
    {
      m_ModelListener->notifyNewUartRxParsedPacket(uartPacket);
    }
    else if(uartPacket.function == '3') //deinit connection
    {
      printf("Deinit packet received\n");
      
      /*Set module not active*/
      deactivateModule(module);
      
      /*Go back to main menu screen*/
      static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen_MainScreenNoTransition();
    }
    else if(uartPacket.function == '7') //set graph range minimum
    {
      printf("Set graph range minimum packet received\n");
      m_ModelListener->notifyNewGraphRange(uartPacket);
    }
    else if(uartPacket.function == '8') //set graph range maximum
    {
      printf("Set graph range maximum packet received\n");
      m_ModelListener->notifyNewGraphRange(uartPacket);
    }
    else
    {
      printf("Wrong packet type for module %d in active state\n", module);
    }
  }
  /*Module inactive*/
  else
  {
    if(uartPacket.function == '2') //init packet
    {
      if(m_ReceivedInitPacketCount < INIT_PACKET_COUNT)
      {
        uint8_t length_int = uartPacket.length - '0'; //convert char to int length 
        
        memcpy(m_InitParametersModule1[m_ReceivedInitPacketCount], uartPacket.payload, length_int);
        
        ++m_ReceivedInitPacketCount;
      }
      
      printf("Received %d out of %d required init packets\n", m_ReceivedInitPacketCount, INIT_PACKET_COUNT);
      
      if(m_ReceivedInitPacketCount == INIT_PACKET_COUNT)
      {
        printf("Received all of %d init packets\n", INIT_PACKET_COUNT);
        m_ModelListener->notifyAllInitPacketsReceived(uartPacket); 
        
        /*Set m_ReceivedInitPacketCount back to 0 to make another connection initialization possible after connection deinitialization*/
        m_ReceivedInitPacketCount = 0;
      }
    }
    else
    {
      printf("Wrong packet type for module %d in inactive state\n", module);
    }
  }
#endif
}

void Model::activateModule(int module)
{
  switch(module)
  {
  case 1:
    module1Connected = true;
    printf("Module 1 activated\n");
    break;
    
  case 2:
    module2Connected = true;
    printf("Module 2 activated\n");
    break;
    
  case 3:
    module3Connected = true;
    printf("Module 3 activated\n");
    break;
    
  default:
    printf("BAD MODULE NUMBER\n");
  }
}

void Model::deactivateModule(int module)
{
  switch(module)
  {
  case 1:
    module1Connected = false;
    printf("Module 1 deactivated\n");
    break;
    
  case 2:
    module2Connected = false;
    printf("Module 2 deactivated\n");
    break;
    
  case 3:
    module3Connected = false;
    printf("Module 3 deactivated\n");
    break;
    
  default:
    printf("BAD MODULE NUMBER\n");
  }
}

bool Model::isModuleActive(int module)
{
  switch(module)
  {
  case 1:
    return module1Connected;
    break;
    
  case 2:
    return module2Connected;
    break;
    
  case 3:
    return module3Connected;
    break;
    
  default:
    printf("BAD GET MODULE STATE\n");
    return false;
  }
}

void Model::setNewValueToSet(const UartPacket & uartPacket)
{
#ifndef SIMULATOR
  uint8_t UART_ValueToTransmit[PACKET_SIZE] = {0};
  
  convertUartStructureToUartPacketTable(uartPacket, UART_ValueToTransmit);
  
  xQueueSendToBack(msgQueueUartTransmit, UART_ValueToTransmit, 0);
  
  /*Give semaphore to activate UART_Tx task*/
  xSemaphoreGive(uartTxSemaphore);
#endif
}
