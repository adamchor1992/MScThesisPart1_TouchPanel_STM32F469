#ifndef DIGITTEMPLATE_HPP
#define DIGITTEMPLATE_HPP

#include <gui_generated/containers/DigitTemplateBase.hpp>

class DigitTemplate : public DigitTemplateBase
{
public:
    DigitTemplate();
    virtual ~DigitTemplate() {}

    virtual void initialize();

	void setDigit(int no);

	int getDigit() { return currentDigit; }

private:
	int currentDigit;
};

#endif // DIGITTEMPLATE_HPP
