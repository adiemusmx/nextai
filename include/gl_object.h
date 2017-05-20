#pragma once

#include "common_types.h"
#include "common_define.h"
#include <vector>

// ObjectId用于标记唯一ObjectID
typedef long OBJECT_ID;

#define INVALID_OBJECT_ID (-1)

namespace Trinity {

	class GL_Object {
	public:
		GL_Object(GL_Object *parent);
		virtual ~GL_Object();

		// ID
		const OBJECT_ID getId();
		void setId(OBJECT_ID id);
		GL_Object *getObjectById(OBJECT_ID id);

		// 描画
		virtual void draw();
		virtual void drawImpl();

		// 点击函数，返回值用于判断是否需要其他部品继续处理该压下
		virtual BOOL hit(const POINT& point, const E_HIT_TYPE hitType);
		virtual BOOL hitImpl(const POINT& point, const E_HIT_TYPE hitType);

		// 控件位置
		virtual void setArea(const RECT& area);
		virtual const RECT& getArea();

	private:
		CLASS_disableCopy(GL_Object);

		// 追加子控件
		void addChild(GL_Object *id);

		// 删除子控件
		void removeChild(OBJECT_ID id);

	private:
		// ID
		OBJECT_ID m_id;

		// 父控件
		GL_Object* m_parent;

		// 子控件
		std::vector<GL_Object*> m_children;

		// 控件的区域
		RECT m_area;

		// 是否处理hit消息
		BOOL m_isHitEnable;

		// 是否能够进行描画
		BOOL m_enable;

		// 是否传递hit消息
		BOOL m_isHitTrans;
	};
}