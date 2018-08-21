#include "stdafx.h"
#include "trinity/trinity_widget_group.h"

namespace NextAI 
{
	WidgetGroup::WidgetGroup()
	{

	}

	WidgetGroup::~WidgetGroup()
	{
		std::vector<WidgetObject*>::iterator iter = m_members.begin();
		while (iter != m_members.end())
		{
			ReleaseNiObject(*iter);
			m_members.erase(iter);
			++iter;
		}
	}

	void WidgetGroup::addMember(WidgetObject* object)
	{
		std::vector<WidgetObject*>::iterator iter = std::find(m_members.begin(), m_members.end(), object);
		if (iter == m_members.end())
		{
			m_members.push_back(object);
			AddNiObjectRef(object);
		}
	}

	void WidgetGroup::removeMember(WidgetObject* object)
	{
		std::vector<WidgetObject*>::iterator iter = std::find(m_members.begin(), m_members.end(), object);
		if (iter != m_members.end())
		{
			m_members.erase(iter);
			ReleaseNiObject(object);
		}
	}

	size_t WidgetGroup::getCount()
	{
		return m_members.size();
	}

	WidgetObject* WidgetGroup::getItem(int32 index)
	{
		return m_members[index];
	}
}