#include "stdafx.h"
#include "trinity/trinity_object_manager.h"
#include "base/nextai_log.h"
#include "trinity/trinity_widget_surface.h"

namespace NextAI {
ObjectManager* ObjectManager::getInstance()
{
	static ObjectManager obj;
	return &obj;
}

void ObjectManager::init()
{
	nextai_TRACE_LOG_START();
	m_surfaces[SURFACE_ID_BASE] = new WidgetSurface(OBJECT_ID_SURFACE_BASE);
	m_surfaces[SURFACE_ID_VIEW] = new WidgetSurface(OBJECT_ID_SURFACE_VIEW);
	m_surfaces[SURFACE_ID_ONS] = new WidgetSurface(OBJECT_ID_SURFACE_ONS);
	m_surfaces[SURFACE_ID_INTERRUPT] = new WidgetSurface(OBJECT_ID_SURFACE_INTERRUPT);
}

void ObjectManager::cleanup()
{
	nextai_TRACE_LOG_START();
	size_t loopIdx;
	for (loopIdx = 0; loopIdx < SURFACE_ID_MAX; ++loopIdx)
	{
		if (m_surfaces[loopIdx] != NULL)
		{
			delete(m_surfaces[loopIdx]);
			m_surfaces[loopIdx] = NULL;
		}
	}
}

void ObjectManager::addView(SURFACE_ID surface, WidgetView* view)
{
	nextai_INFO_LOG("surface[%d] view[%p]", surface, view);
	if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
		m_surfaces[surface]->addChild(view);
	else
		nextai_WARNING_LOG("Invalid SURFACE_ID[%d] view[%p]", surface, view);
}

void ObjectManager::removeView(SURFACE_ID surface, WidgetView* view)
{
	nextai_INFO_LOG("surface[%d] view[%p]", surface, view);
	if (surface >= SURFACE_ID_BASE && surface < SURFACE_ID_MAX && view != NULL)
		m_surfaces[surface]->removeChild(view);
	else
		nextai_WARNING_LOG("Invalid SURFACE_ID[%d] view[%p]", surface, view);
}

void ObjectManager::draw()
{
	size_t loopIdx;
	for (loopIdx = 0; loopIdx < SURFACE_ID_MAX; ++loopIdx)
	{
		if (m_surfaces[loopIdx] != NULL)
			m_surfaces[loopIdx]->draw();
	}
}

ObjectManager::ObjectManager()
{
	nextai_TRACE_LOG_START();
	size_t loopIdx;
	for (loopIdx = 0; loopIdx < SURFACE_ID_MAX; ++loopIdx)
	{
		m_surfaces[loopIdx] = NULL;
	}
}

ObjectManager::~ObjectManager()
{
	nextai_TRACE_LOG_START();
}

BOOL ObjectManager::hardkey(HardkeyID key)
{
	nextai_INFO_LOG("key[%d]", key);
	// TODO
	return FALSE;
}

BOOL ObjectManager::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
{
	nextai_INFO_LOG("touch[%d] touchCount[%d] touchId[%d] touchPos[%d,%d]", touch, touchCount, touchId[0], touchPos[0].x, touchPos[0].y);
	BOOL ret = FALSE;
	size_t loopIdx;
	for (loopIdx = SURFACE_ID_MAX - 1; (loopIdx >= 0) && (ret == FALSE); --loopIdx)
	{
		if (m_surfaces[loopIdx] != NULL)
			ret = m_surfaces[loopIdx]->hit(touch, touchCount, touchId, touchPos);
		nextai_INFO_LOG("touch surface[%u,%p] ret[%d]", loopIdx, m_surfaces[loopIdx], ret);
	}
	return ret;
}

}