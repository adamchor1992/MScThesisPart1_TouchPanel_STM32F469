#include <gui/screen_module1_info_screen/Screen_Module1_InfoView.hpp>
#include <string>

#define PAYLOAD_SIZE 10

Screen_Module1_InfoView::Screen_Module1_InfoView()
{
		#ifndef SIMULATOR
  extern uint8_t m_vendor[PAYLOAD_SIZE];
  extern uint8_t m_type[PAYLOAD_SIZE];
  extern uint8_t m_model[PAYLOAD_SIZE];
  extern uint8_t m_speed[PAYLOAD_SIZE];
  extern uint8_t m_version[PAYLOAD_SIZE];
  extern uint8_t m_vendorStringLength;
  extern uint8_t m_typeStringLength;
  extern uint8_t m_modelStringLength;
  extern uint8_t m_speedStringLength;
  extern uint8_t m_versionStringLength;
  
  uint8_t vendorStringLength_int = m_vendorStringLength - '0';
  uint8_t typeStringLength_int = m_typeStringLength - '0';
  uint8_t modelStringLength_int = m_modelStringLength - '0';
  uint8_t speedStringLength_int = m_speedStringLength - '0';
  uint8_t versionStringLength_int = m_versionStringLength - '0';
  
  uint16_t vendorStringDisplay[10] = { 0 };
  uint16_t vendorTypeDisplay[10] = { 0 };
  uint16_t vendorModelDisplay[10] = { 0 };
  uint16_t vendorSpeedDisplay[10] = { 0 };
  uint16_t vendorVersionDisplay[10] = { 0 };
  
  for (int i = 0; i < vendorStringLength_int; i++)
  {
    *(vendorStringDisplay + i) = *(m_vendor + i);
  }
  
  for (int i = 0; i < typeStringLength_int; i++)
  {
    *(vendorTypeDisplay + i) = *(m_type + i);
  }
  
  for (int i = 0; i < modelStringLength_int; i++)
  {
    *(vendorModelDisplay + i) = *(m_model + i);
  }
  
  for (int i = 0; i < speedStringLength_int; i++)
  {
    *(vendorSpeedDisplay + i) = *(m_speed + i);
  }
  
  for (int i = 0; i < versionStringLength_int; i++)
  {
    *(vendorVersionDisplay + i) = *(m_version + i);
  }
  
  Unicode::snprintf(textArea_VendorBuffer, TEXTAREA_VENDOR_SIZE, "%s", vendorStringDisplay);
  textArea_Vendor.invalidate();

  Unicode::snprintf(textArea_TypeBuffer, TEXTAREA_TYPE_SIZE, "%s", vendorTypeDisplay);
  textArea_Type.invalidate();

  Unicode::snprintf(textArea_ModelBuffer, TEXTAREA_MODEL_SIZE, "%s", vendorModelDisplay);
  textArea_Model.invalidate();

  Unicode::snprintf(textArea_SpeedBuffer, TEXTAREA_SPEED_SIZE, "%s", vendorSpeedDisplay);
  textArea_Speed.invalidate();

  Unicode::snprintf(textArea_VersionBuffer, TEXTAREA_VERSION_SIZE, "%s", vendorVersionDisplay);
  textArea_Version.invalidate();
  #endif
}

void Screen_Module1_InfoView::setupScreen()
{
    Screen_Module1_InfoViewBase::setupScreen();
}

void Screen_Module1_InfoView::tearDownScreen()
{
    Screen_Module1_InfoViewBase::tearDownScreen();
}

void Screen_Module1_InfoView::updateCpuUsage(uint8_t value)
{  
  Unicode::snprintf(textArea_CPU_UsageBuffer,4,"%d",value);
  textArea_CPU_Usage.invalidate();
}