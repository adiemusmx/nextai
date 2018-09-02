#ifndef _TRINITY_WIDGET_GROUP_H_
#define _TRINITY_WIDGET_GROUP_H_

#include "base/nextai_app.h"
#include "base/nextai_object.h"
#include "trinity/trinity_widget_object.h"

namespace NextAI
{
	class WidgetObject;

	/*
	* ���
	*/
	class WidgetGroup : public NiObject
	{
	public:
		WidgetGroup();
		virtual ~WidgetGroup();

		/* �����Ա */
		void addMember(WEAK_PTR<WidgetObject>& object);
		void removeMember(WEAK_PTR<WidgetObject>& object);

		/* ��ó�Ա���� */
		virtual size_t getCount();

		/* ȡ�õ���Ԫ�� */
		virtual WEAK_PTR<WidgetObject>& getItem(int32 index);

	private:
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetGroup);

	private:
		/* ��Ա */
		std::vector<WEAK_PTR<WidgetObject>> m_members;
	};
}
#endif // !_TRINITY_WIDGET_GROUP_H_