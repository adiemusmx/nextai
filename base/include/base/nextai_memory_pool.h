#ifndef _NEXTAI_MEMORY_POOL_H_
#define _NEXTAI_MEMORY_POOL_H_

#include "base/nextai_basic_types.h"
#include "base/nextai_object.h"

namespace NextAI
{
	void AutoReleasePool_add(NiObject* o);
	void AutoReleasePool_drain();

	void autorelease(NiObject* o)
	{
		AutoReleasePool_add(o);
		o->release();
	}
}

#endif // !_NEXTAI_MEMORY_POOL_H_
