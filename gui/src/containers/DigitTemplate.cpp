#include <gui/containers/DigitTemplate.hpp>

DigitTemplate::DigitTemplate()
{

}

void DigitTemplate::initialize()
{
    DigitTemplateBase::initialize();
}

void DigitTemplate::setDigit(int no)
{
	currentDigit = no;

	if (no == 0)
	{
		Unicode::snprintf(textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, "%c", '.');
		return;
	}

	Unicode::itoa(no - 1, textArea_DigitBuffer, TEXTAREA_DIGIT_SIZE, 10);
}

