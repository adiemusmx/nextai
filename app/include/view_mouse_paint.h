#ifndef _VIEW_MOUSE_PAINT_H_
#define _VIEW_MOUSE_PAINT_H_

#include "trinity/trinity_widget_view.h"
#include "trinity/trinity_gl_line.h"

class ViewMousePaint : public MapBarDL::WidgetView, MapBarDL::AppEventListener
{
public:
	ViewMousePaint();
	virtual ~ViewMousePaint();

	virtual void drawImpl();

	virtual BOOL touch(MapBarDL::TouchType touch, int32 touchCount, const int32 touchId[], const MapBarDL::ScreenPoint touchPos[]);

private:
	std::vector<MapBarDL::GL_Line*> m_glLines;
};

#endif // !_VIEW_MOUSE_PAINT_H_