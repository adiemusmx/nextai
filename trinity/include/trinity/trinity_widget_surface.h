#ifndef _TRINITY_WIDGET_SURFACE_H_
#define _TRINITY_WIDGET_SURFACE_H_

#include "trinity_widget_object.h"

namespace NextAI
{

enum SURFACE_ID
{
	SURFACE_ID_BASE,			// Background
	SURFACE_ID_VIEW,			// usser view
	SURFACE_ID_ONS,			// ons view
	SURFACE_ID_INTERRUPT,	// interrup view
	SURFACE_ID_MAX
};

class WidgetSurface : public WidgetObject
{
public:
	WidgetSurface(ObjectId id);
	virtual ~WidgetSurface();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetSurface);
};

}

#endif // !_TRINITY_WIDGET_SURFACE_H_