#ifndef _VIEW_MOUSE_PAINT_H_
#define _VIEW_MOUSE_PAINT_H_

#include "trinity/trinity_widget_view.h"
#include "trinity/trinity_gl_line.h"

class ViewMousePaint : public Trinity::WidgetView, Trinity::AppEventListener
{
public:
	ViewMousePaint();
	virtual ~ViewMousePaint();

	virtual void drawImpl();

	virtual BOOL touch(Trinity::TouchType touch, int32 touchCount, const int32 touchId[], const Trinity::Point touchPos[]);

private:
	std::vector<Trinity::GL_Line*> m_glLines;
};

#endif // !_VIEW_MOUSE_PAINT_H_