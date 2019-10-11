#include <gui/containers/ExponentContainer.hpp>

ExponentContainer::ExponentContainer()
{
  
}

void ExponentContainer::initialize()
{
  ExponentContainerBase::initialize();
}

void ExponentContainer::setNumber(int number, int offset)
{
  switch(number)
  {
  case 0:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 1:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 2:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 3:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 4:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 5:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 6:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 7:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 8:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 9:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 10:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 11:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 12:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 13:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 14:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 15:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 16:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  case 17:
    Unicode::itoa(offset + number, textArea_ExponentBuffer, TEXTAREA_EXPONENT_SIZE, 10);
    break;
  } 
}

