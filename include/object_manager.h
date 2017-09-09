#pragma once

#include "widget_object.h"



namespace Trinity {

class ObjectManager
{
public:
	static ObjectManager* getInstance();

	// Draw function
	void draw();

	// Hit function
	BOOL hit(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2 = { 0, 0 });

private:
	ObjectManager();
	virtual ~ObjectManager();

	ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);

private:
	// Root of the object's tree.
	WidgetObject* m_root;
};
}