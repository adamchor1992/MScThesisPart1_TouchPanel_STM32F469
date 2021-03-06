#include <gui/screen_main_screen/Screen_MainView.hpp>
#include <cstring>
#include "BitmapDatabase.hpp"

#ifndef SIMULATOR
#include "stm32469i_discovery.h"
#endif

void Screen_MainView::setupScreen()
{
#ifndef SIMULATOR
  
  char activeModuleString[PAYLOAD_SIZE] = {0};
  
  /*Activate Module buttons of active modules*/
  if(Model::IsModuleActive(ModuleID::MODULE1) == true)
  {
    buttonWithLabel_Module1.setAlpha(255);
    buttonWithLabel_Module1.setTouchable(true);
    buttonWithLabel_Module1.setBitmaps(touchgfx::Bitmap(BITMAP_DC_DC_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_DC_DC_ON_BUTTON_ID));
    
    strcat(activeModuleString, "1 ");
  }
  else
  {
    buttonWithLabel_Module1.setAlpha(100);
    buttonWithLabel_Module1.setTouchable(false);
    buttonWithLabel_Module1.setBitmaps(touchgfx::Bitmap(BITMAP_DC_DC_OFF_BUTTON_ID), touchgfx::Bitmap(BITMAP_DC_DC_OFF_BUTTON_ID));
  }
  
  if(Model::IsModuleActive(ModuleID::MODULE2) == true)
  {
    buttonWithLabel_Module2.setAlpha(255);
    buttonWithLabel_Module2.setTouchable(true);
    buttonWithLabel_Module2.setBitmaps(touchgfx::Bitmap(BITMAP_AC_DC_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_AC_DC_ON_BUTTON_ID));
    
    strcat(activeModuleString, "2 ");
  }
  else
  {
    buttonWithLabel_Module2.setAlpha(100);
    buttonWithLabel_Module2.setTouchable(false);
    buttonWithLabel_Module2.setBitmaps(touchgfx::Bitmap(BITMAP_AC_DC_OFF_BUTTON_ID), touchgfx::Bitmap(BITMAP_AC_DC_OFF_BUTTON_ID));
  }
  
  if(Model::IsModuleActive(ModuleID::MODULE3) == true)
  {
    buttonWithLabel_Module3.setAlpha(255);
    buttonWithLabel_Module3.setTouchable(true);
    buttonWithLabel_Module3.setBitmaps(touchgfx::Bitmap(BITMAP_DC_AC_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_DC_AC_ON_BUTTON_ID));
    
    strcat(activeModuleString, "3 ");
  }
  else
  {
    buttonWithLabel_Module3.setAlpha(100);
    buttonWithLabel_Module3.setTouchable(false);
    buttonWithLabel_Module3.setBitmaps(touchgfx::Bitmap(BITMAP_DC_AC_OFF_BUTTON_ID), touchgfx::Bitmap(BITMAP_DC_AC_OFF_BUTTON_ID));
  }
  
  /*If no modules active*/
  if(Model::IsModuleActive(ModuleID::MODULE1) == false && Model::IsModuleActive(ModuleID::MODULE2) == false && Model::IsModuleActive(ModuleID::MODULE3) == false)
  {
    Unicode::strncpy(textArea_ActiveModuleBuffer,"None", PAYLOAD_SIZE);
  }
  
  strcat(activeModuleString, "\n");
  
  Unicode::strncpy(textArea_ActiveModuleBuffer, activeModuleString, PAYLOAD_SIZE);
  
  buttonWithLabel_Module1.invalidate();
  buttonWithLabel_Module2.invalidate();
  buttonWithLabel_Module3.invalidate();
  textArea_ActiveModule.invalidate();
#endif
}

void Screen_MainView::tearDownScreen()
{
  
}

void Screen_MainView::ClearLeds()
{
#ifndef SIMULATOR
  BSP_LED_Off(LED1);
  BSP_LED_Off(LED2);
  BSP_LED_Off(LED3); 
  BSP_LED_Off(LED4);
#endif
}

void Screen_MainView::ProcessInitPacket(UartPacket& uartPacket)
{
#ifndef SIMULATOR
  printf("Processing init packet\n");
  
  switch(uartPacket.GetModule())
  {
  case ModuleID::MODULE1:
    buttonWithLabel_Module1.setAlpha(255);
    buttonWithLabel_Module1.setTouchable(true);
    buttonWithLabel_Module1.setBitmaps(touchgfx::Bitmap(BITMAP_DC_DC_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_DC_DC_ON_BUTTON_ID));
    
    Model::ActivateModule(ModuleID::MODULE1);
    break;
    
  case ModuleID::MODULE2:
    buttonWithLabel_Module2.setAlpha(255);
    buttonWithLabel_Module2.setTouchable(true);
    buttonWithLabel_Module1.setBitmaps(touchgfx::Bitmap(BITMAP_AC_DC_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_AC_DC_ON_BUTTON_ID));
    
    Model::ActivateModule(ModuleID::MODULE2);
    break;
    
  case ModuleID::MODULE3:
    buttonWithLabel_Module3.setAlpha(255);
    buttonWithLabel_Module3.setTouchable(true);
    buttonWithLabel_Module1.setBitmaps(touchgfx::Bitmap(BITMAP_DC_AC_ON_BUTTON_ID), touchgfx::Bitmap(BITMAP_DC_AC_ON_BUTTON_ID));
    
    Model::ActivateModule(ModuleID::MODULE3);
    break;
  }
  
  buttonWithLabel_Module1.invalidate();
  buttonWithLabel_Module2.invalidate();
  buttonWithLabel_Module3.invalidate();
  textArea_ActiveModule.invalidate();
  
  printf("Init packet processed\n");
  
  setupScreen();
#endif
}

void Screen_MainView::UpdateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}