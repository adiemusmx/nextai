#ifndef _TRINITY_OBJECT_MANAGER_H_
#define _TRINITY_OBJECT_MANAGER_H_

#include "trinity_widget_object.h"

#define WIDGET_ROOT_ID 1

namespace Trinity
{

class ObjectManager
{
public:
	static ObjectManager* getInstance();

	// Add and remove child
	void addChild(WidgetObject* object);
	void removeChild(WidgetObject* object);

	// Draw function
	void draw();

	// Hit function
	BOOL hit(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2 = { 0, 0 });

private:
	ObjectManager();
	virtual ~ObjectManager();

	// Disable copy constructor
	DISABLE_CLASS_COPY(ObjectManager);

private:
	// Root of the object's tree.
	WidgetObject* m_root;
};
}

#endif // !_TRINITY_OBJECT_MANAGER_H_