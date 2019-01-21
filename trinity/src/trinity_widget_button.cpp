#include "stdafx.h"
#include "trinity/trinity_widget_button.h"
#include "trinity/trinity_widget_group.h"
#include "base/nextai_object.h"

namespace NextAI
{
	WidgetButton::WidgetButton(ObjectId id) : WidgetObject(id)
	{
		setHitEnable(TRUE);
		m_status = Status::Normal;
		for (size_t loopIdx = 0; loopIdx < element_of(m_pictures); ++loopIdx)
		{
			m_pictures[loopIdx] = std::shared_ptr<WidgetPicture>(NiNew(WidgetPicture, id));
		}
	}

	WidgetButton::~WidgetButton()
	{
	}

	void WidgetButton::drawImpl()
	{
		m_pictures[(int32)m_status]->drawImpl();
	}

	HitResult WidgetButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_TRACE_LOG("TRINITY", "id[{}] m_status[{}] touch[{}] count[{}] touchPos[{},{}][{},{}]", getId(), m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

		if (m_status == Status::Normal && touch == TouchType_BEGAN)
		{
			m_status = Status::Pressed;
			setCaptureTouch(TRUE);
		}

		else if (m_status == Status::Pressed &&
			(touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			m_status = Status::Normal;
			setCaptureTouch(FALSE);
		}

		else if (m_status == Status::Disabled)
		{
			return HitResult::Missed;
		}

		return HitResult::Hit;
	}

	void WidgetButton::setPath(Status status, const WCHAR* path)
	{
		NEXTAI_INFO_LOG("TRINITY", "id[{}] status[{}] path[{}]", getId(), status, path);
		m_pictures[(int32)status]->setPath(path);
	}

	const WCHAR* WidgetButton::getPath(Status status)
	{
		return m_pictures[(int32)status]->getPath();
	}

	void WidgetButton::setStatus(Status status)
	{
		NEXTAI_INFO_LOG("TRINITY", "id[{}] status[{}]", getId(), status);
		m_status = status;
	}

	WidgetButton::Status WidgetButton::getStatus()
	{
		return m_status;
	}

	void WidgetButton::setDrawableArea(const Rect& area)
	{
		WidgetObject::setDrawableArea(area);

		for (size_t loopIdx = 0; loopIdx < element_of(m_pictures); ++loopIdx)
		{
			m_pictures[loopIdx]->setDrawableArea(area);
		}
	}

	WidgetPushButton::WidgetPushButton(ObjectId id) : WidgetButton(id)
	{

	}

	WidgetPushButton::~WidgetPushButton()
	{

	}

	WidgetRadioButton::WidgetRadioButton(ObjectId id) : WidgetButton(id)
	{
		m_check = FALSE;
		m_group = NULL;
	}

	WidgetRadioButton::~WidgetRadioButton()
	{
	}

	HitResult WidgetRadioButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_TRACE_LOG("TRINITY", "id[{}] m_status[{}] touch[{}] count[{}] touchPos[{},{}][{},{}]", getId(), m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

		if (m_status == Status::Normal && touch == TouchType_BEGAN)
		{
			m_status = Status::Pressed;
			setCaptureTouch(TRUE);
		}

		else if (m_status == Status::Pressed &&
			(touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			if (m_check == FALSE)
			{
				setChecked();
			}
			setCaptureTouch(FALSE);
		}

		else if (m_status == Status::Selected && touch == TouchType_BEGAN)
		{
			m_status = Status::Pressed;
			setCaptureTouch(TRUE);
		}

		else if (m_status == Status::Disabled)
		{
			return HitResult::Missed;
		}

		return HitResult::Hit;
	}

	void WidgetRadioButton::setChecked()
	{
		NEXTAI_TRACE_LOG("TRINITY", "id[{}]", getId());

		if (m_group != NULL)
		{
			for (size_t loopIdx = 0; loopIdx < m_group->getCount(); ++loopIdx)
			{
				WidgetRadioButton* button = (WidgetRadioButton*)(std::shared_ptr<WidgetObject>(m_group->getItem(loopIdx))).get();
				BOOL isChecked = (button == this);
				button->m_check = isChecked;
				button->m_status = isChecked ? Status::Selected : Status::Normal;
			}
		}
		else
		{
			NEXTAI_WARN_LOG("TRINITY", "id[{}] button's group is NULL.", getId());
		}
	}

	WidgetCheckButton::WidgetCheckButton(ObjectId id) : WidgetButton(id)
	{
		m_check = FALSE;
	}
	
	WidgetCheckButton::~WidgetCheckButton()
	{

	}

	HitResult WidgetCheckButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_TRACE_LOG("TRINITY", "id[{}] m_status[{}] touch[{}] count[{}] touchPos[{},{}][{},{}]", getId(), m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

		if (m_status == Status::Normal && touch == TouchType_BEGAN)
		{
			m_status = Status::Pressed;
			setCaptureTouch(TRUE);
		}

		else if (m_status == Status::Pressed &&
			(touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			m_check = !m_check;
			m_status = m_check ? Status::Selected : Status::Normal;
			setCaptureTouch(FALSE);
		}

		else if (m_status == Status::Selected && touch == TouchType_BEGAN)
		{
			m_status = Status::Pressed;
			setCaptureTouch(TRUE);
		}

		else if (m_status == Status::Disabled)
		{
			return HitResult::Missed;
		}

		return HitResult::Hit;
	}
}

std::wostream& operator<<(std::wostream& os, NextAI::WidgetButton::Status mode)
{
	switch (mode)
	{
	case NextAI::WidgetButton::Status::Normal:
		os << L"WidgetButton::Status::Normal";
		break;
	case NextAI::WidgetButton::Status::Pressed:
		os << L"WidgetButton::Status::Pressed";
		break;
	case NextAI::WidgetButton::Status::Selected:
		os << L"WidgetButton::Status::Selected";
		break;
	case NextAI::WidgetButton::Status::Disabled:
		os << L"WidgetButton::Status::Disabled";
		break;
	default:
		os << L"WidgetButton::Status::Unknown";
		break;
	}
	return os;
}