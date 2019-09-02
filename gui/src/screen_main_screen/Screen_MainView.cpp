#include <gui/screen_main_screen/Screen_MainView.hpp>

Screen_MainView::Screen_MainView()
{

}

void Screen_MainView::setupScreen()
{
  Screen_MainViewBase::setupScreen();

  extern uint8_t activeModule;

  /*Dim and deactivate Module buttons*/
  if(activeModule == 1)
  {
    buttonWithLabel_Module1.setAlpha(255);
    buttonWithLabel_Module1.setTouchable(true);
    buttonWithLabel_Module2.setAlpha(100);
    buttonWithLabel_Module2.setTouchable(false);
    Unicode::strncpy(textArea_ActiveModuleBuffer,"Module 1",10);
  }
  else if(activeModule == 2)
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
}

void Screen_MainView::tearDownScreen()
{
  Screen_MainViewBase::tearDownScreen();
}

void Screen_MainView::processControlFrame(UARTFrameStruct_t s_UARTFrame)
{
  extern uint8_t activeModule;

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

      activeModule = 1;
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

      activeModule = 2;
      break;
  }
}

void Screen_MainView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}