#include "widget_object_manager.h"

namespace Trinity {
ObjectManager* ObjectManager::getInstance()
{
	static ObjectManager obj;
	return &obj;
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