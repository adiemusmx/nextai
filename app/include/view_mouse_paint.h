#ifndef _VIEW_MOUSE_PAINT_H_
#define _VIEW_MOUSE_PAINT_H_

#include "trinity_widget_view.h"
#include "trinity_gl_line.h"

class ViewMousePaint : public Trinity::WidgetView, Trinity::AppEventListener
{
public:
	ViewMousePaint();
	virtual ~ViewMousePaint();

	virtual void drawImpl();

	virtual BOOL touch(Trinity::TouchType touch, int32 touchCount, int32 touchId[], Trinity::Point touchPos[]);

private:
	Trinity::GL_Line* m_glLine;
};

#endif // !_VIEW_MOUSE_PAINT_H_