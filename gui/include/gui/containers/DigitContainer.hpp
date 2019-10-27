#ifndef DIGITCONTAINER_HPP
#define DIGITCONTAINER_HPP

#include <gui_generated/containers/DigitContainerBase.hpp>

class DigitContainer : public DigitContainerBase
{
public:
    DigitContainer();
    virtual ~DigitContainer() {}

    virtual void initialize();

	virtual void scrollWheel_Digit10UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit9UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit8UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit7UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit6UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit5UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit4UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit3UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit2UpdateItem(DigitTemplate& item, int16_t itemIndex);
	virtual void scrollWheel_Digit1UpdateItem(DigitTemplate& item, int16_t itemIndex);

	int* getValueTable() { return valueTable; }

private:
	int valueTable[10];
};

#endif // DIGITCONTAINER_HPP
