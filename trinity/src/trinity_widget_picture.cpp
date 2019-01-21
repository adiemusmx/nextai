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

		/* 图片资源描画 */
		RENDER_SYSTEM()->drawPicture(m_picture, getDrawableArea());
	}

	void WidgetPicture::setPath(const WCHAR* path)
	{
		if (path == NULL)
		{
			NEXTAI_WARN_LOG("TRINITY", "Path is a null pointer!");
			return;
		}

		/* 保存图片路径 */
		wcscpy(m_path, path);

		/* 加载新的纹理资源 */
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