#ifndef _NEXTAI_OBJECT_H_
#define _NEXTAI_OBJECT_H_

#include "base/nextai_basic_types.h"

namespace NextAI
{
	class NiObject
	{
	public:
		/* 构造函数 */
		NiObject()
		{
			m_refCount = 0;
		}
		
		/* 析构函数 */
		virtual ~NiObject() {}

		/* 增加引用 */
		void retain()
		{
			++this->m_refCount;
		}

		/* 释放引用 */
		void release()
		{
			if (this->m_refCount == 1)
			{
				this->m_refCount = 0;
				NiDelete(this);
			}
			else if (this->m_refCount > 1)
			{
				--this->m_refCount;
			}
			else
			{
				assert(this->m_refCount < 1);
			}
		}		

	private:
		/* 禁止拷贝 */
		DISABLE_CLASS_COPY(NiObject);

		/* 引用计数 */
		size_t m_refCount;
	};

	
}

#endif // !_NEXTAI_OBJECT_H_
