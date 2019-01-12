#include "stdafx.h"
#include "trinity/trinity_widget_manager.h"
#include "base/nextai_log.h"
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
		TRINITY_TRACE_FUNC();
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
		TRINITY_TRACE_FUNC();

		APP_SERVICE()->removeEventListener(this);
	}

	void WidgetManager::addView(SURFACE_ID surface, std::shared_ptr<WidgetView> view)
	{
		TRINITY_INFO_LOG("surface[{}] view[{}]", surface, view);
		if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
			m_root->getItem(surface)->addChild(std::shared_ptr<WidgetObject>(view));
		else
			TRINITY_WARN_LOG("Invalid SURFACE_ID[{}] view[{}]", surface, view);
	}

	void WidgetManager::removeView(SURFACE_ID surface, std::shared_ptr<WidgetView> view)
	{
		TRINITY_INFO_LOG("surface[{}] view[{}]", surface, view);
		if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
			m_root->getItem(surface)->removeChild(view);
		else
			TRINITY_WARN_LOG("Invalid SURFACE_ID[{}] view[{}]", surface, view);
	}

	ListenerResult WidgetManager::render()
	{
		size_t loopIdx;
		for (loopIdx = 0; loopIdx < SURFACE_ID_MAX; ++loopIdx)
		{
			if (m_root->getItem(loopIdx) != NULL)
				m_root->getItem(loopIdx)->draw();
		}
		return ListenerResult::OK;
	}

	WidgetManager::WidgetManager()
	{
		TRINITY_TRACE_FUNC();
		m_root = NULL;
	}

	WidgetManager::~WidgetManager()
	{
		TRINITY_TRACE_FUNC();
	}

	ListenerResult WidgetManager::hardkey(HardkeyID key)
	{
		TRINITY_INFO_LOG("key[{}]", key);

		// TODO
		return ListenerResult::OK;
	}

	ListenerResult WidgetManager::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		TRINITY_INFO_LOG("touch[{}] touchCount[{}] touchId[{}] touchPos[{},{}]", touch, touchCount, touchId[0], touchPos[0].x, touchPos[0].y);
		ListenerResult ret = ListenerResult::OK;
		
		for (int32 loopIdx = m_root->getItemCount() - 1; (loopIdx >= 0) && (ret == ListenerResult::OK); --loopIdx)
		{
			if (m_root->getItem(loopIdx) != NULL)
				ret = m_root->getItem(loopIdx)->hit(touch, touchCount, touchId, touchPos) == HitResult::Hit ? ListenerResult::BLOCK_OTHERS : ListenerResult::OK;
		}
		return ret;
	}

}