#ifndef _TRINITY_WIDGET_GROUP_H_
#define _TRINITY_WIDGET_GROUP_H_

#include "base/nextai_app.h"
#include "base/nextai_object.h"
#include "trinity/trinity_widget_object.h"

namespace NextAI
{
	class WidgetObject;

	/*
	* 组队
	*/
	class WidgetGroup : public NiObject
	{
	public:
		WidgetGroup();
		virtual ~WidgetGroup();

		/* 管理成员 */
		void addMember(SMART_PTR<WidgetObject>& object);
		void removeMember(SMART_PTR<WidgetObject>& object);

		/* 获得成员数量 */
		virtual size_t getCount();

		/* 取得单个元素 */
		virtual WEAK_PTR<WidgetObject> getItem(int32 index);

	private:
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetGroup);

	private:
		/* 成员 */
		std::vector<WEAK_PTR<WidgetObject>> m_members;
	};
}
#endif // !_TRINITY_WIDGET_GROUP_H_