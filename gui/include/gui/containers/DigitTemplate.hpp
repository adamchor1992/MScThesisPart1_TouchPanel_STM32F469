#ifndef DIGITTEMPLATE_HPP
#define DIGITTEMPLATE_HPP

#include <gui_generated/containers/DigitTemplateBase.hpp>

class DigitTemplate : public DigitTemplateBase
{
public:
    DigitTemplate();
    virtual ~DigitTemplate() {}

    virtual void initialize();

	void setDigitWithComma(int no);
	void setDigitWithoutComma(int no);
};

#endif // DIGITTEMPLATE_HPP
