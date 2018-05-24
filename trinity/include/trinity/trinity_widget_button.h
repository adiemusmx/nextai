#ifndef _TRINITY_WIDGET_BUTTON_H_
#define _TRINITY_WIDGET_BUTTON_H_

#include "trinity/trinity_widget_object.h"

namespace NextAI
{

class WidgetButton : public WidgetObject
{
public:
	WidgetButton();
	virtual ~WidgetButton();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetButton);
};

}

#endif // !_TRINITY_WIDGET_BUTTON_H_