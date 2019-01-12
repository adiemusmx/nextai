#ifndef _TRINITY_WIDGET_OBJECT_H_
#define _TRINITY_WIDGET_OBJECT_H_

#include "trinity_object_id.h"
#include "base/nextai_app.h"
#include "base/nextai_object.h"
#include "render_system/render_system.h"

typedef unsigned long ObjectId;

namespace NextAI
{
	enum class HitResult
	{
		Hit = 0,		/* 命中 */
		Missed,			/* 未命中 */
	};

	/* 控件 */
	class WidgetObject
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
		virtual BOOL isChild(const std::shared_ptr<WidgetObject> child);

		/* 获得子控件 */
		virtual std::shared_ptr<WidgetObject> getItem(size_t index);
		virtual std::shared_ptr<WidgetObject> operator[](size_t index);
		virtual size_t getItemCount();

		/* 获得ObjectID */
		virtual WidgetObject* getObjectById(ObjectId id);

		/* 描画 */
		virtual void draw();
		virtual void drawImpl();
		virtual void setDrawableArea(const Rect& area);
		virtual const Rect& getDrawableArea();

		/* 点击 */
		virtual HitResult hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual void setHitableArea(const Rect& area);
		virtual const Rect& getHitableArea();

		/* 语法糖 */
		virtual void setArea(const Rect& area)
		{
			setDrawableArea(area);
			setHitableArea(area);
		}

		/* 是否可见 */
		virtual void setVisible(BOOL visible);
		virtual BOOL getVisible();

		/* 点击事件 */
		virtual void setHitEnable(BOOL hitEnable);
		virtual BOOL getHitEnable();

		/* 点击透过 */
		virtual void setHitTransEnable(BOOL hitTransEnable);
		virtual BOOL getHitTransEnable();

		/* 是否需要进行刷新 */
		virtual void invalidate();
		virtual BOOL isNeedsRefresh();

		/* 设定捕捉Touch事件 */
		virtual void setCaptureTouch(BOOL isCapture);
		virtual BOOL isCaptureTouch();
		virtual WidgetObject*  getCaptureTouchObject();

	private:
		/* 禁用拷贝构造函数 */
		DISABLE_CLASS_COPY(WidgetObject);

		/* 禁用常用的一些操作符号 */
		BOOL operator==(WidgetObject& object);
		BOOL operator!=(WidgetObject& object);
		BOOL operator!();

		/* 唯一ID */
		ObjectId m_id;

		/* 描画相关 */
		Rect m_drawableArea;

		/* 点击事件相关 */
		Rect m_hitableArea;
		BOOL m_hitEnable;		// Default[FALSE]: Call hitImpl function.
		BOOL m_hitTransEnable;	// Default[TRUE]: Send hit event to other widget.

		/* 是否可见 */
		BOOL m_visible;			// Default[TRUE]

		/* 是否需要刷新 */
		BOOL m_needsRefresh;	// Default[TRUE]

		/* 是否捕捉点击事件。如果当前开始处理TouchBegan消息，
		 * 则后续直至End的消息都会发送给该控件。 */
		BOOL m_isCaptureTouch;

		/* 子控件 */
		std::vector<std::shared_ptr<WidgetObject>> m_children;
	};

}
#endif // !_TRINITY_WIDGET_OBJECT_H_