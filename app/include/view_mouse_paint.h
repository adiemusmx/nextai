#ifndef _VIEW_MOUSE_PAINT_H_
#define _VIEW_MOUSE_PAINT_H_

#include "trinity_widget_view.h"

class ViewMousePaint : public Trinity::WidgetView, Trinity::AppEventListener
{
public:
	ViewMousePaint();
	virtual ~ViewMousePaint();

	virtual BOOL touch(Trinity::TouchType touch, int32 touchCount, int32 touchId[], Trinity::Point touchPos[]);
};

#endif // !_VIEW_MOUSE_PAINT_H_