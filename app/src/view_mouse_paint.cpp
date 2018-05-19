#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "base/mapbar_log.h"
#include "trinity/trinity_widget_picture.h"
#include <algorithm>

using namespace MapBarDL;

ViewMousePaint::ViewMousePaint() : MapBarDL::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	MapBarDL::WidgetPicture* picture = new MapBarDL::WidgetPicture(1000);
	Rect area = {0, 0, MapBarDL::AppService::getInstance()->getWindowsWidth(), MapBarDL::AppService::getInstance()->getWindowsHeight()};
	picture->setPath("res/background.bmp");
	picture->setDrawableArea(area);

	addChild(picture);
	MapBarDL::AppService::getInstance()->addEventListener(this);
}

ViewMousePaint::~ViewMousePaint()
{
	MapBarDL::AppService::getInstance()->removeEventListener(this);
	m_glLines.clear();
}

void ViewMousePaint::drawImpl()
{
	// Parent's draw fucntion
	MapBarDL::WidgetView::drawImpl();

	// Mouse track line
	std::vector<MapBarDL::GL_Line*>::iterator iter = m_glLines.begin();
	while (iter != m_glLines.end())
	{
		(*iter)->draw();
		++iter;
	}
}

BOOL ViewMousePaint::touch(MapBarDL::TouchType touch, int32 touchCount, const int32 touchId[], const MapBarDL::ScreenPoint touchPos[])
{
	const ColorCode colorCodeTable[] = { 0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0x888888FF };
	static int32 loopIdx = 0;
	static MapBarDL::GL_Line* glLine = NULL;
	if (touch == TouchType_BEGAN)
	{
		glLine = new MapBarDL::GL_Line();
		glLine->setStyle(GL_LINE_STYLE_3);
		glLine->setWidth(3);
		glLine->setStyleFactor(3);
		glLine->setColor(colorCodeTable[loopIdx++ % element_of(colorCodeTable)]);
		glLine->appendPoint(touchPos[0]);
		m_glLines.push_back(glLine);
	}
	else if (touch == TouchType_MOVED)
	{
		glLine->appendPoint(touchPos[0]);
	}
	else
	{
		glLine->appendPoint(touchPos[0]);

	}

	return FALSE;
}