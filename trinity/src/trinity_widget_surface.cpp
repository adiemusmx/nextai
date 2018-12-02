#include "stdafx.h"
#include "trinity/trinity_widget_surface.h"
#include "base/nextai_app.h"

namespace NextAI
{

WidgetSurface::WidgetSurface(ObjectId id): WidgetObject(id)
{
	Rect full = { 0, 0, APP_SERVICE()->getWindowsWidth(), APP_SERVICE()->getWindowsHeight() };
	setArea(full);
}

WidgetSurface::~WidgetSurface()
{

}
}