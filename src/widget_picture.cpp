#include "widget_picture.h"

namespace Trinity {

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

// 设定/取得区域
void WidgetPicture::setArea(const RECT& area)
{
	WidgetObject::setArea(area);
	if (m_bmp != NULL)
		m_bmp->setArea(area);
}

void WidgetPicture::setPath(const CHAR* path)
{
	if (path == NULL)
	{
		TRI_WARNING_LOG("Path is a null pointer!");
		return;
	}

	if (m_bmp != NULL)
		m_bmp->setPath(path);
	else
		m_bmp = new GL_Bitmap(path);
}

}