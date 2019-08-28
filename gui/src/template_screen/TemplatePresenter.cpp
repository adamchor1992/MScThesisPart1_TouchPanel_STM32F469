#include <gui/template_screen/TemplateView.hpp>
#include <gui/template_screen/TemplatePresenter.hpp>

TemplatePresenter::TemplatePresenter(TemplateView& v)
: view(v)
{
}

void TemplatePresenter::activate()
{
  
}

void TemplatePresenter::deactivate()
{
  
}

void TemplatePresenter::notifyNewUART_RXParsedFrame(UARTFrameStruct_t s_UARTFrame)
{
  view.addNewValueToGraphFromUART(s_UARTFrame.length, s_UARTFrame.payload);
}

void TemplatePresenter::notifyNewCpuUsageValue(uint8_t value)
{
  view.updateCpuUsage(value);
}

