#include "widget_object.h"
#include "util_log.h"

namespace Trinity
{

WidgetObject::WidgetObject(ObjectId id)
{
	m_id = id;
	m_area.left = 0;
	m_area.top = 0;
	m_area.right = 0;
	m_area.bottom = 0;
	m_isHitEnable = FALSE;
	m_isHitTrans = TRUE;
	m_visible = FALSE;
	m_needsRefresh = TRUE;
}

WidgetObject::~WidgetObject()
{
	for (auto pObj : m_children)
	{
		delete(pObj);
	}
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
		TRI_WARNING_LOG("Add same object[%d], do you really intended to do this?", child->m_id);
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
		TRI_WARNING_LOG("Can't find object[%d], do you really intended to do this?", child->m_id);
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

BOOL WidgetObject::hit()
{
	for (auto pObj : m_children)
	{
		if (pObj->hit() == FALSE)
		{
			return FALSE;
		}
	}
	return hitImpl();

	// ��ǰ��Ʒ����ʾ�����߲��ɱ����
	if (!m_visible || !m_isHitEnable) return false;

	// ���������ڷ�Χ�ڣ�����Ҫ���д���
	if (!RECT_testPOINT(m_area, point)) return false;

	// �Ӳ�Ʒ��Hit����
	for (std::vector<GL_Object*>::iterator i = m_children.begin(); i != m_children.end(); ++i)
	{
		if (((GL_Object*)*i)->hit(point, hitType))
			return true;
	}

	// ��ǰ��Ʒ��hit����
	if (hitImpl(point, hitType) || !m_isHitTrans)
		return true;
	else
		return false;
}

BOOL WidgetObject::hitImpl()
{
	return TRUE;
}

void WidgetObject::setArea(const RECT& area)
{
	m_area = area;
}

const RECT& WidgetObject::getArea()
{
	return m_area;
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
	m_isHitEnable = hitEnable;
}

BOOL WidgetObject::getHitEnable()
{
	return m_isHitEnable;
}

void WidgetObject::setHitTransEnable(BOOL hitTransEnable)
{
	m_isHitTrans = hitTransEnable;
}

BOOL WidgetObject::getHitTransEnable()
{
	return m_isHitTrans;
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