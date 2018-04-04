#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "trinity/trinity_util_log.h"
#include "trinity/trinity_widget_picture.h"
#include <algorithm>

using namespace Trinity;

ViewMousePaint::ViewMousePaint() : Trinity::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	Trinity::WidgetPicture* picture = new Trinity::WidgetPicture(1000);
	Rect area = {0, 0, Trinity::AppService::getInstance()->getWindowsWidth(), Trinity::AppService::getInstance()->getWindowsHeight()};
	picture->setPath("res/background.bmp");
	picture->setDrawableArea(area);

	addChild(picture);
	Trinity::AppService::getInstance()->addEventListener(this);
}

ViewMousePaint::~ViewMousePaint()
{
	Trinity::AppService::getInstance()->removeEventListener(this);
	m_glLines.clear();
}

void ViewMousePaint::drawImpl()
{
	// Parent's draw fucntion
	Trinity::WidgetView::drawImpl();

	// Mouse track line
	std::vector<Trinity::GL_Line*>::iterator iter = m_glLines.begin();
	while (iter != m_glLines.end())
	{
		(*iter)->draw();
		++iter;
	}
}

BOOL ViewMousePaint::touch(Trinity::TouchType touch, int32 touchCount, const int32 touchId[], const Trinity::Point touchPos[])
{
	const ColorCode colorCodeTable[] = { 0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0x888888FF };
	static int32 loopIdx = 0;
	static Trinity::GL_Line* glLine = NULL;
	if (touch == TouchType_BEGAN)
	{
		glLine = new Trinity::GL_Line();
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