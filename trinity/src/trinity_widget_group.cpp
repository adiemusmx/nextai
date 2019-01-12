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

	void WidgetGroup::addMember(SMART_PTR<WidgetObject>& object)
	{
		std::vector<WEAK_PTR<WidgetObject>>::iterator iter = m_members.begin();
		while (iter != m_members.end())
		{
			WidgetObject* obj = (WidgetObject*)(SMART_PTR<WidgetObject>(*iter)).get();
			if (obj == object.get())
			{
				TRINITY_TRACE_LOG("Add Same Member![{}]", object.get());
				break;
			}
			++iter;
		}

		if (iter == m_members.end())
		{
			m_members.push_back(object);
		}
	}

	void WidgetGroup::removeMember(SMART_PTR<WidgetObject>& object)
	{
		std::vector<WEAK_PTR<WidgetObject>>::iterator iter = m_members.begin();
		while (iter != m_members.end())
		{
			WidgetObject* obj = (WidgetObject*)(SMART_PTR<WidgetObject>(*iter)).get();
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
			TRINITY_TRACE_LOG("Remove Invalidate Member![{}]", object.get());
		}
	}

	size_t WidgetGroup::getCount()
	{
		return m_members.size();
	}

	WEAK_PTR<WidgetObject>& WidgetGroup::getItem(int32 index)
	{
		return m_members[index];
	}
}