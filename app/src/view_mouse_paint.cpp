#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "trinity_util_log.h"

using namespace Trinity;

ViewMousePaint::ViewMousePaint() : Trinity::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	m_glLine = new Trinity::GL_Line();
	Trinity::AppService::getInstance()->addEventListener(this);
}

ViewMousePaint::~ViewMousePaint()
{
	Trinity::AppService::getInstance()->removeEventListener(this);
	if (m_glLine != NULL)
		delete(m_glLine);
}

void ViewMousePaint::drawImpl()
{
	// Parent's draw fucntion
	Trinity::WidgetView::drawImpl();

	// Mouse track line
	m_glLine->draw();
}

BOOL ViewMousePaint::touch(Trinity::TouchType touch, int32 touchCount, const int32 touchId[], const Trinity::Point touchPos[])
{
	m_glLine->appendPoint(touchPos[0]);
	return FALSE;
}