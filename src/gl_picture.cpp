#include "gl_picture.h"

#ifdef SYSTEM_WINDOWS
#include <winuser.h>
#endif // SYSTEM_WINDOWS

#include <string.h>
#include "gl_bitmap.h"
#include "log.h"

namespace Trinity {

	GL_Bitmap* bmp;
	GL_Picture::GL_Picture(GL_Object *parent) :GL_Object(parent)
	{
		memset(m_picturePath, 0x00, sizeof(m_picturePath));
	}

	GL_Picture::~GL_Picture()
	{
	}

	void GL_Picture::Draw()
	{
		glEnable(GL_TEXTURE_2D);//图像有效化
		glBindTexture(GL_TEXTURE_2D, bmp->getTexture());
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
			strcpy_s(m_picturePath, ARRAY_LENGTH(m_picturePath), path);
			bmp = new GL_Bitmap(path);
		}
	}
}