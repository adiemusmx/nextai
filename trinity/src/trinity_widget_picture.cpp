#include "stdafx.h"
#include "trinity/trinity_widget_picture.h"
#include "base/mapbar_log.h"

namespace MapBarDL {

WidgetPicture::WidgetPicture(ObjectId id): WidgetObject(id)
{
	m_bmp = NULL;
}

WidgetPicture::~WidgetPicture()
{
	if (m_bmp != NULL)
	{
		delete(m_bmp);
		m_bmp = NULL;
	}
}

void WidgetPicture::drawImpl()
{
	if (m_bmp == NULL)
		return;

	m_bmp->draw();
}

void WidgetPicture::setDrawableArea(const Rect& area)
{
	WidgetObject::setDrawableArea(area);
	if (m_bmp != NULL)
		m_bmp->setArea(area);
}

void WidgetPicture::setPath(const CHAR* path)
{
	if (path == NULL)
	{
		MAPBAR_WARNING_LOG("Path is a null pointer!");
		return;
	}

	if (m_bmp != NULL)
		m_bmp->setPath(path);
	else
		m_bmp = new GL_Bitmap(path);
}

}