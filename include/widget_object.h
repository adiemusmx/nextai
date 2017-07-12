#pragma once
#include "common_types.h"
#include <vector>

namespace Trinity {

// 对象ID
typedef int32 ObjectId;

class WidgetObject
{
public:
	WidgetObject(ObjectId id);
	virtual ~WidgetObject();

	BOOL operator==(const WidgetObject& obj) { return (m_id == obj.m_id); }

	// 读取ID
	void setId(ObjectId id) { m_id = id; }
	ObjectId getId() { return m_id; }

	// 设定/取得区域
	virtual void setArea(const RECT& area);
	virtual const RECT& getArea();

	// 描画相关
	virtual void draw();
	virtual void drawImpl();

	// 点击相关
	virtual BOOL hit();
	virtual BOOL hitImpl();

	// 是否显示
	virtual void setVisible(BOOL visible);
	virtual BOOL getVisible();

	// 是否支持点击
	virtual void setHitEnable(BOOL hitEnable);
	virtual BOOL getHitEnable();

	// 是否支持点击穿透
	virtual void setHitTransEnable(BOOL hitTransEnable);
	virtual BOOL getHitTransEnable();

	// 子对象相关操作
	void addChild(WidgetObject* child);
	void removeChild(WidgetObject* child);
	BOOL isChild(WidgetObject* child);

	// 以ID进行搜索，包含递归子控件。
	WidgetObject* getObjectById(ObjectId id);

private:
	// 禁止拷贝
	WidgetObject(const WidgetObject& obj);
	WidgetObject& operator=(const WidgetObject& obj);

	// 本控件需要进行刷新
	void invalidate();
	BOOL isNeedsRefresh();

private:
	// 对象唯一ID，用于检索
	ObjectId m_id;

	// 设定控件区域
	RECT m_area;

	// 子对象
	std::vector<WidgetObject*> m_children;

	// 是否处理hit消息
	BOOL m_isHitEnable;

	// 是否传递hit消息
	BOOL m_isHitTrans;

	// 是否能够进行描画
	BOOL m_visible;

	// 是否需要刷新
	BOOL m_needsRefresh;
};

}