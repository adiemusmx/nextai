#ifndef _VIEW_MOUSE_PAINT_H_
#define _VIEW_MOUSE_PAINT_H_

#include "trinity/trinity_widget_view.h"

class ViewMousePaint : public NextAI::WidgetView, NextAI::AppEventListener
{
public:
	ViewMousePaint();
	virtual ~ViewMousePaint();

	virtual void drawImpl();

	virtual NextAI::ListenerResult touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[]);
};

#endif // !_VIEW_MOUSE_PAINT_H_