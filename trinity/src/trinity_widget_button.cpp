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
			m_pictures[loopIdx] = SMART_PTR<WidgetPicture>(NiNew(WidgetPicture, id));
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
		NEXTAI_TRACE_LOG_FLAG("this[%p] m_status[%d] touch[%d] count[%d] touchPos[%d,%d][%d,%d]", this, (int32)m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

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
		NEXTAI_INFO_W_LOG(L"this[%p] status[%d] path[%s]", this, (int32)status, path);
		m_pictures[(int32)status]->setPath(path);
	}

	const WCHAR* WidgetButton::getPath(Status status)
	{
		return m_pictures[(int32)status]->getPath();
	}

	void WidgetButton::setStatus(Status status)
	{
		NEXTAI_INFO_LOG("this[%p] status[%d]", this, (int32)status);
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
		NEXTAI_TRACE_LOG_FLAG("this[%p] m_status[%d] touch[%d] count[%d] touchPos[%d,%d][%d,%d]", this, (int32)m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

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
		NEXTAI_TRACE_LOG_FLAG("this[%p]", this);

		if (m_group != NULL)
		{
			for (size_t loopIdx = 0; loopIdx < m_group->getCount(); ++loopIdx)
			{
				WidgetRadioButton* button = (WidgetRadioButton*)(SMART_PTR<WidgetObject>(m_group->getItem(loopIdx))).get();
				BOOL isChecked = (button == this);
				button->m_check = isChecked;
				button->m_status = isChecked ? Status::Selected : Status::Normal;
			}
		}
		else
		{
			NEXTAI_WARNING_LOG("this[%p] button's group is NULL.", this);
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
		NEXTAI_TRACE_LOG_FLAG("this[%p] m_status[%d] touch[%d] count[%d] touchPos[%d,%d][%d,%d]", this, (int32)m_status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);

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