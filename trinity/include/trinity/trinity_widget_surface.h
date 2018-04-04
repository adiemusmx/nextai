#ifndef _TRINITY_WIDGET_SURFACE_H_
#define _TRINITY_WIDGET_SURFACE_H_

#include "trinity_widget_object.h"

namespace Trinity
{

enum SurfaceID
{
	SurfaceID_BASE,			// Background
	SurfaceID_VIEW,			// usser view
	SurfaceID_ONS,			// ons view
	SurfaceID_INTERRUPT,	// interrup view
	SurfaceID_MAX
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