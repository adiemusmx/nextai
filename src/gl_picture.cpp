#include "gl_picture.h"

#ifdef SYSTEM_WINDOWS
#include <winuser.h>
#endif // SYSTEM_WINDOWS

#include <string.h>
#include "gl_bitmap.h"
#include "log.h"

namespace Trinity {

	GL_Picture::GL_Picture(GL_Object *parent) :GL_Object(parent)
	{
		m_bmp = NULL;
	}

	GL_Picture::~GL_Picture()
	{
		if (m_bmp)
			delete(m_bmp);
	}

	void GL_Picture::Draw()
	{
		if (!m_bmp)
			return;

		glEnable(GL_TEXTURE_2D);//图像有效化
		glBindTexture(GL_TEXTURE_2D, m_bmp->getTexture());
		glEnable(GL_ALPHA_TEST);//试描画开始
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f); glVertex2d(10, 230);//左下
		glTexCoord2f(0.0f, 1.0f); glVertex2d(10, 10);//左上
		glTexCoord2f(1.0f, 1.0f); glVertex2d(310, 10);//右上
		glTexCoord2f(1.0f, 0.0f); glVertex2d(310, 230);//右下
		glEnd();
		glDisable(GL_ALPHA_TEST);//试描画结束
		glDisable(GL_TEXTURE_2D);//图像无效
	}

	void GL_Picture::setPicturePath(const char* path)
	{
		if (NULL != path)
		{
			if (m_bmp)
				m_bmp->setPicturePath(path);
			else
				m_bmp = new GL_Bitmap(path);
		}
	}
}