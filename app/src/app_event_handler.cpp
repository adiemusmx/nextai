#include "app_event_handler.h"
#include "trinity_object_manager.h"
#include "view_mouse_paint.h"

BOOL AppEventHandler::initCompleted()
{
	Trinity::ObjectManager::getInstance()->addView(Trinity::SurfaceID_VIEW, new ViewMousePaint());
	return FALSE;
}

BOOL AppEventHandler::touch(Trinity::TouchType touch, int32 touchCount, int32 touchId[], Trinity::Point touchPos[])
{
	return FALSE;
}