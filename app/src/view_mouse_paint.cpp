#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "trinity_util_log.h"

using namespace Trinity;

ViewMousePaint::ViewMousePaint() : Trinity::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	printf("################\n");
	m_glLine = new Trinity::GL_Line();
}

ViewMousePaint::~ViewMousePaint()
{
	printf("################\n");
	if (m_glLine != NULL)
		delete(m_glLine);
}

void ViewMousePaint::drawImpl()
{
	printf("################\n");

	// Parent's draw fucntion
	Trinity::WidgetView::drawImpl();

	// Mouse track line
	m_glLine->draw();
}

BOOL ViewMousePaint::touch(Trinity::TouchType touch, int32 touchCount, int32 touchId[], Trinity::Point touchPos[])
{
	TRI_INFO_LOG("ViewMousePaint touch");
	m_glLine->appendPoint(touchPos[0]);
	return FALSE;
}