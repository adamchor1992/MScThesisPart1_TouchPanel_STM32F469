#include <gui/containers/DigitTemplate.hpp>

DigitTemplate::DigitTemplate()
{
  
}

void DigitTemplate::initialize()
{
  DigitTemplateBase::initialize();
}

void DigitTemplate::SetDigitWithComma(int no)
{
  /*Position 0 is reserved for comma '.'*/
  if ( no == 0)
  {
    Unicode::snprintf(textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, "%c", '.');
    return;
  }
  
  /*Subtract 1 to account for position 0 reserved for comma*/
  Unicode::itoa(no - 1, textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, 10);
}

void DigitTemplate::SetDigitWithoutComma(int no)
{
  Unicode::itoa(no, textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, 10);
}