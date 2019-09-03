#ifndef TEMPLATE_PRESENTER_HPP
#define TEMPLATE_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class TemplateView;

class TemplatePresenter : public Presenter, public ModelListener
{
public:
  TemplatePresenter(TemplateView& v);
  virtual void notifyNewUART_RX_Parsed_Frame_Graph(UARTFrameStruct_t & s_UARTFrame); 
  void notifyNewCpuUsageValue(uint8_t value);
  
  /**
  * The activate function is called automatically when this screen is "switched in"
  * (ie. made active). Initialization logic can be placed here.
  */
  virtual void activate();
  
  /**
  * The deactivate function is called automatically when this screen is "switched out"
  * (ie. made inactive). Teardown functionality can be placed here.
  */
  virtual void deactivate();
  
  virtual ~TemplatePresenter() {};
  
private:
  TemplatePresenter();
  
  TemplateView& view;
};


#endif // TEMPLATE_PRESENTER_HPP