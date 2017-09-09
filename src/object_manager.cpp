#include "object_manager.h"

namespace Trinity {
ObjectManager* ObjectManager::getInstance()
{
	static ObjectManager obj;
	return &obj;
}

void ObjectManager::draw()
{

}

BOOL ObjectManager::hit(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2)
{
	return FALSE;
}

ObjectManager::ObjectManager()
{
	// TODO
}

ObjectManager::~ObjectManager()
{
	// TODO
}
}