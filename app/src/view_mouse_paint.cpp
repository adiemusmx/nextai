#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "base/nextai_log.h"
#include "trinity/trinity_widget_picture.h"
#include <algorithm>

using namespace NextAI;

ViewMousePaint::ViewMousePaint() : NextAI::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{

}

ViewMousePaint::~ViewMousePaint()
{

}

void ViewMousePaint::drawImpl()
{

}

NextAI::ListenerResult ViewMousePaint::touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[])
{
	return NextAI::ListenerResult::OK;
}