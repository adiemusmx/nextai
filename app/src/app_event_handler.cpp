#include "stdafx.h"
#include "app_event_handler.h"
#include "trinity/trinity_widget_manager.h"
#include "view_mouse_paint.h"
#include "render_system/render_system.h"

AppEventHandler* AppEventHandler::instance()
{
	static AppEventHandler instance;
	return &instance;
}

NextAI::ListenerResult AppEventHandler::initStarted()
{
	WIDGET_MANAGER()->init();
	WIDGET_MANAGER()->addView(NextAI::SurfaceId::View, std::shared_ptr<NextAI::WidgetView>(NiNew(ViewMousePaint)));
	return NextAI::ListenerResult::OK;
}

NextAI::ListenerResult AppEventHandler::initCompleted()
{
	//NextAI::ObjectManager::instance()->addView(NextAI::SurfaceId::View, new ViewMousePaint());
	return NextAI::ListenerResult::OK;
}

NextAI::ListenerResult AppEventHandler::cleanupCompleted()
{
	WIDGET_MANAGER()->cleanup();
	return NextAI::ListenerResult::OK;
}

NextAI::ListenerResult AppEventHandler::render()
{
#if 0
	NextAI::PixelColor color = 0x0000FFFF;
	// Point
	NextAI::Point center = { 600, 100 };
	RENDER_SYSTEM()->drawPoint(center, 4.0f, color);
	// Line
	NextAI::Point points[2];
	points[0].x = points[0].y = 10;
	points[1].x = 500;
	points[1].y = 300;
	RENDER_SYSTEM()->drawPolyLine(points, element_of(points), 1.0f, 1, LINE_STYLE_1, color);
	NextAI::Segment seg;
	seg.start = points[1];
	seg.end = points[0];
	float angel = seg.angel();
	// Polygon
	NextAI::MapPoint polygonPoint[6];
	polygonPoint[0].x = 300;
	polygonPoint[0].y = 300;
	polygonPoint[1].x = 400;
	polygonPoint[1].y = 250;
	polygonPoint[2].x = 400;
	polygonPoint[2].y = 400;
	polygonPoint[3].x = 350;
	polygonPoint[3].y = 490;
	polygonPoint[4].x = 300;
	polygonPoint[4].y = 420;
	polygonPoint[5].x = 250;
	polygonPoint[5].y = 250;
	color = 0x00FF00FF;
	RENDER_SYSTEM()->drawPolygon(polygonPoint, element_of(polygonPoint), 1.0f, 1, LINE_STYLE_1, color, NextAI::POLYGON_MODE_POINT);
	// Picture
	NextAI::Rect drawArea = { 600, 0, 900, 300 };
	PICTURE_TEXTURE_ID textureId = INVALID_TEXTURE_ID;
	RENDER_SYSTEM()->allocPictureTexture(L"res/test.bmp", textureId);
	RENDER_SYSTEM()->drawPicture(textureId, drawArea);
	NextAI::Rect drawArea2 = { 600, 300, 900, 600 };
	PICTURE_TEXTURE_ID textureId2 = INVALID_TEXTURE_ID;
	RENDER_SYSTEM()->allocPictureTexture(L"res/test.jpg", textureId2);
	RENDER_SYSTEM()->drawPicture(textureId2, drawArea2);
	NextAI::Font* font = NextAI::WindowsFont::allocFont(16, "宋体");
	NextAI::ScreenPoint pos = { 600, 300 };
	RENDER_SYSTEM()->drawText(font, pos, PIXEL_COLOR_RED, L"Hello World");
	NextAI::ScreenPoint pos3 = { 630, 330 };
	RENDER_SYSTEM()->drawText(font, pos3, PIXEL_COLOR_RED, "Hello World");
	NextAI::Font* font2 = NextAI::WindowsFont::allocFont(29, "黑体");
	NextAI::ScreenPoint pos2 = { 700, 400 };
	RENDER_SYSTEM()->drawText(font2, pos2, PIXEL_COLOR_BLUE, L"你好");
	std::vector<PICTURE_TEXTURE_ID> textureId;
	
	if (textureId.size() == 0)
	{
		RENDER_SYSTEM()->allocPictureTextureArray(L"res/button_default.png", 4, textureId);
	}
	
	for (int loopIdx = 0; loopIdx < 9; ++loopIdx)
	{
		NextAI::Rect drawArea = { loopIdx * 100, 100, loopIdx * 100 + 100, 200 };
		RENDER_SYSTEM()->drawTexture(loopIdx, drawArea);
	}
	
#endif
	return NextAI::ListenerResult::OK;
}

NextAI::ListenerResult AppEventHandler::touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[])
{
	return NextAI::ListenerResult::OK;
}