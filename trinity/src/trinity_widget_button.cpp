#include "stdafx.h"
#include "trinity/trinity_widget_button.h"
#include "trinity/trinity_widget_group.h"

namespace NextAI
{
	WidgetButton::WidgetButton(ObjectId id) : WidgetObject(id)
	{
		m_isPressed = false;
		setHitEnable(true);
		setHitTransEnable(false);
		
		for (size_t loopIdx = 0; loopIdx < (int32)Status::Max; ++loopIdx)
		{
			std::shared_ptr<WidgetPicture> pic = std::make_shared<WidgetPicture>(id);
			m_pictures.push_back(pic);
		}
	}
	
	WidgetButton::~WidgetButton()
	{
	}
	
	void WidgetButton::drawImpl()
	{
		Status status = getStatus();
		
		if (status == Status::Normal)
		{
			m_pictures[0]->drawImpl();
		}
		else if (status == Status::Pressed && m_pictures[1]->isValid())
		{
			m_pictures[1]->drawImpl();
		}
		else if(status == Status::Selected && m_pictures[2]->isValid())
		{
			m_pictures[2]->drawImpl();
		}
		else if (status == Status::Disabled && m_pictures[3]->isValid())
		{
			m_pictures[3]->drawImpl();
		}
		else
		{
			m_pictures[0]->drawImpl();
		}
	}
	
	void WidgetButton::setPath(const std::wstring& path)
	{
		NEXTAI_INFO_LOG(L"id[{}] path[{}]", getId(), path);
		WidgetPicture::allocPictures(path, (int32)Status::Max, m_pictures);
	}
	
	void WidgetButton::setPath(Status status, const std::wstring& path)
	{
		NEXTAI_INFO_LOG(L"id[{}] status[{}] path[{}]", getId(), status, path);
		m_pictures[(int32)status]->setPath(path.c_str());
	}
	
	std::wstring WidgetButton::getPath(Status status)
	{
		return m_pictures[(int32)status]->getPath();
	}
	
	WidgetButton::Status WidgetButton::getStatus()
	{
		return isHitEnable() ? (m_isPressed ? Status::Pressed : Status::Normal) : Status::Disabled;
	}
	
	void WidgetButton::setDrawableArea(const Rect& area)
	{
		WidgetObject::setDrawableArea(area);
		
		for (size_t loopIdx = 0; loopIdx < m_pictures.size(); ++loopIdx)
		{
			m_pictures[loopIdx]->setDrawableArea(area);
		}
	}
	
	void WidgetButton::setHitableArea(const Rect& area)
	{
		WidgetObject::setHitableArea(area);
		
		for (size_t loopIdx = 0; loopIdx < m_pictures.size(); ++loopIdx)
		{
			m_pictures[loopIdx]->setHitableArea(area);
		}
	}
	
	WidgetPushButton::WidgetPushButton(ObjectId id) : WidgetButton(id)
	{
	}
	
	WidgetPushButton::~WidgetPushButton()
	{
	}
	
	HitResult WidgetPushButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		Status status = getStatus();
		NEXTAI_TRACE_LOG(L"id[{}] status[{}] touch[{}] count[{}] touchPos[{},{}][{},{}]",
						 getId(), status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);
						 
		if (m_isPressed == false && touch == TouchType_BEGAN)
		{
			m_isPressed = true;
			setCaptureTouch(true);
		}
		else if (m_isPressed == true && (touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			m_isPressed = false;
			setCaptureTouch(false);
		}
		else if (isCaptureTouch() == false)		/* 如果当前不是捕捉Touch的状态，则消息继续让给其他模块进行处理 */
		{
			return HitResult::Missed;
		}
		
		return HitResult::Hit;
	}
	
	WidgetRadioButton::WidgetRadioButton(ObjectId id) : WidgetButton(id)
	{
		m_isChecked = false;
		m_group = NULL;
	}
	
	WidgetRadioButton::~WidgetRadioButton()
	{
	}
	
	HitResult WidgetRadioButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		Status status = getStatus();
		NEXTAI_TRACE_LOG(L"id[{}] status[{}] touch[{}] count[{}] touchPos[{},{}][{},{}]",
						 getId(), status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);
						 
		if (m_isPressed == false && touch == TouchType_BEGAN)
		{
			m_isPressed = true;
			setCaptureTouch(true);
		}
		else if (m_isPressed == true && (touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			m_isPressed = false;
			
			if (m_isChecked == false)
			{
				setChecked(true);
			}
			
			setCaptureTouch(false);
		}
		else if (isCaptureTouch() == false)		/* 如果当前不是捕捉Touch的状态，则消息继续让给其他模块进行处理 */
		{
			return HitResult::Missed;
		}
		
		return HitResult::Hit;
	}
	
	WidgetButton::Status WidgetRadioButton::getStatus()
	{
		return isHitEnable() ? (m_isPressed ? Status::Pressed : (m_isChecked ? Status::Selected : Status::Normal)) : Status::Disabled;
	}
	
	void WidgetRadioButton::setChecked(bool checked)
	{
		NEXTAI_TRACE_LOG(L"id[{}] checked[{}]", getId(), m_isChecked);
		
		if (m_group != NULL)
		{
			for (size_t loopIdx = 0; loopIdx < m_group->getCount(); ++loopIdx)
			{
				std::shared_ptr<WidgetRadioButton> item;
				
				if (m_group->getItem(loopIdx, item))
				{
					if (item->getId() == getId())
					{
						item->m_isChecked = true;
					}
					else
					{
						item->m_isChecked = false;
					}
				}
			}
		}
		else
		{
			NEXTAI_WARN_LOG(L"id[{}] button's group is NULL.", getId());
		}
	}
	
	WidgetCheckButton::WidgetCheckButton(ObjectId id) : WidgetButton(id)
	{
		m_isChecked = false;
	}
	
	WidgetCheckButton::~WidgetCheckButton()
	{
	}
	
	HitResult WidgetCheckButton::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		Status status = getStatus();
		NEXTAI_TRACE_LOG(L"id[{}] status[{}] touch[{}] count[{}] touchPos[{},{}][{},{}]",
						 getId(), status, touch, touchCount, touchPos[0].x, touchPos[0].y, touchPos[1].x, touchPos[1].y);
						 
		if (m_isPressed == false && touch == TouchType_BEGAN)
		{
			m_isPressed = true;
			setCaptureTouch(true);
		}
		else if (m_isPressed == true && (touch == TouchType_CANCELLED || touch == TouchType_ENDED))
		{
			m_isPressed = false;
			setChecked(!m_isChecked);
			setCaptureTouch(false);
		}
		else if (isCaptureTouch() == false)		/* 如果当前不是捕捉Touch的状态，则消息继续让给其他模块进行处理 */
		{
			return HitResult::Missed;
		}
		
		return HitResult::Hit;
	}
	
	WidgetButton::Status WidgetCheckButton::getStatus()
	{
		return isHitEnable() ? (m_isPressed ? Status::Pressed : (m_isChecked ? Status::Selected : Status::Normal)) : Status::Disabled;
	}
	
	void WidgetCheckButton::setChecked(bool checked)
	{
		NEXTAI_TRACE_LOG(L"id[{}] checked[{}]", getId(), checked);
		m_isChecked = checked;
	}
	
}

std::wostream& operator<<(std::wostream& os, NextAI::WidgetButton::Status mode)
{
	switch (mode)
	{
		OUT_STREAM_ENUM_CLASS_CASE(WidgetButton::Status::Normal);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetButton::Status::Pressed);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetButton::Status::Selected);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetButton::Status::Disabled);
	}
	
	return os << L"WidgetButton::Status::Unknown";
}