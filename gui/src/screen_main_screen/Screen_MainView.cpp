#include <gui/screen_main_screen/Screen_MainView.hpp>

Screen_MainView::Screen_MainView()
{

}

void Screen_MainView::setupScreen()
{  
#ifndef SIMULATOR
  /*Dim and deactivate Module buttons*/
  if(Model::m_ActiveModule == 1)
  {
    buttonWithLabel_Module1.setAlpha(255);
    buttonWithLabel_Module1.setTouchable(true);
    buttonWithLabel_Module2.setAlpha(100);
    buttonWithLabel_Module2.setTouchable(false);
    Unicode::strncpy(textArea_ActiveModuleBuffer,"Module 1",10);
  }
  else if(Model::m_ActiveModule == 2)
  {
    buttonWithLabel_Module1.setAlpha(100);
    buttonWithLabel_Module1.setTouchable(false);
    buttonWithLabel_Module2.setAlpha(255);
    buttonWithLabel_Module2.setTouchable(true);
    Unicode::strncpy(textArea_ActiveModuleBuffer,"Module 2",10);
  }
  else
  {
    buttonWithLabel_Module1.setAlpha(100);
    buttonWithLabel_Module1.setTouchable(false);
    buttonWithLabel_Module2.setAlpha(100);
    buttonWithLabel_Module2.setTouchable(false);
    Unicode::strncpy(textArea_ActiveModuleBuffer,"None",10);
  }
  
  buttonWithLabel_Module1.invalidate();
  buttonWithLabel_Module2.invalidate();
  textArea_ActiveModule.invalidate();
#endif
}

void Screen_MainView::tearDownScreen()
{
  
}

void Screen_MainView::processInitFrame(UARTFrameStruct_t & s_UARTFrame)
{
#ifndef SIMULATOR
  printf("Processing init frame\n");
  
  switch(s_UARTFrame.module)
  {
  case '1':
    buttonWithLabel_Module1.setAlpha(255);
    buttonWithLabel_Module1.setTouchable(true);
    buttonWithLabel_Module2.setAlpha(100);
    buttonWithLabel_Module2.setTouchable(false);
    
    Unicode::strncpy(textArea_ActiveModuleBuffer,"Module 1",10);
    
    buttonWithLabel_Module1.invalidate();
    buttonWithLabel_Module2.invalidate();
    textArea_ActiveModule.invalidate();
    
    Model::m_ActiveModule = 1;
    printf("Active module %d\n", Model::m_ActiveModule);
    break;
    
    case'2':
      buttonWithLabel_Module1.setAlpha(100);
      buttonWithLabel_Module1.setTouchable(false);
      buttonWithLabel_Module2.setAlpha(255);
      buttonWithLabel_Module2.setTouchable(true);
      
      Unicode::strncpy(textArea_ActiveModuleBuffer,"Module 2",10);
      
      buttonWithLabel_Module1.invalidate();
      buttonWithLabel_Module2.invalidate();
      textArea_ActiveModule.invalidate();
      
      Model::m_ActiveModule = 2;
      printf("Active module %d\n", Model::m_ActiveModule);
      break;
  }
  printf("Init frame processed\n");
#endif
}

void Screen_MainView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}