#include <gui/containers/DigitTemplate.hpp>

DigitTemplate::DigitTemplate()
{

}

void DigitTemplate::initialize()
{
    DigitTemplateBase::initialize();
}

void DigitTemplate::setDigitWithComma(int no)
{
	if ( no == 0)
	{
		Unicode::snprintf(textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, "%c", '.');
		return;
	}

	Unicode::itoa(no - 1, textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, 10);
}

void DigitTemplate::setDigitWithoutComma(int no)
{
	Unicode::itoa(no, textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, 10);
}