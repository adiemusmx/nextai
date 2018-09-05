#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "base/nextai_log.h"
#include "trinity/trinity_widget_picture.h"
#include <algorithm>

using namespace NextAI;

ViewMousePaint::ViewMousePaint() : NextAI::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	APP_SERVICE()->addEventListener(this);
}

ViewMousePaint::~ViewMousePaint()
{
	APP_SERVICE()->removeEventListener(this);
}

void ViewMousePaint::drawImpl()
{
	RENDER_SYSTEM()->drawPolyLine(m_mouseTrace, 3, 1, LINE_STYLE_1, COLOR_RED);
}

NextAI::ListenerResult ViewMousePaint::touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[])
{
	switch (touch)
	{
	case NextAI::TouchType_BEGAN:
		m_mouseTrace.clear();
		m_mouseTrace.push_back(touchPos[0]);
		break;
	case NextAI::TouchType_MOVED:
	case NextAI::TouchType_ENDED:
		m_mouseTrace.push_back(touchPos[0]);
		break;
	default:
		break;
	}
	return NextAI::ListenerResult::OK;
}