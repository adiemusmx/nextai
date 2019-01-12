#include "stdafx.h"
#include "trinity/trinity_widget_group.h"

namespace NextAI 
{
	WidgetGroup::WidgetGroup()
	{

	}

	WidgetGroup::~WidgetGroup()
	{
		m_members.clear();
	}

	void WidgetGroup::addMember(std::shared_ptr<WidgetObject>& object)
	{
		std::vector<std::weak_ptr<WidgetObject>>::iterator iter = m_members.begin();
		while (iter != m_members.end())
		{
			WidgetObject* obj = (WidgetObject*)(std::shared_ptr<WidgetObject>(*iter)).get();
			if (obj == object.get())
			{
				TRINITY_TRACE_LOG("Add Same Member![{}]", object->getId());
				break;
			}
			++iter;
		}

		if (iter == m_members.end())
		{
			m_members.push_back(object);
		}
	}

	void WidgetGroup::removeMember(std::shared_ptr<WidgetObject>& object)
	{
		std::vector<std::weak_ptr<WidgetObject>>::iterator iter = m_members.begin();
		while (iter != m_members.end())
		{
			WidgetObject* obj = (WidgetObject*)(std::shared_ptr<WidgetObject>(*iter)).get();
			if (obj == object.get())
			{
				break;
			}
			++iter;
		}

		if (iter != m_members.end())
		{
			m_members.erase(iter);
		}
		else
		{
			TRINITY_TRACE_LOG("Remove Invalidate Member![{}]", object->getId());
		}
	}

	size_t WidgetGroup::getCount()
	{
		return m_members.size();
	}

	std::weak_ptr<WidgetObject> WidgetGroup::getItem(int32 index)
	{
		return m_members[index];
	}
}