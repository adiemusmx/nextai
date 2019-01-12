#include "stdafx.h"
#include "trinity/trinity_widget_object.h"
#include "base/nextai_log.h"
#include <algorithm>

namespace NextAI 
{

	WidgetObject::WidgetObject(ObjectId id)
	{
		TRINITY_TRACE_LOG("Id[{}]", id);
		m_id = id;

		m_drawableArea = { 0, 0, 0, 0 };
		m_hitableArea = { 0, 0, 0, 0 };

		m_hitEnable = TRUE;
		m_hitTransEnable = TRUE;

		m_visible = TRUE;
		m_needsRefresh = TRUE;

		m_isCaptureTouch = FALSE;
	}

	WidgetObject::~WidgetObject()
	{
		TRINITY_TRACE_LOG("Id[{}]", m_id);
		m_children.clear();
	}

	void WidgetObject::addChild(SMART_PTR<WidgetObject> child)
	{
		if (child == NULL)
		{
			TRINITY_WARN_LOG("Add null pointer object!");
			return;
		}
		auto pObj = std::find(m_children.begin(), m_children.end(), child);
		if (pObj == m_children.end())
		{
			m_children.push_back(child);
		}
		else
		{
			TRINITY_WARN_LOG("Add same object[{}], it's weird.", child->m_id);
		}
	}

	void WidgetObject::removeChild(const SMART_PTR<WidgetObject> child)
	{
		if (child == NULL)
		{
			TRINITY_WARN_LOG("Remove null pointer object!");
			return;
		}
		auto pObj = std::find(m_children.begin(), m_children.end(), child);
		if (pObj != m_children.end())
		{
			m_children.erase(pObj);
		}
		else
		{
			TRINITY_WARN_LOG("Can't find object[{}], it's weird.", child->m_id);
		}
	}

	BOOL WidgetObject::isChild(const SMART_PTR<WidgetObject> child)
	{
		if (child == NULL)
		{
			TRINITY_WARN_LOG("Remove null pointer object!");
			return FALSE;
		}
		auto pObj = std::find(m_children.begin(), m_children.end(), child);
		if (pObj == m_children.end())
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

	SMART_PTR<WidgetObject> WidgetObject::getItem(size_t index)
	{
		return m_children[index];
	}

	SMART_PTR<WidgetObject> WidgetObject::operator[](size_t index)
	{
		return m_children[index];
	}

	size_t WidgetObject::getItemCount()
	{
		return m_children.size();
	}

	WidgetObject* WidgetObject::getObjectById(ObjectId id)
	{
		if (id == m_id)
			return this;

		WidgetObject* ret = NULL;
		for (auto pObj : m_children)
		{
			ret = pObj->getObjectById(id);
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
		if (!m_visible || !m_hitEnable)
			return HitResult::Missed;

		if (!m_hitableArea.testPoint(touchPos[0]))
			return HitResult::Missed;

		for (auto pObj : m_children)
		{
			if (pObj->hit(touch, touchCount, touchId, touchPos) == HitResult::Hit)
				return HitResult::Hit;;
		}

		if ((m_hitEnable && hitImpl(touch, touchCount, touchId, touchPos) == HitResult::Hit) || !m_hitTransEnable)
			return HitResult::Hit;
		else
			return HitResult::Missed;
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

	void WidgetObject::setVisible(BOOL visible)
	{
		m_visible = visible;
	}

	BOOL WidgetObject::getVisible()
	{
		return m_visible;
	}

	void WidgetObject::setHitEnable(BOOL hitEnable)
	{
		m_hitEnable = hitEnable;
	}

	BOOL WidgetObject::getHitEnable()
	{
		return m_hitEnable;
	}

	void WidgetObject::setHitTransEnable(BOOL hitTransEnable)
	{
		m_hitTransEnable = hitTransEnable;
	}

	BOOL WidgetObject::getHitTransEnable()
	{
		return m_hitTransEnable;
	}

	void WidgetObject::invalidate()
	{
		m_needsRefresh = TRUE;
	}

	BOOL WidgetObject::isNeedsRefresh()
	{
		return m_needsRefresh;
	}

	void WidgetObject::setCaptureTouch(BOOL isCapture)
	{
		m_isCaptureTouch = isCapture;
	}

	BOOL WidgetObject::isCaptureTouch()
	{
		return m_isCaptureTouch;
	}

	WidgetObject* WidgetObject::getCaptureTouchObject()
	{
		WidgetObject* ret = NULL;

		if (m_isCaptureTouch == TRUE)
		{
			ret = this;
		}
		else
		{
			for (auto pObj : m_children)
			{
				ret = pObj->getCaptureTouchObject();
				if (ret != NULL)
					break;
			}
		}

		return ret;
	}
}