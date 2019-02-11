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
	class WidgetManager : public AppEventListener
	{
	public:
	
		/* 单例模式 */
		static WidgetManager* instance();
		
		/* 初始化和析构 */
		void init();
		void cleanup();
		
		/* 管理View */
		void addView(SurfaceId surface, std::shared_ptr<WidgetView> view);
		void removeView(SurfaceId surface, std::shared_ptr<WidgetView> view);
		
		/* 描画函数 */
		virtual ListenerResult render();
		
		/* 硬件消息 */
		virtual ListenerResult hardkey(HardkeyID key);
		
		/* 点击事件 */
		virtual ListenerResult touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		
		/* 点击事件进行强制捕捉 */
		virtual void setTouchCaptureObject(std::shared_ptr<WidgetObject> obj);
		virtual void resetTouchCaptureObject();
		
	private:
	
		/* 构造函数和析构函数 */
		WidgetManager();
		virtual ~WidgetManager();
		
		/* 禁用拷贝函数 */
		DISABLE_CLASS_COPY(WidgetManager);
		
		/* 根节点 */
		std::shared_ptr<WidgetObject> m_root;
		
		/* 捕捉Touch消息对象 */
		std::weak_ptr<WidgetObject> m_touchCaptureObject;
	};
}

#endif // !_TRINITY_WIDGET_MANAGER_H_