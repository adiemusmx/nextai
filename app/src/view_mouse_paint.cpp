#include "stdafx.h"
#include "view_mouse_paint.h"
#include "app_object_id.h"
#include "trinity/trinity_widget_picture.h"
#include "trinity/trinity_widget_button.h"

using namespace NextAI;

ViewMousePaint::ViewMousePaint() : NextAI::WidgetView(OBJECT_ID_SCREEN_MOUSE_PAINT)
{
	/*
	 * 不能正确的执行只通过1张图片拆分成4张图片的功能。当前只能正确加载两个Texture，具体的原因不明确
	 */
	APP_SERVICE()->addEventListener(this);
	std::shared_ptr<WidgetPushButton> button = std::make_shared<WidgetPushButton>(10);
	Rect position = { 0, 0, 100, 100 };
	button->setArea(position);
	button->setPath(L"res/button_default.png");
	this->addChild(std::shared_ptr<WidgetObject>(button));
	/*
	std::shared_ptr<WidgetPushButton> button1 = std::make_shared<WidgetPushButton>(10);
	Rect position1 = { 100, 0, 200, 100 };
	button1->setArea(position1);
	button1->setPath(L"res/button_default.png");
	button1->setHitEnable(false);
	this->addChild(std::shared_ptr<WidgetObject>(button1));
	
	std::shared_ptr<WidgetPushButton> button2 = std::make_shared<WidgetPushButton>(10);
	Rect position2 = { 200, 0, 300, 100 };
	button2->setArea(position2);
	button2->setPath(L"res/button_default.png");
	this->addChild(std::shared_ptr<WidgetObject>(button2));
	std::shared_ptr<WidgetCheckButton> button3 = std::make_shared<WidgetCheckButton>(10);
	Rect position3 = { 300, 0, 400, 100 };
	button3->setArea(position3);
	button3->setChecked(true);
	button3->setPath(L"res/button_default.png");
	this->addChild(std::shared_ptr<WidgetObject>(button3));
	*/
}

ViewMousePaint::~ViewMousePaint()
{
	APP_SERVICE()->removeEventListener(this);
}

void ViewMousePaint::drawImpl()
{
	RENDER_SYSTEM()->drawPolyLine(m_mouseTrace, 3, 1, LINE_STYLE_1, PIXEL_COLOR_RED);
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