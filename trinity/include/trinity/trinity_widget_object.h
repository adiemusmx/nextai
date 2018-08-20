#ifndef _TRINITY_WIDGET_OBJECT_H_
#define _TRINITY_WIDGET_OBJECT_H_

#include "trinity_object_id.h"
#include "base/nextai_app.h"
#include "base/nextai_object.h"
#include "render_system/render_system.h"

typedef unsigned long ObjectId;

namespace NextAI
{

	/* 控件 */
	class WidgetObject : public NiObject
	{
	public:
		/* 构造函数和析构函数 */
		WidgetObject(ObjectId id);
		virtual ~WidgetObject();

		/* 管理子控件 */
		virtual void addChild(WidgetObject* child);
		virtual void removeChild(WidgetObject* child);
		virtual BOOL isChild(WidgetObject* child);

		/* 获得子控件 */
		virtual WidgetObject* getItem(size_t index);
		virtual WidgetObject* operator[](size_t index);
		virtual size_t getItemCount();

		/* 获得ObjectID */
		virtual WidgetObject* getObjectById(ObjectId id);

		/* 描画 */
		virtual void draw();
		virtual void drawImpl();
		virtual void setDrawableArea(const Rect& area);
		virtual const Rect& getDrawableArea();

		/* 点击 */
		virtual BOOL hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual BOOL hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual void setHitableArea(const Rect& area);
		virtual const Rect& getHitableArea();

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
		std::vector<WidgetObject*> m_children;
	};

}
#endif // !_TRINITY_WIDGET_OBJECT_H_