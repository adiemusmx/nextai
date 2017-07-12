#pragma once

namespace Trinity {
class ObjectManager
{
public:
	static ObjectManager* getInstance();

private:
	ObjectManager();
	virtual ~ObjectManager();

	ObjectManager(const ObjectManager&);
	ObjectManager& operator=(const ObjectManager&);


};
}