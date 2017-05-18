#include "TObject.h"
#include <memory.h>
#include "Log.h"

TObject::TObject(TObject* parent, Rect area)
{
	m_id = INVALID_ID;
	memset(m_children, 0x00, sizeof(m_children));

	parent->addChild(this);
	m_parent = parent;

	m_area = area;
	m_isHitEnable = false;
	m_enable = true;
	m_isHitTrans = false;

	return;
}

TObject::~TObject()
{
	m_id = INVALID_ID;
	removeALLChild();

	m_parent = NULL;
	return;
}

const OBJECT_ID TObject::getId()
{
	return m_id;
}

void TObject::setId(OBJECT_ID id)
{
	m_id = id;
	return;
}

TObject* TObject::getObjectById(OBJECT_ID id)
{
	INT32 loopIdx;

	if (INVALID_ID == id) return NULL;

	// 判断当前层次是否查找成功
	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL == m_children[loopIdx])
		{
			break;
		}
		if (m_children[loopIdx]->m_id == id)
		{
			return m_children[loopIdx];
		}
	}

	// 递归判断
	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL == m_children[loopIdx])
		{
			break;
		}

		TObject* result = m_children[loopIdx]->getObjectById(id);
		if (NULL != result)
		{
			return result;
		}
	}

	return NULL;
}

void TObject::draw()
{
	// 本地描画
	drawImpl();

	// 子部品的描画
	INT32 loopIdx;
	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL != m_children[loopIdx])
		{
			m_children[loopIdx]->drawImpl();
		}
	}
	return;
}

void TObject::drawImpl()
{
	// 默认函数，无操作
	return;
}

bool TObject::hit(const Point point, const E_HIT_TYPE hitType)
{
	// 当前部品不显示，或者不可被点击
	if (!m_enable || !m_isHitEnable) return false;

	// 如果点击不在范围内，则不需要进行处理
	if (!m_area.isInArea(point)) return false;

	// 子部品的Hit处理
	INT32 loopIdx;
	for (loopIdx = CHLIDREN_NUM; loopIdx >= 0; --loopIdx)
	{
		if (NULL != m_children[loopIdx])
		{
			if (m_children[loopIdx]->hit(point, hitType))
				return true;
		}
	}

	// 当前部品的hit处理
	if (hitImpl(point, hitType) || m_isHitTrans)
		return true;
	else
		return false;
}

bool TObject::hitImpl(const Point point, const E_HIT_TYPE hitType)
{
	// 默认函数，无操作
	return false;
}

void TObject::setArea(const Rect area)
{
	m_area = area;
	return;
}

const const Rect TObject::getArea()
{
	return m_area;
}

void TObject::addChild(TObject *obj)
{
	INT32 loopIdx;

	if (NULL == obj) return;

	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL == m_children[loopIdx])
		{
			m_children[loopIdx] = obj;
			break;
		}
	}

	if (CHLIDREN_NUM == loopIdx)
	{
		LOG_LEVEL_PRINT(E_LOG_LEVEL_OBJECT_IMP, "Too many children! parent = [%d] child = [%d]", m_id, obj->m_id);
	}
	return;
}

bool TObject::removeChild(OBJECT_ID id)
{
	INT32 loopIdx;

	if (INVALID_ID == id) return false;

	// 判断当前层次是否查找成功
	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL == m_children[loopIdx])
		{
			break;
		}
		if (m_children[loopIdx]->m_id == id)
		{
			delete m_children[loopIdx];
			m_children[loopIdx] = NULL;

			// 向前移动
			INT32 j;
			for (j = loopIdx; j < CHLIDREN_NUM - 1; ++j)
				m_children[j] = m_children[j + 1];

			return true;
		}
	}

	// 递归判断
	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL == m_children[loopIdx])
		{
			break;
		}

		bool result = m_children[loopIdx]->removeChild(id);
		if (NULL != result)
		{
			return result;
		}
	}

	return false;
}

void TObject::removeALLChild()
{
	INT32 loopIdx;

	for (loopIdx = 0; loopIdx < CHLIDREN_NUM; ++loopIdx)
	{
		if (NULL == m_children[loopIdx]) break;
		m_children[loopIdx]->removeALLChild();
		delete m_children[loopIdx];
		m_children[loopIdx] = NULL;
	}
	return;
}

