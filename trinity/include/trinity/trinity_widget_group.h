#ifndef _TRINITY_WIDGET_GROUP_H_
#define _TRINITY_WIDGET_GROUP_H_

#include "base/nextai_app.h"
#include "trinity/trinity_widget_object.h"

namespace NextAI
{
	class WidgetObject;

	/*
	* 组队
	*/
	class WidgetGroup
	{
	public:
		WidgetGroup();
		virtual ~WidgetGroup();

		/* 管理成员 */
		bool addMember(std::shared_ptr<WidgetObject> object);
		bool removeMember(std::shared_ptr<WidgetObject> object);

		/* 获得成员数量 */
		virtual size_t getCount();

		/* 取得关联的其他元素 */
		virtual bool getItem(uint32 index, std::shared_ptr<WidgetObject> item);

	private:
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetGroup);

	private:
		/* 成员 */
		std::vector<std::weak_ptr<WidgetObject>> m_members;
	};
}
#endif // !_TRINITY_WIDGET_GROUP_H_