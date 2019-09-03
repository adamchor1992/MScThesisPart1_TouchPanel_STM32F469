#ifndef TEMPLATE_VIEW_HPP
#define TEMPLATE_VIEW_HPP

#include <mvp/View.hpp>
#include <gui_generated/template_screen/TemplateViewBase.hpp>
#include <gui/template_screen/TemplatePresenter.hpp>
#include <gui/common/Graph.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>

using namespace touchgfx;

/**
* The View for a template screen. In the MVP paradigm, the view is a
* passive interface that only displays the user interface and routes
* any events from the user interface to the presenter. Normally it is the
* responsibility of the presenter to act upon those events.
*
* By deriving from View, this class has a presenter pointer, which is configured
* automatically.
*/
class TemplateView : public TemplateViewBase
{
public:
  /**
  * The view constructor. Note that the constructor runs before the new screen is
  * completely initialized, so do not place code here that causes anything to be drawn.
  * Use the setupScreen function instead.
  */
  TemplateView()
  {

  }
  virtual ~TemplateView() { }
  
  /**
  * This function is called automatically when the view is activated. This function
  * should add widgets to the root container, configure widget sizes and event
  * callbacks, et cetera.
  */
  virtual void setupScreen();
  
  /**
  * This function is called automatically when transitioning to a different screen
  * than this one. Can optionally be used to clean up.
  */
  virtual void tearDownScreen();
  
  virtual void handleTickEvent();
  
  virtual void addNewValueToGraphFromUART(UARTFrameStruct_t & s_UARTFrame);
  void updateCpuUsage(uint8_t value);
  
private:
  int tickCounter;
  uint8_t length_int;
  int16_t value_int;
  bool isNegative;
  
  Image background;
  Graph graph;
};

#endif // TEMPLATE_VIEW_HPP
