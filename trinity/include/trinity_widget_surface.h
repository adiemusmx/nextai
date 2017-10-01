#ifndef _TRINITY_WIDGET_SURFACE_H_
#define _TRINITY_WIDGET_SURFACE_H_

namespace Trinity
{

class WidgetSurface : public WidgetObject
{
public:
	WidgetSurface();
	~WidgetSurface();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetSurface);
}

}

#endif // !_TRINITY_WIDGET_SURFACE_H_