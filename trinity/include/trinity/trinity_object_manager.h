#ifndef _TRINITY_OBJECT_MANAGER_H_
#define _TRINITY_OBJECT_MANAGER_H_

#include "base/mapbar_basic_define.h"
#include "base/mapbar_basic_types.h"

#include "trinity_widget_object.h"
#include "trinity_widget_surface.h"
#include "trinity_widget_view.h"
#include "trinity_app_service.h"

namespace MapBarDL
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
	void addView(SURFACE_ID surface, WidgetView* view);
	void removeView(SURFACE_ID surface, WidgetView* view);

	// Draw function
	void draw();

private:
	ObjectManager();
	virtual ~ObjectManager();

	// Disable copy constructor
	DISABLE_CLASS_COPY(ObjectManager);

	// Hardkey
	virtual BOOL hardkey(HardkeyID key);

	// touchCount indicates valid data count of touch.
	// touchId and touchPos has 10 elements.
	virtual BOOL touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

	// Root of the object's tree.
	WidgetSurface* m_surfaces[SURFACE_ID_MAX];
};
}

#endif // !_TRINITY_OBJECT_MANAGER_H_