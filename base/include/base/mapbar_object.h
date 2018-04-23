#ifndef _MAPBAR_OBJECT_H_
#define _MAPBAR_OBJECT_H_

namespace MapBarDL
{
	class MbObject
	{
	public:
		MbObject();
		virtual ~MbObject();
		
		/* ����ռ� */
		void alloc(size_t size);
		size_t getSize() { return m_bufferSize; }		/* �ռ��Сֻ�ܻ�ȡ���޸���ʹ��alloc */

		/* �������ü��� */
		void addRef() { ++m_refCount; }
		void removeRef() { --m_refCount; }
		size_t getRefCount() { return m_refCount; }

		/* �趨����ռ�Ĳ��� */
		void setStep(size_t step) { m_bufferStep = step; }
		size_t getStep() { return m_bufferStep; }

	private:
		MbObject(const MbObject&);
		MbObject& operator=(const MbObject&);

		void recycle(size_t size);

		void* m_buffer;
		size_t m_bufferSize;
		size_t m_bufferStep;	/* Ĭ��1k */
		size_t m_refCount;
	};
}

#endif // !_MAPBAR_OBJECT_H_