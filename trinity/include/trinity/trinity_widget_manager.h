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
	 * 控件管理模块 
	 */
	class WidgetManager : AppEventListener
	{
	public:
		/* 单例模式 */
		static WidgetManager* instance();

		/* 初始化和析构 */
		void init();
		void cleanup();

		/* 管理View */
		void addView(SURFACE_ID surface, SMART_PTR<WidgetView>& view);
		void removeView(SURFACE_ID surface, SMART_PTR<WidgetView>& view);

		/* 描画函数 */
		void draw();

		/* 硬件消息 */
		virtual BOOL hardkey(HardkeyID key);

		/* 点击事件 */
		virtual BOOL touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

	private:
		WidgetManager();
		virtual ~WidgetManager();

		/* 禁用拷贝函数 */
		DISABLE_CLASS_COPY(WidgetManager);

		/* 根节点 */
		SMART_PTR<WidgetObject> m_root;
	};
}

#endif // !_TRINITY_WIDGET_MANAGER_H_