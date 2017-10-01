#ifndef _TRINITY_OBJECT_MANAGER_H_
#define _TRINITY_OBJECT_MANAGER_H_

#include "trinity_widget_object.h"
#include "trinity_widget_surface.h"
#include "trinity_widget_view.h"
#include "trinity_app_service.h"

namespace Trinity
{

class ObjectManager : AppEventListener
{
public:
	// Single instance
	static ObjectManager* getInstance();

	// Init/cleanup
	void init();
	void cleanup();

	// Add and remove view
	void addView(SurfaceID surface, WidgetView* view);
	void removeView(SurfaceID surface, WidgetView* view);

	// Draw function
	void draw();

private:
	ObjectManager();
	virtual ~ObjectManager();

	// Disable copy constructor
	DISABLE_CLASS_COPY(ObjectManager);

	// Hardkey
	virtual void hardkey(HardkeyID key);

	// touchCount indicates valid data count of touch.
	// touchId and touchPos has 10 elements.
	virtual void touch(TouchType touch, int32 touchCount, const int32 touchId[], const POINT touchPos[]);

	// Root of the object's tree.
	WidgetSurface* m_surfaces[SurfaceID_MAX];
};
}

#endif // !_TRINITY_OBJECT_MANAGER_H_