#ifndef _NEXTAI_OBJECT_H_
#define _NEXTAI_OBJECT_H_

#include "base/nextai_basic_types.h"

namespace NextAI
{
	class NiObject
	{
		friend NiObject* AllocObject();
		friend void AddReference(NiObject* object);
		friend void ReleaseObject(NiObject* object);

	public:
		NiObject();
		virtual ~NiObject();

		NiObject(const NiObject&);
		NiObject& operator=(const NiObject&);

		size_t m_refCount;
	};

	/* 创建空间 */
#define AllocNiObject(T, ...) (new T(__VA_ARGS__))

	/* 增加引用 */
	inline void AddNiObjectRef(NiObject* object)
	{
		++object->m_refCount;
	}

	/* 释放引用 */
	inline void ReleaseNiObject(NiObject* object)
	{
		if (object->m_refCount == 1)
		{
			NiDelete(object);
		}
		else if (object->m_refCount > 1)
		{
			--object->m_refCount;
		}
		else
		{
			assert(object->m_refCount < 1);
		}
	}
}

#endif // !_NEXTAI_OBJECT_H_
