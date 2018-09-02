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

	void WidgetGroup::addMember(WEAK_PTR<WidgetObject>& object)
	{
		std::vector<WEAK_PTR<WidgetObject>>::iterator iter = std::find(m_members.begin(), m_members.end(), object);
		if (iter == m_members.end())
		{
			m_members.push_back(object);
		}
	}

	void WidgetGroup::removeMember(WEAK_PTR<WidgetObject>& object)
	{
		std::vector<WEAK_PTR<WidgetObject>>::iterator iter = std::find(m_members.begin(), m_members.end(), object);
		if (iter != m_members.end())
		{
			m_members.erase(iter);
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