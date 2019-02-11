#include "stdafx.h"
#include "trinity/trinity_widget_manager.h"
#include "trinity/trinity_widget_surface.h"

namespace NextAI
{
	WidgetManager* WidgetManager::instance()
	{
		static WidgetManager obj;
		return &obj;
	}
	
	void WidgetManager::init()
	{
		NEXTAI_TRACE_FUNC();
		Rect full = { 0, 0, (int32)APP_SERVICE()->getWindowsWidth(), (int32)APP_SERVICE()->getWindowsHeight() };
		m_root = std::shared_ptr<WidgetObject>(NiNew(WidgetObject, 0));
		m_root->setArea(full);
		m_root->addChild(std::shared_ptr<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_BASE)));
		m_root->addChild(std::shared_ptr<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_VIEW)));
		m_root->addChild(std::shared_ptr<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_ONS)));
		m_root->addChild(std::shared_ptr<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_INTERRUPT)));
		APP_SERVICE()->addEventListener(this);
	}
	
	void WidgetManager::cleanup()
	{
		NEXTAI_TRACE_FUNC();
		APP_SERVICE()->removeEventListener(this);
	}
	
	void WidgetManager::addView(SurfaceId surface, std::shared_ptr<WidgetView> view)
	{
		NEXTAI_INFO_LOG(L"surface[{}] view[{}]", surface, view->getId());
		
		if (surface >= SurfaceId::Base && surface < SurfaceId::Max && view != NULL)
		{ m_root->getItem((size_t)surface)->addChild(std::shared_ptr<WidgetObject>(view)); }
		else
		{ NEXTAI_WARN_LOG(L"Invalid SurfaceId[{}] view[{}]", surface, view); }
	}
	
	void WidgetManager::removeView(SurfaceId surface, std::shared_ptr<WidgetView> view)
	{
		NEXTAI_INFO_LOG(L"surface[{}] view[{}]", surface, view->getId());
		
		if (surface >= SurfaceId::Base && surface < SurfaceId::Max && view != NULL)
		{ m_root->getItem((size_t)surface)->removeChild(view); }
		else
		{ NEXTAI_WARN_LOG(L"Invalid SurfaceId[{}] view[{}]", surface, view->getId()); }
	}
	
	ListenerResult WidgetManager::render()
	{
		size_t loopIdx;
		
		for (loopIdx = 0; loopIdx < (size_t)SurfaceId::Max; ++loopIdx)
		{
			if (m_root->getItem(loopIdx) != NULL)
			{ m_root->getItem(loopIdx)->draw(); }
		}
		
		return ListenerResult::OK;
	}
	
	WidgetManager::WidgetManager()
	{
		NEXTAI_TRACE_FUNC();
		m_root = NULL;
	}
	
	WidgetManager::~WidgetManager()
	{
		NEXTAI_TRACE_FUNC();
	}
	
	ListenerResult WidgetManager::hardkey(HardkeyID key)
	{
		NEXTAI_INFO_LOG(L"key[{}]", key);
		// TODO
		return ListenerResult::OK;
	}
	
	ListenerResult WidgetManager::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_INFO_LOG(L"touch[{}] touchCount[{}] touchId[{}] touchPos[{},{}]", touch, touchCount, touchId[0], touchPos[0].x, touchPos[0].y);
		ListenerResult ret = ListenerResult::OK;
		
		if (!m_touchCaptureObject.expired())
		{
			auto obj = m_touchCaptureObject.lock();
			obj->hitImpl(touch, touchCount, touchId, touchPos);
			ret = ListenerResult::BLOCK_OTHERS;
		}
		else
		{
			for (int32 loopIdx = m_root->getItemCount() - 1; (loopIdx >= 0) && (ret == ListenerResult::OK); --loopIdx)
			{
				if (m_root->getItem(loopIdx) != NULL)
				{
					ret = m_root->getItem(loopIdx)->hit(touch, touchCount, touchId, touchPos) == HitResult::Hit ? ListenerResult::BLOCK_OTHERS : ListenerResult::OK;
				}
			}
		}
		
		return ret;
	}
	
	void WidgetManager::setTouchCaptureObject(std::shared_ptr<WidgetObject> obj)
	{
		NEXTAI_INFO_LOG(L"id[{}]", obj->getId());
		m_touchCaptureObject = obj;
	}
	
	void WidgetManager::resetTouchCaptureObject()
	{
		NEXTAI_INFO_LOG(L"reset touch");
		m_touchCaptureObject.reset();
	}
	
}