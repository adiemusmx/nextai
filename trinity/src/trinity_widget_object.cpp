#include "trinity_widget_object.h"
#include "trinity_util_log.h"
#include <algorithm>

namespace Trinity {

WidgetObject::WidgetObject(ObjectId id)
{
	m_id = id;

	m_drawableArea = { 0, 0, 0, 0 };
	m_hitableArea = { 0, 0, 0, 0 };

	m_hitEnable = FALSE;
	m_hitTransEnable = TRUE;

	m_visible = TRUE;
	m_needsRefresh = TRUE;
}

WidgetObject::~WidgetObject()
{
	m_children.clear();
}

void WidgetObject::addChild(WidgetObject* child)
{
	if (child == NULL)
	{
		TRI_WARNING_LOG("Add null pointer object!");
		return;
	}
	auto pObj = std::find(m_children.begin(), m_children.end(), child);
	if (pObj == m_children.end())
	{
		m_children.push_back(child);
	}
	else
	{
		TRI_WARNING_LOG("Add same object[%lu], it's weird.", child->m_id);
	}
}

void WidgetObject::removeChild(WidgetObject* child)
{
	if (child == NULL)
	{
		TRI_WARNING_LOG("Remove null pointer object!");
		return;
	}
	auto pObj = std::find(m_children.begin(), m_children.end(), child);
	if (pObj != m_children.end())
	{
		m_children.erase(pObj);
	}
	else
	{
		TRI_WARNING_LOG("Can't find object[%lu], it's weird.", child->m_id);
	}
}

BOOL WidgetObject::isChild(WidgetObject* child)
{
	if (child == NULL)
	{
		TRI_WARNING_LOG("Remove null pointer object!");
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

BOOL WidgetObject::hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
{
	if (!m_visible || !m_hitEnable)
		return false;

	if (!RECT_testPOINT(m_hitableArea, touchPos[0]))
		return false;

	for (auto pObj : m_children)
	{
		if (pObj->hit(touch, touchCount, touchId, touchPos) == TRUE)
			return TRUE;
	}

	if (hitImpl(touch, touchCount, touchId, touchPos) || !m_hitTransEnable)
		return TRUE;
	else
		return FALSE;
}

BOOL WidgetObject::hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
{
	// TODO
	return FALSE;
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

}