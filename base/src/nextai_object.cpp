#include "base/nextai_object.h"
#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

namespace NextAI
{
	MbObject::MbObject()
	{
		m_buffer = NULL;
		m_bufferSize = 0;
		m_bufferStep = 1000;
		m_refCount = 0;
	}

	MbObject::~MbObject()
	{
		if (m_buffer != NULL)
		{
			MbDeleteArray(m_buffer);
		}
	}

	void MbObject::alloc(size_t size)
	{
		MbAssert(size != 0);

		/* 重新申请空间 */
		if (size > m_bufferSize)
		{
			size_t newSize = ((size / m_bufferStep) + 1) * m_bufferStep;
			if (m_bufferSize < newSize)
			{
				if (m_buffer != NULL)
				{
					MbDeleteArray(m_buffer);
				}
				m_buffer = MbNewArray(CHAR, newSize);
				m_bufferSize = newSize;
			}
		}
		/* 新的空间远小于 */
		else if (size < m_bufferSize / 10 && size > m_bufferStep)
		{
			if (size < m_bufferStep && m_bufferSize != m_bufferStep)
			{
				recycle(m_bufferStep);
			}
			else if (size > m_bufferStep)
			{
				recycle(size);
			}
		}
	}

	void MbObject::recycle(size_t size)
	{
		if (m_buffer != NULL)
		{
			MbDeleteArray(m_buffer);
			m_bufferSize = 0;
			m_buffer = NULL;
		}
		alloc(size);
	}
}