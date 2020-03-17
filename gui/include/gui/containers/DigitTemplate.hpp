#pragma once

#include <gui_generated/containers/DigitTemplateBase.hpp>

class DigitTemplate : public DigitTemplateBase
{
public:
  DigitTemplate();
  virtual ~DigitTemplate() override {}
  
  virtual void initialize() override;
  
  void SetDigitWithComma(int no);
  void SetDigitWithoutComma(int no);
};