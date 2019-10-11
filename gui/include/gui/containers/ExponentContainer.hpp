#ifndef EXPONENTCONTAINER_HPP
#define EXPONENTCONTAINER_HPP

#include <gui_generated/containers/ExponentContainerBase.hpp>

class ExponentContainer : public ExponentContainerBase
{
public:
    ExponentContainer();
    virtual ~ExponentContainer() {}

    virtual void initialize();
    void setNumber(int number, int offset);
};

#endif // EXPONENTCONTAINER_HPP
