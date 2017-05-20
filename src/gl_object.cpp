#include "gl_object.h"
#include <memory.h>
#include "log.h"

namespace Trinity {

	GL_Object::GL_Object(GL_Object* parent)
	{
		m_id = INVALID_OBJECT_ID;

		if (parent)
			parent->addChild(this);
		m_parent = parent;

		STRUCT_invalid(&m_area);
		m_isHitEnable = false;
		m_enable = true;
		m_isHitTrans = false;

		return;
	}

	GL_Object::~GL_Object()
	{
		m_children.clear();
	}

	const OBJECT_ID GL_Object::getId()
	{
		return m_id;
	}

	void GL_Object::setId(OBJECT_ID id)
	{
		m_id = id;
		return;
	}

	GL_Object* GL_Object::getObjectById(OBJECT_ID id)
	{
		GL_Object* ret = NULL;
		if (m_id == id) { return this; }
		else {
			for (std::vector<GL_Object*>::iterator i = m_children.begin(); i != m_children.end(); ++i)
			{
				ret = ((GL_Object*)*i)->getObjectById(id);
				if (ret) break;
			}
		}
		return ret;
	}

	void GL_Object::draw()
	{
		// 本地描画
		drawImpl();

		// 子部品的描画
		for (std::vector<GL_Object*>::iterator i = m_children.begin(); i != m_children.end(); ++i)
		{
			((GL_Object*)*i)->draw();
		}
		return;
	}

	void GL_Object::drawImpl()
	{
		// 默认函数，无操作
		return;
	}

	BOOL GL_Object::hit(const POINT& point, const E_HIT_TYPE hitType)
	{
		// 当前部品不显示，或者不可被点击
		if (!m_enable || !m_isHitEnable) return false;

		// 如果点击不在范围内，则不需要进行处理
		if (!RECT_testPOINT(m_area, point)) return false;

		// 子部品的Hit处理
		for (std::vector<GL_Object *>::iterator i = m_children.begin(); i != m_children.end(); ++i)
		{
			if (((GL_Object*)*i)->hit(point, hitType))
				return true;
		}
		
		// 当前部品的hit处理
		if (hitImpl(point, hitType) || !m_isHitTrans)
			return true;
		else
			return false;
	}

	BOOL GL_Object::hitImpl(const POINT& point, const E_HIT_TYPE hitType)
	{
		// 默认函数，无操作
		return false;
	}

	void GL_Object::setArea(const RECT& area)
	{
		m_area = area;
	}

	const RECT& GL_Object::getArea()
	{
		return m_area;
	}

	void GL_Object::addChild(GL_Object *obj)
	{
		if (NULL == obj) return;
		m_children.push_back(obj);
	}

	void GL_Object::removeChild(OBJECT_ID id)
	{
		for (std::vector<GL_Object*>::iterator i = m_children.begin(); i != m_children.end(); ++i) {
			if (((GL_Object*)*i)->getId() == id) {
				m_children.erase(i);
				break;
			}
		}
	}
}