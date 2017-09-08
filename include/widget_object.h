#pragma once

#include "common_types.h"

typedef int32 ObjectId;

namespace Trinity {

// Gesture type
// 1. Single Down -> Single Up / Single Cancel
// 2. Single Down -> Single Long -> Single Long Up / Single Cancel
// 3. Single Down -> Single Long -> Single Repeat -> ... -> Single Repeat -> Single Long Up / Single Cancel
// 4. Single Down -> Double Begin -> Double End / Double Cancel
// 5. Single Down -> Double Begin -> Double Move -> ... -> Double Move -> Double End / Double Cancel
enum HIT_EVENT_TYPE
{
	HIT_EVENT_TYPE_SINGLE_DOWN,		// Down event
	HIT_EVENT_TYPE_SINGLE_UP,		// Up event
	HIT_EVENT_TYPE_SINGLE_LONG,		// Long event
	HIT_EVENT_TYPE_SINGLE_LONG_UP,	// Long up event
	HIT_EVENT_TYPE_SINGLE_REPEAT,	// Repeat event
	HIT_EVENT_TYPE_SINGLE_CANCEL,	// Cancel event

	HIT_EVENT_TYPE_DOUBLE_BEGIN,	// Double fingers begin event
	HIT_EVENT_TYPE_DOUBLE_MOVE,		// Double fingers move event
	HIT_EVENT_TYPE_DOUBLE_END,		// Double fingers end event
	HIT_EVENT_TYPE_DOUBLE_CANCEL,	// Double fingers cancel event

	HIT_EVENT_TYPE_MAX
};

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
	BOOL hit(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2 = { 0, 0 });
	BOOL hitImpl(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2);
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

	// Copy construct & operator = are disabled.
	WidgetObject(const WidgetObject& obj) {}
	WidgetObject& operator=(const WidgetObject& obj) {}

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