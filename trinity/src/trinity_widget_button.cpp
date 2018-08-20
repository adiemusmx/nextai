#include "stdafx.h"
#include "trinity/trinity_widget_button.h"
#include "trinity/trinity_widget_group.h"
#include "base/nextai_object.h"

namespace NextAI
{
	WidgetButton::WidgetButton(ObjectId id) : WidgetObject(id)
	{
		m_status = Status::Normal;
		for (int32 loopIdx = 0; loopIdx < element_of(m_pictures); ++loopIdx)
		{
			m_pictures[loopIdx] = NiNew(WidgetPicture, id);
		}
		m_group = NULL;
	}

	WidgetButton::~WidgetButton()
	{
		for (int32 loopIdx = 0; loopIdx < element_of(m_pictures); ++loopIdx)
		{
			if (m_pictures[loopIdx] != NULL)
			{
				NiDelete(m_pictures[loopIdx]);
				m_pictures[loopIdx] = NULL;
			}
		}

		if (m_group != NULL)
		{
			m_group->removeMember(this);
			ReleaseNiObject(m_group);
			m_group = NULL;
		}
	}

	void WidgetButton::drawImpl()
	{
		m_pictures[(int32)m_status]->drawImpl();
	}

	BOOL WidgetButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_TRACE_LOG_FLAG("m_status[%d] touch[%d] count[%d] touchPos[%d,%d][%d,%d]", m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

		/* 压下 */
		if (m_status == Status::Normal && touch == TouchType_BEGAN)
		{
			m_status = Status::Pressed;
			setCaptureTouch(TRUE);
		}
		/* 抬起 */
		else if (m_status == Status::Pressed &&
			(touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			m_status = Status::Normal;
			setCaptureTouch(FALSE);
		}
		/* 无效 */
		else if (m_status == Status::Disabled)
		{
			return FALSE;
		}

		return TRUE;
	}

	void WidgetButton::setPath(Status status, const WCHAR* path)
	{
		NEXTAI_INFO_W_LOG(L"status[%d] path[%s]", status, path);
		m_pictures[(int32)m_status]->setPath(path);
	}

	void WidgetButton::setStatus(Status status)
	{
		NEXTAI_INFO_LOG("status[%d]", status);
		m_status = status;
	}

	void WidgetButton::setGroup(WidgetGroup* group)
	{
		NEXTAI_INFO_LOG("group[%p]", group);
		
		if (m_group != NULL)
		{
			m_group->removeMember(this);
			ReleaseNiObject(m_group);
		}
		
		m_group = group;
		AddNiObjectRef(m_group);
		m_group->addMember(this);
	}

	const WCHAR* WidgetButton::getPath(Status status)
	{
		return m_pictures[(int32)status]->getPath();
	}
}