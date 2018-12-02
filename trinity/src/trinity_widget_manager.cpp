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
		NEXTAI_TRACE_LOG_START();
		Rect full = { 0, 0, APP_SERVICE()->getWindowsWidth(), APP_SERVICE()->getWindowsHeight() };
		
		m_root = SMART_PTR<WidgetObject>(NiNew(WidgetObject, 0));
		m_root->setArea(full);
		m_root->addChild(SMART_PTR<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_BASE)));
		m_root->addChild(SMART_PTR<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_VIEW)));
		m_root->addChild(SMART_PTR<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_ONS)));
		m_root->addChild(SMART_PTR<WidgetObject>(NiNew(WidgetSurface, OBJECT_ID_SURFACE_INTERRUPT)));

		APP_SERVICE()->addEventListener(this);

		NEXTAI_TRACE_LOG_END();
	}

	void WidgetManager::cleanup()
	{
		NEXTAI_TRACE_LOG();

		APP_SERVICE()->removeEventListener(this);
	}

	void WidgetManager::addView(SURFACE_ID surface, SMART_PTR<WidgetView>& view)
	{
		NEXTAI_INFO_LOG("surface[%d] view[%p]", surface, view);
		if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
			m_root->getItem(surface)->addChild(SMART_PTR<WidgetObject>(view));
		else
			NEXTAI_WARNING_LOG("Invalid SURFACE_ID[%d] view[%p]", surface, view);
	}

	void WidgetManager::removeView(SURFACE_ID surface, SMART_PTR<WidgetView>& view)
	{
		NEXTAI_INFO_LOG("surface[%d] view[%p]", surface, view);
		if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
			m_root->getItem(surface)->removeChild(view);
		else
			NEXTAI_WARNING_LOG("Invalid SURFACE_ID[%d] view[%p]", surface, view);
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
		NEXTAI_TRACE_LOG_START();
		m_root = NULL;
	}

	WidgetManager::~WidgetManager()
	{
		NEXTAI_TRACE_LOG_START();
	}

	ListenerResult WidgetManager::hardkey(HardkeyID key)
	{
		NEXTAI_INFO_LOG("key[%d]", key);

		// TODO
		return ListenerResult::OK;
	}

	ListenerResult WidgetManager::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		NEXTAI_INFO_LOG("touch[%d] touchCount[%d] touchId[%d] touchPos[%d,%d]", touch, touchCount, touchId[0], touchPos[0].x, touchPos[0].y);
		ListenerResult ret = ListenerResult::OK;
		
		for (int32 loopIdx = m_root->getItemCount() - 1; (loopIdx >= 0) && (ret == ListenerResult::OK); --loopIdx)
		{
			if (m_root->getItem(loopIdx) != NULL)
				ret = m_root->getItem(loopIdx)->hit(touch, touchCount, touchId, touchPos) == HitResult::Hit ? ListenerResult::BLOCK_OTHERS : ListenerResult::OK;
		}
		return ret;
	}

}