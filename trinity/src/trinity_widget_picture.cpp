#include "stdafx.h"
#include "trinity/trinity_widget_picture.h"

namespace NextAI
{
	bool WidgetPicture::allocPictures(const std::wstring& path, int32 size, std::vector<std::shared_ptr<WidgetPicture>>& pictures)
	{
		std::vector<PICTURE_TEXTURE_ID> ids;
		RENDER_SYSTEM()->allocPictureTextureArray(path, size, ids);
		
		for (int32 loopIdx = 0; loopIdx < size; ++loopIdx)
		{
			pictures[loopIdx]->m_path = path;
			pictures[loopIdx]->release();
			pictures[loopIdx]->m_picture = ids[loopIdx];
		}
		
		return true;
	}
	
	WidgetPicture::WidgetPicture(ObjectId id): WidgetObject(id)
	{
		m_picture = INVALID_TEXTURE_ID;
		m_path = L"";
		setHitTransEnable(true);
		setHitEnable(false);
	}
	
	WidgetPicture::~WidgetPicture()
	{
		release();
	}
	
	void WidgetPicture::drawImpl()
	{
		if (m_picture == INVALID_TEXTURE_ID)
		{
			return;
		}
		
		NEXTAI_INFO_LOG(L"object[{}] picture[{}]", getId(), m_picture);
		/* 图片资源描画 */
		RENDER_SYSTEM()->drawTexture(m_picture, getDrawableArea());
	}
	
	void WidgetPicture::setPath(const std::wstring& path)
	{
		if (path == L"")
		{
			NEXTAI_WARN_LOG(L"Path is a null pointer!");
			return;
		}
		
		/* 保存图片路径 */
		m_path = path;
		/* 加载新的纹理资源 */
		RENDER_SYSTEM()->releasePictureTexture(m_picture);
		RENDER_SYSTEM()->allocPictureTexture(m_path, m_picture);
	}
	
	std::wstring WidgetPicture::getPath()
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