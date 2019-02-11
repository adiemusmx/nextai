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
	
	bool WidgetGroup::addMember(std::shared_ptr<WidgetObject> object)
	{
		for (auto item : m_members)
		{
			if (!item.expired())
			{
				if (item.lock() == object)
				{
					NEXTAI_TRACE_LOG(L"Add Same Member![{}]", object->getId());
					return false;
				}
			}
		}
		
		m_members.push_back(object);
		return true;
	}
	
	bool WidgetGroup::removeMember(std::shared_ptr<WidgetObject> object)
	{
		for (auto iter = m_members.begin(); iter != m_members.end(); ++iter)
		{
			if (!iter->expired())
			{
				if (iter->lock() == object)
				{
					m_members.erase(iter);
					return true;
				}
			}
		}
		
		NEXTAI_TRACE_LOG(L"Remove Invalidate Member![{}]", object->getId());
		return false;
	}
	
	size_t WidgetGroup::getCount()
	{
		return m_members.size();
	}
	
	bool WidgetGroup::getItem(uint32 index, std::shared_ptr<WidgetObject> item)
	{
		bool ret = false;
		
		if (m_members.size() > index && !m_members[index].expired())
		{
			item = m_members[index].lock();
			ret = true;
		}
		
		return ret;
	}
}