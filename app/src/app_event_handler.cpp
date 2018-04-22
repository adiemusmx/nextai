#include "app_event_handler.h"
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
	//MapBarDL::ObjectManager::getInstance()->addView(MapBarDL::SURFACE_ID_VIEW, new ViewMousePaint());

	return FALSE;
}

BOOL AppEventHandler::render()
{
	ColorCode color = 0x0000FFFF;
	
	// Point
	Point center = { 600, 100 };
	RENDER_SYSTEM()->drawPoint(center, 4.0f, color);

	// Line
	Point points[10];
	points[0].x = points[0].y = 10;
	for (int32 loopIdx = 1; loopIdx < element_of(points); ++loopIdx)
	{
		points[loopIdx].x = points[loopIdx - 1].x + 10;
		points[loopIdx].y = points[loopIdx - 1].y + 10;
	}
	RENDER_SYSTEM()->drawPolyLine(points, element_of(points), 1.0f, 1, LINE_STYLE_2, color);

	// Polygon
	Point polygonPoint[6];
	polygonPoint[0].x = 300; polygonPoint[0].y = 300;
	polygonPoint[1].x = 400; polygonPoint[1].y = 250;
	polygonPoint[2].x = 400; polygonPoint[2].y = 400;
	polygonPoint[3].x = 350; polygonPoint[3].y = 490;
	polygonPoint[4].x = 300; polygonPoint[4].y = 420;
	polygonPoint[5].x = 250; polygonPoint[5].y = 250;
	color = 0x00FF00FF;
	RENDER_SYSTEM()->drawPolygon(polygonPoint, element_of(polygonPoint), 1.0f, 1, LINE_STYLE_1, color, MapBarDL::POLYGON_MODE_POINT);

	// Picture
	Rect drawArea = { 300, 300, 600, 600 };
	static MapBarDL::TEXTURE_ID textureId = RENDER_SYSTEM()->allocTexture("res/test.bmp");
	RENDER_SYSTEM()->drawPicture(textureId, drawArea);

	return FALSE;
}

BOOL AppEventHandler::touch(MapBarDL::TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
{
	return FALSE;
}