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
#include "utilities.h"

extern xQueueHandle msgQueueUART_RX_ProcessedFrame;
extern xQueueHandle msgQueueUARTTransmit;
extern xSemaphoreHandle UART_TxSemaphore;

extern UART_HandleTypeDef huart6;
UART_HandleTypeDef* Model::m_pHuart6 = &huart6;

/*Structure to which UART task writes processed UART frame*/
UARTFrameStruct_t s_UARTFrame;
#endif

uint8_t Model::m_InitParametersModule1[INIT_FRAME_COUNT][PAYLOAD_SIZE] = {{0}};
uint8_t Model::m_InitParametersModule2[INIT_FRAME_COUNT][PAYLOAD_SIZE] = {{0}};
uint8_t Model::m_InitParametersModule3[INIT_FRAME_COUNT][PAYLOAD_SIZE] = {{0}};

bool Model::module1Connected = false;
bool Model::module2Connected = false;
bool Model::module3Connected = false;

Model::Model() : m_ModelListener(0)
{
#ifndef SIMULATOR
  m_ReceivedInitFrameCount = 0;
#endif
}

void Model::tick()
{
#ifndef SIMULATOR
  //get new UART message from message queue (if any)
  if (uxQueueMessagesWaiting(msgQueueUART_RX_ProcessedFrame) > 0)
  {
    /*Reset frame to all zeroes*/
    clearFrameStructure(s_UARTFrame);
    
    /*Frame is validated at this point and can be directly recovered from queue and copied to local s_UARTFrame structure*/    
    xQueueReceive(msgQueueUART_RX_ProcessedFrame, &s_UARTFrame, 0);
    
    switch(s_UARTFrame.module)
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
    if(s_UARTFrame.function == '1') //data type frame
    {
      m_ModelListener->notifyNewUART_RX_ParsedFrame(s_UARTFrame);
    }
    else if(s_UARTFrame.function == '3') //deinit connection
    {
      printf("Deinit frame received\n");
      
      /*Set module not active*/
      deactivateModule(module);
      
      /*Go back to main menu screen*/
      static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen_MainScreenNoTransition();
    }
    else
    {
      printf("Wrong frame type for module %d in active state\n", module);
    }
  }
  /*Module inactive*/
  else
  {
    if(s_UARTFrame.function == '2') //init frame
    {
      if(m_ReceivedInitFrameCount < INIT_FRAME_COUNT)
      {
        uint8_t length_int = s_UARTFrame.length - '0'; //convert char to int length 
        
        memcpy(m_InitParametersModule1[m_ReceivedInitFrameCount], s_UARTFrame.payload, length_int);
        
        ++m_ReceivedInitFrameCount;
      }
      
      printf("Received %d out of %d required init frames\n", m_ReceivedInitFrameCount, INIT_FRAME_COUNT);
      
      if(m_ReceivedInitFrameCount == INIT_FRAME_COUNT)
      {
        printf("Received all of %d init frames\n", INIT_FRAME_COUNT);
        m_ModelListener->notifyAllInitFrameReceived(s_UARTFrame); 
        
        /*Set m_ReceivedInitFrameCount back to 0 to make another connection initialization possible after connection deinitialization*/
        m_ReceivedInitFrameCount = 0;
      }
    }
    else
    {
      printf("Wrong frame type for module %d in inactive state\n", module);
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

void Model::setNewValueToSet(const UARTFrameStruct_t & frameStructure)
{
#ifndef SIMULATOR
  uint8_t UART_ValueToTransmit[FRAME_SIZE] = {0};
  
  convertUARTstructToFrameTable(frameStructure, UART_ValueToTransmit);
  
  xQueueSendToBack(msgQueueUARTTransmit, UART_ValueToTransmit, 0);
  
  /*Give semaphore to activate UART_Tx task*/
  xSemaphoreGive(UART_TxSemaphore);
#endif
}
