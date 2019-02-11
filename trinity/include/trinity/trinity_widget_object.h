#ifndef _TRINITY_WIDGET_OBJECT_H_
#define _TRINITY_WIDGET_OBJECT_H_

#include "trinity_object_id.h"
#include "base/nextai_app.h"
#include "render_system/render_system.h"

typedef unsigned long ObjectId;

namespace NextAI
{

	/* 点击结果 */
	enum class HitResult
	{
		Hit = 0,        /* 命中 */
		Missed,         /* 未命中 */
	};
	
	/* 控件 */
	class WidgetObject : public std::enable_shared_from_this<WidgetObject>
	{
	public:
	
		/* 构造函数和析构函数 */
		WidgetObject(ObjectId id);
		virtual ~WidgetObject();
		
		virtual void setId(ObjectId id) { m_id = id; }
		virtual ObjectId getId() { return m_id; }
		
		/* 管理子控件 */
		virtual void addChild(std::shared_ptr<WidgetObject> child);
		virtual void removeChild(const std::shared_ptr<WidgetObject> child);
		virtual bool isChild(const std::shared_ptr<WidgetObject> child);
		
		/* 获得子控件 */
		virtual std::shared_ptr<WidgetObject> getItem(size_t index);
		virtual std::shared_ptr<WidgetObject> operator[](size_t index);
		virtual size_t getItemCount();
		
		/* 获得ObjectID */
		virtual WidgetObject* find(ObjectId id);
		
		/* 语法糖 */
		virtual void setArea(const Rect& area)
		{
			setDrawableArea(area);
			setHitableArea(area);
		}
		
		/* #### 描画相关 #### */
		
		/* 描画 */
		virtual void draw();
		virtual void drawImpl();
		virtual void setDrawableArea(const Rect& area);
		virtual const Rect& getDrawableArea();
		
		/* 是否可见 */
		virtual void setVisible(bool visible);
		virtual bool getVisible();
		
		/* 是否需要进行刷新 */
		virtual void invalidate();
		virtual bool isNeedsRefresh();
		
		/* #### 点击相关 #### */
		
		/* 点击 */
		virtual HitResult hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual void setHitableArea(const Rect& area);
		virtual const Rect& getHitableArea();
		
		/* 点击事件 */
		virtual void setHitEnable(bool hitEnable);
		virtual bool isHitEnable();
		
		/* 点击透过 */
		virtual void setHitTransEnable(bool hitTransEnable);
		virtual bool isHitTransEnable();
		
		/* 设定捕捉Touch事件 */
		virtual void setCaptureTouch(bool isCapture);
		virtual bool isCaptureTouch() { return m_isCaptureTouch; }
		
	private:
	
		/* 禁用拷贝构造函数 */
		DISABLE_CLASS_COPY(WidgetObject);
		
		/* 禁用常用的一些操作符号 */
		bool operator==(WidgetObject& object);
		bool operator!=(WidgetObject& object);
		bool operator!();
		
	private:
	
		ObjectId m_id;				/* 唯一ID */
		std::vector<std::shared_ptr<WidgetObject>> m_children;		/* 子控件 */
		
		/* #### 描画相关 #### */
		bool m_visible;				/* 是否可见，默认值[TRUE] */
		bool m_needsRefresh;		/* 是否需要刷新，默认值[TRUE] */
		Rect m_drawableArea;		/* 描画区域 */
		
		/* #### 点击相关 #### */
		Rect m_hitableArea;			/* 点击区域 */
		bool m_hitEnable;			/* 是否能够点击，默认值[FALSE] */
		bool m_hitTransEnable;		/* 是否能够向子控件传递，默认值[TRUE] */
		bool m_isCaptureTouch;		/* 当前是否捕捉Touch操作 */
	};
	
}
#endif // !_TRINITY_WIDGET_OBJECT_H_