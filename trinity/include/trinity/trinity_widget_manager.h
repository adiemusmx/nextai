#ifndef _TRINITY_WIDGET_MANAGER_H_
#define _TRINITY_WIDGET_MANAGER_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

#include "trinity_widget_object.h"
#include "trinity_widget_surface.h"
#include "trinity_widget_view.h"
#include "base/nextai_app.h"

namespace NextAI
{
#define WIDGET_MANAGER() NextAI::WidgetManager::instance()

	/* 
	 * �ؼ�����ģ�� 
	 */
	class WidgetManager : AppEventListener
	{
	public:
		/* ����ģʽ */
		static WidgetManager* instance();

		/* ��ʼ�������� */
		void init();
		void cleanup();

		/* ����View */
		void addView(SURFACE_ID surface, SMART_PTR<WidgetView>& view);
		void removeView(SURFACE_ID surface, SMART_PTR<WidgetView>& view);

		/* �軭���� */
		void draw();

		/* Ӳ����Ϣ */
		virtual BOOL hardkey(HardkeyID key);

		/* ����¼� */
		virtual BOOL touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

	private:
		WidgetManager();
		virtual ~WidgetManager();

		/* ���ÿ������� */
		DISABLE_CLASS_COPY(WidgetManager);

		/* ���ڵ� */
		SMART_PTR<WidgetObject> m_root;
	};
}

#endif // !_TRINITY_WIDGET_MANAGER_H_