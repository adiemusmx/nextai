#include "object_manager.h"

namespace Trinity {
ObjectManager* ObjectManager::getInstance()
{
	static ObjectManager obj;
	return &obj;
}

void ObjectManager::addChild(WidgetObject* object)
{
	m_root->addChild(object);
}

void ObjectManager::removeChild(WidgetObject* object)
{
	m_root->removeChild(object);
}

void ObjectManager::draw()
{
	m_root->draw();
}

BOOL ObjectManager::hit(HIT_EVENT_TYPE hitEventType, POINT finger1, POINT finger2)
{
	m_root->hit(hitEventType, finger1, finger2);
	return FALSE;
}

ObjectManager::ObjectManager()
{
	m_root = new WidgetObject(WIDGET_ROOT_ID);
}

ObjectManager::~ObjectManager()
{
	delete(m_root);
}
}