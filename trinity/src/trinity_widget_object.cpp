#include "stdafx.h"
#include "trinity/trinity_widget_object.h"
#include "trinity/trinity_widget_manager.h"
#include <algorithm>

namespace NextAI
{

	WidgetObject::WidgetObject(ObjectId id)
	{
		NEXTAI_TRACE_LOG(L"Id[{}]", id);
		m_id = id;
		m_drawableArea = { 0, 0, 0, 0 };
		m_hitableArea = { 0, 0, 0, 0 };
		m_hitEnable = true;
		m_hitTransEnable = true;
		m_visible = true;
		m_needsRefresh = true;
		m_isCaptureTouch = false;
	}
	
	WidgetObject::~WidgetObject()
	{
		NEXTAI_TRACE_LOG(L"Id[{}]", m_id);
		m_children.clear();
	}
	
	void WidgetObject::addChild(std::shared_ptr<WidgetObject> child)
	{
		if (child == NULL)
		{
			NEXTAI_WARN_LOG(L"Add null pointer object!");
			return;
		}
		
		auto pObj = std::find(m_children.begin(), m_children.end(), child);
		
		if (pObj == m_children.end())
		{
			m_children.push_back(child);
		}
		else
		{
			NEXTAI_WARN_LOG(L"Add same object[{}], it's weird.", child->m_id);
		}
	}
	
	void WidgetObject::removeChild(const std::shared_ptr<WidgetObject> child)
	{
		if (child == NULL)
		{
			NEXTAI_WARN_LOG(L"Remove null pointer object!");
			return;
		}
		
		auto pObj = std::find(m_children.begin(), m_children.end(), child);
		
		if (pObj != m_children.end())
		{
			m_children.erase(pObj);
		}
		else
		{
			NEXTAI_WARN_LOG(L"Can't find object[{}], it's weird.", child->m_id);
		}
	}
	
	bool WidgetObject::isChild(const std::shared_ptr<WidgetObject> child)
	{
		if (child == NULL)
		{
			NEXTAI_WARN_LOG(L"Remove null pointer object!");
			return false;
		}
		
		auto pObj = std::find(m_children.begin(), m_children.end(), child);
		
		if (pObj == m_children.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	std::shared_ptr<WidgetObject> WidgetObject::getItem(size_t index)
	{
		return m_children[index];
	}
	
	std::shared_ptr<WidgetObject> WidgetObject::operator[](size_t index)
	{
		return m_children[index];
	}
	
	size_t WidgetObject::getItemCount()
	{
		return m_children.size();
	}
	
	WidgetObject* WidgetObject::find(ObjectId id)
	{
		if (id == m_id)
		{ return this; }
		
		WidgetObject* ret = NULL;
		
		for (auto pObj : m_children)
		{
			ret = pObj->find(id);
			
			if (ret != NULL)
			{
				break;
			}
		}
		
		return ret;
	}
	
	void WidgetObject::draw()
	{
		for (auto pObj : m_children)
		{
			pObj->draw();
		}
		
		drawImpl();
	}
	
	void WidgetObject::drawImpl()
	{
		// TODO
	}
	
	void WidgetObject::setDrawableArea(const Rect& area)
	{
		m_drawableArea = area;
	}
	
	const Rect& WidgetObject::getDrawableArea()
	{
		return m_drawableArea;
	}
	
	HitResult WidgetObject::hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		/* 如果基类无法看见，则不进行处理 */
		if (!m_visible)
		{
			return HitResult::Missed;
		}
		
		/* 如果点击事件不在控件范围内，则不进行处理 */
		if (!m_hitableArea.testPoint(touchPos[0]))
		{
			return HitResult::Missed;
		}
		
		/* 优先子对象进行处理 */
		for (auto pObj : m_children)
		{
			if (pObj->hit(touch, touchCount, touchId, touchPos) == HitResult::Hit)
			{
				return HitResult::Hit;
			}
		}
		
		/* 如果当前对象不可被点击，则不进行处理 */
		if ((m_hitEnable && hitImpl(touch, touchCount, touchId, touchPos) == HitResult::Hit) || !m_hitTransEnable)
		{
			return HitResult::Hit;
		}
		else
		{
			return HitResult::Missed;
		}
	}
	
	HitResult WidgetObject::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		// TODO
		return HitResult::Missed;
	}
	
	void WidgetObject::setHitableArea(const Rect& area)
	{
		m_hitableArea = area;
	}
	
	const Rect& WidgetObject::getHitableArea()
	{
		return m_hitableArea;
	}
	
	void WidgetObject::setVisible(bool visible)
	{
		m_visible = visible;
	}
	
	bool WidgetObject::getVisible()
	{
		return m_visible;
	}
	
	void WidgetObject::setHitEnable(bool hitEnable)
	{
		m_hitEnable = hitEnable;
	}
	
	bool WidgetObject::isHitEnable()
	{
		return m_hitEnable;
	}
	
	void WidgetObject::setHitTransEnable(bool hitTransEnable)
	{
		m_hitTransEnable = hitTransEnable;
	}
	
	bool WidgetObject::isHitTransEnable()
	{
		return m_hitTransEnable;
	}
	
	void WidgetObject::invalidate()
	{
		m_needsRefresh = true;
	}
	
	bool WidgetObject::isNeedsRefresh()
	{
		return m_needsRefresh;
	}
	
	void WidgetObject::setCaptureTouch(bool isCapture)
	{
		m_isCaptureTouch = isCapture;
		
		if (isCapture == true)
		{
			WIDGET_MANAGER()->setTouchCaptureObject(shared_from_this());
		}
		else
		{
			WIDGET_MANAGER()->resetTouchCaptureObject();
		}
	}
	
}