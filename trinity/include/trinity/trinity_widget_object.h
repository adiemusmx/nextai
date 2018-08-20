#ifndef _TRINITY_WIDGET_OBJECT_H_
#define _TRINITY_WIDGET_OBJECT_H_

#include "trinity_object_id.h"
#include "base/nextai_app.h"
#include "base/nextai_object.h"
#include "render_system/render_system.h"

typedef unsigned long ObjectId;

namespace NextAI
{

	/* �ؼ� */
	class WidgetObject : public NiObject
	{
	public:
		/* ���캯������������ */
		WidgetObject(ObjectId id);
		virtual ~WidgetObject();

		/* �����ӿؼ� */
		virtual void addChild(WidgetObject* child);
		virtual void removeChild(WidgetObject* child);
		virtual BOOL isChild(WidgetObject* child);

		/* ����ӿؼ� */
		virtual WidgetObject* getItem(size_t index);
		virtual WidgetObject* operator[](size_t index);
		virtual size_t getItemCount();

		/* ���ObjectID */
		virtual WidgetObject* getObjectById(ObjectId id);

		/* �軭 */
		virtual void draw();
		virtual void drawImpl();
		virtual void setDrawableArea(const Rect& area);
		virtual const Rect& getDrawableArea();

		/* ��� */
		virtual BOOL hit(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual BOOL hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		virtual void setHitableArea(const Rect& area);
		virtual const Rect& getHitableArea();

		/* �Ƿ�ɼ� */
		virtual void setVisible(BOOL visible);
		virtual BOOL getVisible();

		/* ����¼� */
		virtual void setHitEnable(BOOL hitEnable);
		virtual BOOL getHitEnable();

		/* ���͸�� */
		virtual void setHitTransEnable(BOOL hitTransEnable);
		virtual BOOL getHitTransEnable();

		/* �Ƿ���Ҫ����ˢ�� */
		virtual void invalidate();
		virtual BOOL isNeedsRefresh();

		/* �趨��׽Touch�¼� */
		virtual void setCaptureTouch(BOOL isCapture);
		virtual BOOL isCaptureTouch();
		virtual WidgetObject*  getCaptureTouchObject();

	private:
		/* ���ÿ������캯�� */
		DISABLE_CLASS_COPY(WidgetObject);

		/* ���ó��õ�һЩ�������� */
		BOOL operator==(WidgetObject& object);
		BOOL operator!=(WidgetObject& object);
		BOOL operator!();

		/* ΨһID */
		ObjectId m_id;

		/* �軭��� */
		Rect m_drawableArea;

		/* ����¼���� */
		Rect m_hitableArea;
		BOOL m_hitEnable;		// Default[FALSE]: Call hitImpl function.
		BOOL m_hitTransEnable;	// Default[TRUE]: Send hit event to other widget.

		/* �Ƿ�ɼ� */
		BOOL m_visible;			// Default[TRUE]

		/* �Ƿ���Ҫˢ�� */
		BOOL m_needsRefresh;	// Default[TRUE]

		/* �Ƿ�׽����¼��������ǰ��ʼ����TouchBegan��Ϣ��
		 * �����ֱ��End����Ϣ���ᷢ�͸��ÿؼ��� */
		BOOL m_isCaptureTouch;

		/* �ӿؼ� */
		std::vector<WidgetObject*> m_children;
	};

}
#endif // !_TRINITY_WIDGET_OBJECT_H_