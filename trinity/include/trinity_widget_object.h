#ifndef _TRINITY_WIDGET_OBJECT_H_
#define _TRINITY_WIDGET_OBJECT_H_

#include "trinity_common_types.h"
#include "trinity_common_define.h"
#include "trinity_object_id.h"
#include "trinity_app_service.h"

typedef unsigned long ObjectId;

namespace Trinity
{

// Widget
class WidgetObject
{
public:
	// Constructor and destructor
	WidgetObject(ObjectId id);
	~WidgetObject();

	// Add and remove child widget.
	void addChild(WidgetObject* child);
	void removeChild(WidgetObject* child);
	BOOL isChild(WidgetObject* child);

	// Get object id.
	WidgetObject* getObjectById(ObjectId id);

	// Drawable
	void draw();
	void drawImpl();
	void setDrawableArea(const RECT& area);
	const RECT& getDrawableArea();

	// Hitable
	BOOL hit(TouchType touch, int32 touchCount, const int32 touchId[], const POINT touchPos[]);
	BOOL hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const POINT touchPos[]);
	void setHitableArea(const RECT& area);
	const RECT& getHitableArea();

	// Visible
	void setVisible(BOOL visible);
	BOOL getVisible();

	// Hit enable
	void setHitEnable(BOOL hitEnable);
	BOOL getHitEnable();

	// Hit trans enable
	void setHitTransEnable(BOOL hitTransEnable);
	BOOL getHitTransEnable();

	// Need refresh
	void invalidate();
	BOOL isNeedsRefresh();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetObject);

	// Object's id.
	ObjectId m_id;

	// Drawable area
	RECT m_drawableArea;

	// Hitable area
	RECT m_hitableArea;

	// Hitable properties
	BOOL m_hitEnable;		// Default[FALSE]: Call hitImpl function.
	BOOL m_hitTransEnable;	// Default[TRUE]: Send hit event to other widget.

	// Visible
	BOOL m_visible;			// Default[TRUE]

	// Need refresh flag
	BOOL m_needsRefresh;	// Default[TRUE]

	// Children
	std::vector<WidgetObject*> m_children;
};

}
#endif // !_TRINITY_WIDGET_OBJECT_H_