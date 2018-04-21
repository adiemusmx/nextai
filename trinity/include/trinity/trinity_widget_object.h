#ifndef _TRINITY_WIDGET_OBJECT_H_
#define _TRINITY_WIDGET_OBJECT_H_

#include "trinity_object_id.h"
#include "trinity_app_service.h"

typedef unsigned long ObjectId;

namespace MapBarDL
{

// Widget
class WidgetObject
{
public:
	// Constructor and destructor
	WidgetObject(ObjectId id);
	virtual ~WidgetObject();

	// Add and remove child widget.
	virtual void addChild(WidgetObject* child);
	virtual void removeChild(WidgetObject* child);
	virtual BOOL isChild(WidgetObject* child);

	// Get object id.
	virtual WidgetObject* getObjectById(ObjectId id);

	// Drawable
	virtual void draw();
	virtual void drawImpl();
	virtual void setDrawableArea(const Rect& area);
	virtual const Rect& getDrawableArea();

	// Hitable
	virtual BOOL hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
	virtual BOOL hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
	virtual void setHitableArea(const Rect& area);
	virtual const Rect& getHitableArea();

	// Visible
	virtual void setVisible(BOOL visible);
	virtual BOOL getVisible();

	// Hit enable
	virtual void setHitEnable(BOOL hitEnable);
	virtual BOOL getHitEnable();

	// Hit trans enable
	virtual void setHitTransEnable(BOOL hitTransEnable);
	virtual BOOL getHitTransEnable();

	// Need refresh
	virtual void invalidate();
	virtual BOOL isNeedsRefresh();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetObject);

	// Object's id.
	ObjectId m_id;

	// Drawable area
	Rect m_drawableArea;

	// Hitable area
	Rect m_hitableArea;

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