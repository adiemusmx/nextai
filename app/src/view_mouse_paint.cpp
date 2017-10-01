#include "view_mouse_paint.h"
#include "app_object_id.h"

ViewMousePaint::ViewMousePaint() : Trinity::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{

}

ViewMousePaint::~ViewMousePaint()
{

}

BOOL ViewMousePaint::touch(Trinity::TouchType touch, int32 touchCount, int32 touchId[], Trinity::Point touchPos[])
{
	return FALSE;
}