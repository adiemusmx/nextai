#ifndef _TRINITY_WIDGET_VIEW_H_
#define _TRINITY_WIDGET_VIEW_H_

#include "trinity_widget_object.h"

namespace NextAI
{

class WidgetView : public WidgetObject
{
public:
	WidgetView(ObjectId id);
	virtual ~WidgetView();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetView);
};

}

#endif // !_TRINITY_WIDGET_VIEW_H_