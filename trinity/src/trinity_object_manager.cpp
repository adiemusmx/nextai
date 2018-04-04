#include "trinity/trinity_object_manager.h"
#include "trinity/trinity_util_log.h"

namespace Trinity {
ObjectManager* ObjectManager::getInstance()
{
	static ObjectManager obj;
	return &obj;
}

void ObjectManager::init()
{
	TRI_TRACE_LOG();
	m_surfaces[SurfaceID_BASE] = new WidgetSurface(OBJECT_ID_SURFACE_BASE);
	m_surfaces[SurfaceID_VIEW] = new WidgetSurface(OBJECT_ID_SURFACE_VIEW);
	m_surfaces[SurfaceID_ONS] = new WidgetSurface(OBJECT_ID_SURFACE_ONS);
	m_surfaces[SurfaceID_INTERRUPT] = new WidgetSurface(OBJECT_ID_SURFACE_INTERRUPT);
}

void ObjectManager::cleanup()
{
	TRI_TRACE_LOG();
	size_t loopIdx;
	for (loopIdx = 0; loopIdx < SurfaceID_MAX; ++loopIdx)
	{
		if (m_surfaces[loopIdx] != NULL)
		{
			delete(m_surfaces[loopIdx]);
			m_surfaces[loopIdx] = NULL;
		}
	}
}

void ObjectManager::addView(SurfaceID surface, WidgetView* view)
{
	TRI_INFO_LOG("surface[%d] view[%p]", surface, view);
	if (surface >= SurfaceID_BASE && surface < SurfaceID_MAX && view != NULL)
		m_surfaces[surface]->addChild(view);
	else
		TRI_WARNING_LOG("Invalid surfaceID[%d] view[%p]", surface, view);
}

void ObjectManager::removeView(SurfaceID surface, WidgetView* view)
{
	TRI_INFO_LOG("surface[%d] view[%p]", surface, view);
	if (surface >= SurfaceID_BASE && surface < SurfaceID_MAX && view != NULL)
		m_surfaces[surface]->removeChild(view);
	else
		TRI_WARNING_LOG("Invalid surfaceID[%d] view[%p]", surface, view);
}

void ObjectManager::draw()
{
	size_t loopIdx;
	for (loopIdx = 0; loopIdx < SurfaceID_MAX; ++loopIdx)
	{
		if (m_surfaces[loopIdx] != NULL)
			m_surfaces[loopIdx]->draw();
	}
}

ObjectManager::ObjectManager()
{
	TRI_TRACE_LOG();
	size_t loopIdx;
	for (loopIdx = 0; loopIdx < SurfaceID_MAX; ++loopIdx)
	{
		m_surfaces[loopIdx] = NULL;
	}
}

ObjectManager::~ObjectManager()
{
	TRI_TRACE_LOG();
}

BOOL ObjectManager::hardkey(HardkeyID key)
{
	TRI_INFO_LOG("key[%d]", key);
	// TODO
	return FALSE;
}

BOOL ObjectManager::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
{
	TRI_INFO_LOG("touch[%d] touchCount[%d] touchId[%d] touchPos[%d,%d]", touch, touchCount, touchId[0], touchPos[0].x, touchPos[0].y);
	BOOL ret = FALSE;
	size_t loopIdx;
	for (loopIdx = SurfaceID_MAX - 1; (loopIdx >= 0) && (ret == FALSE); --loopIdx)
	{
		if (m_surfaces[loopIdx] != NULL)
			ret = m_surfaces[loopIdx]->hit(touch, touchCount, touchId, touchPos);
		TRI_INFO_LOG("touch surface[%zu,%p] ret[%d]", loopIdx, m_surfaces[loopIdx], ret);
	}
	return ret;
}

}