#pragma once

class ObjectManager
{
public:
	static ObjectManager* getInstance();

private:
	ObjectManager();
	~ObjectManager();

	D_CLASS_DISABLE_COPY(ObjectManager);
}