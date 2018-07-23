﻿#include "app_event_handler.h"
#include "trinity/trinity_object_manager.h"
#include "view_mouse_paint.h"
#include "render_system/render_system.h"

AppEventHandler* AppEventHandler::getInstance()
{
	static AppEventHandler instance;
	return &instance;
}

BOOL AppEventHandler::initCompleted()
{
	//NextAI::ObjectManager::getInstance()->addView(NextAI::SURFACE_ID_VIEW, new ViewMousePaint());

	return FALSE;
}

BOOL AppEventHandler::render()
{
	NextAI::ColorCode color = 0x0000FFFF;
	
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
	polygonPoint[0].x = 300; polygonPoint[0].y = 300;
	polygonPoint[1].x = 400; polygonPoint[1].y = 250;
	polygonPoint[2].x = 400; polygonPoint[2].y = 400;
	polygonPoint[3].x = 350; polygonPoint[3].y = 490;
	polygonPoint[4].x = 300; polygonPoint[4].y = 420;
	polygonPoint[5].x = 250; polygonPoint[5].y = 250;
	color = 0x00FF00FF;
	RENDER_SYSTEM()->drawPolygon(polygonPoint, element_of(polygonPoint), 1.0f, 1, LINE_STYLE_1, color, NextAI::POLYGON_MODE_POINT);

	// Picture
	NextAI::Rect drawArea = { 600, 0, 900, 300 };
	static NextAI::PICTURE_TEXTURE_ID textureId = RENDER_SYSTEM()->allocPictureTexture(L"test.bmp");
	RENDER_SYSTEM()->drawPicture(textureId, drawArea);

	NextAI::Rect drawArea2 = { 600, 300, 900, 600 };
	static NextAI::PICTURE_TEXTURE_ID textureId2 = RENDER_SYSTEM()->allocPictureTexture(L"test.jpg");
	RENDER_SYSTEM()->drawPicture(textureId2, drawArea2);

	//NextAI::TextTextureInfo text1 = RENDER_SYSTEM()->allocTextTexture(L"Nothing");
	//RENDER_SYSTEM()->drawText(text1, drawArea2);

	//NextAI::Rect drawArea3 = { 700, 300, 900, 600 };
	//NextAI::TextTextureInfo text2 = RENDER_SYSTEM()->allocTextTexture(L"你好");
	//RENDER_SYSTEM()->drawText(text2, drawArea3);

	return FALSE;
}

BOOL AppEventHandler::touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[])
{
	return FALSE;
}