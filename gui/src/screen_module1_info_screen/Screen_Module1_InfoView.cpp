#include <gui/screen_module1_info_screen/Screen_Module1_InfoView.hpp>
#include <gui/model/Model.hpp>
#include <string>

#define PAYLOAD_SIZE 10

Screen_Module1_InfoView::Screen_Module1_InfoView()
{
#ifndef SIMULATOR  
  uint8_t vendorStringLength_int = Model::m_vendorStringLength - '0';
  uint8_t typeStringLength_int = Model::m_typeStringLength - '0';
  uint8_t modelStringLength_int = Model::m_modelStringLength - '0';
  uint8_t speedStringLength_int = Model::m_speedStringLength - '0';
  uint8_t versionStringLength_int = Model::m_versionStringLength - '0';
  
  uint16_t vendorStringDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t vendorTypeDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t vendorModelDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t vendorSpeedDisplay[PAYLOAD_SIZE] = { 0 };
  uint16_t vendorVersionDisplay[PAYLOAD_SIZE] = { 0 };
  
  for (int i = 0; i < vendorStringLength_int; i++)
  {
    *(vendorStringDisplay + i) = *(Model::m_vendor + i);
  }
  
  for (int i = 0; i < typeStringLength_int; i++)
  {
    *(vendorTypeDisplay + i) = *(Model::m_type + i);
  }
  
  for (int i = 0; i < modelStringLength_int; i++)
  {
    *(vendorModelDisplay + i) = *(Model::m_model + i);
  }
  
  for (int i = 0; i < speedStringLength_int; i++)
  {
    *(vendorSpeedDisplay + i) = *(Model::m_speed + i);
  }
  
  for (int i = 0; i < versionStringLength_int; i++)
  {
    *(vendorVersionDisplay + i) = *(Model::m_version + i);
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