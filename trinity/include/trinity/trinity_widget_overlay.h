#ifndef _TRINITY_WIDGET_OVERLAY_H_
#define _TRINITY_WIDGET_OVERLAY_H_

namespace NextAI
{

class WidgetOverlay : public WidgetObject
{
public:
	WidgetOverlay();
	virtual ~WidgetOverlay();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetOverlay);
};

}

#endif // !_TRINITY_WIDGET_OVERLAY_H_