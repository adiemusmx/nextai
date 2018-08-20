#include "stdafx.h"
#include "trinity/trinity_widget_picture.h"
#include "base/nextai_log.h"

namespace NextAI {

	WidgetPicture::WidgetPicture(ObjectId id): WidgetObject(id)
	{
		m_picture = INVALID_TEXTURE_ID;
		memset(m_path, 0x00, sizeof(m_path));
	}

	WidgetPicture::~WidgetPicture()
	{
		release();
	}

	void WidgetPicture::drawImpl()
	{
		if (m_picture == INVALID_TEXTURE_ID)
			return;

		/* ͼƬ��Դ�軭 */
		RENDER_SYSTEM()->drawPicture(m_picture, getDrawableArea());
	}

	void WidgetPicture::setPath(const WCHAR* path)
	{
		if (path == NULL)
		{
			NEXTAI_WARNING_LOG("Path is a null pointer!");
			return;
		}

		/* ����ͼƬ·�� */
		wcscpy_s(m_path, path);

		/* �����µ�������Դ */
		m_picture = RENDER_SYSTEM()->allocPictureTexture(m_path, m_picture);
	}

	const WCHAR* WidgetPicture::getPath()
	{
		return m_path;
	}

	void WidgetPicture::release()
	{
		if (m_picture != INVALID_TEXTURE_ID)
		{
			RENDER_SYSTEM()->releasePictureTexture(m_picture);
			m_picture = INVALID_TEXTURE_ID;
		}
	}

}