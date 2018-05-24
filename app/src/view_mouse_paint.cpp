#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "base/nextai_log.h"
#include "trinity/trinity_widget_picture.h"
#include <algorithm>

using namespace NextAI;

ViewMousePaint::ViewMousePaint() : NextAI::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	NextAI::WidgetPicture* picture = new NextAI::WidgetPicture(1000);
	Rect area = {0, 0, NextAI::AppService::getInstance()->getWindowsWidth(), NextAI::AppService::getInstance()->getWindowsHeight()};
	picture->setPath("res/background.bmp");
	picture->setDrawableArea(area);

	addChild(picture);
	NextAI::AppService::getInstance()->addEventListener(this);
}

ViewMousePaint::~ViewMousePaint()
{
	NextAI::AppService::getInstance()->removeEventListener(this);
	m_glLines.clear();
}

void ViewMousePaint::drawImpl()
{
	// Parent's draw fucntion
	NextAI::WidgetView::drawImpl();

	// Mouse track line
	std::vector<NextAI::GL_Line*>::iterator iter = m_glLines.begin();
	while (iter != m_glLines.end())
	{
		(*iter)->draw();
		++iter;
	}
}

BOOL ViewMousePaint::touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[])
{
	const ColorCode colorCodeTable[] = { 0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0x888888FF };
	static int32 loopIdx = 0;
	static NextAI::GL_Line* glLine = NULL;
	if (touch == TouchType_BEGAN)
	{
		glLine = new NextAI::GL_Line();
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