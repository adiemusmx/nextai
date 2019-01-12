#include "stdafx.h"
#include "trinity/trinity_widget_view.h"

namespace NextAI
{

WidgetView::WidgetView(ObjectId id): WidgetObject(id)
{
	Rect full = { 0, 0, (int32)APP_SERVICE()->getWindowsWidth(), (int32)APP_SERVICE()->getWindowsHeight() };
	setDrawableArea(full);
}

WidgetView::~WidgetView()
{

}

}
