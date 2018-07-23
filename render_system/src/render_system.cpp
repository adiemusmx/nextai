#include "stdafx.h"
#include "render_system/render_system.h"
#include "render_system/free_image.h"
#include "base/nextai_app.h"

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0x000000FF
#define COLOR_RED 0xFF0000FF
#define COLOR_GREEN 0x00FF00FF
#define COLOR_BLUE 0x0000FFFF

namespace NextAI
{
	RenderSystem* RenderSystem::instance()
	{
		static RenderSystem ins;
		return &ins;
	}

	void RenderSystem::init()
	{
	}

	void RenderSystem::cleanup()
	{
		
	}

	void RenderSystem::drawPoint(const Point& point, float pointSize, ColorCode pointColor)
	{
		glBegin(GL_POINT);

		glColor4f(COLOR_GET_4F(pointColor));
		glPointSize(pointSize);
		glVertex3i(point.x, point.y, 0);

		glEnd();
	}

	void RenderSystem::drawPolyLine(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(lineStyleFactor, lineStyle);
		glLineWidth(lineWidth);

		glBegin(GL_LINE_STRIP);
		glColor4f(COLOR_GET_4F(lineColor));

		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
			glVertex3i(points[loopIdx].x, points[loopIdx].y, 0);

		glEnd();
		glDisable(GL_LINE_STIPPLE);

		glFlush();
	}

	void RenderSystem::drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor, POLYGON_MODE polygonMode)
	{
		glBegin(GL_POLYGON);
		glColor4f(COLOR_GET_4F(lineColor));

		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
			glVertex3i(points[loopIdx].x, points[loopIdx].y, 0);

		glEnd();

		glFlush();
	}

	PICTURE_TEXTURE_ID RenderSystem::allocPictureTexture(const WCHAR* fileName, PICTURE_TEXTURE_ID oldTextureId)
	{
		// 删除旧的纹理
		if (oldTextureId != INVALID_TEXTURE_ID)
		{
			releasePictureTexture(oldTextureId);
		}

		if (!FileSystem::isExist(fileName))
		{
			NEXTAI_WARNING_W_LOG(L"Can NOT find file[%s]", fileName);
			return INVALID_TEXTURE_ID;
		}
		else
		{
			return FreeImage::loadTexture(fileName);
		}
	}

	void RenderSystem::releasePictureTexture(PICTURE_TEXTURE_ID textureId)
	{
		if (textureId != INVALID_TEXTURE_ID && glIsTexture(textureId))
		{
			glDeleteTextures(1, &textureId);
		}
	}

	void RenderSystem::drawPicture(PICTURE_TEXTURE_ID textureId, const Rect& drawArea)
	{
		glColor4f(COLOR_GET_4F(COLOR_BLACK));

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glEnable(GL_ALPHA_TEST);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(drawArea.left, drawArea.bottom);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(drawArea.left, drawArea.top);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(drawArea.right, drawArea.top);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2d(drawArea.right, drawArea.bottom);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_TEXTURE_2D);

		glFlush();
	}

	TextTextureInfo RenderSystem::allocTextTexture(const WCHAR* str)
	{
		TextTextureInfo ret;
#ifdef SYSTEM_WINDOWS
		HDC hDC = wglGetCurrentDC();

		HFONT hFont = CreateFontA(13, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
			GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体_GB2312");
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		DeleteObject(hOldFont);

		ret.num = wcslen(str);
		ret.texture = glGenLists(ret.num);

		MbAssert(ret.texture != 0);

		// 逐个输出字符
		for (size_t i = 0; i < ret.num; ++i)
		{
			WCHAR temp = str[i];
			wglUseFontBitmapsW(hDC, temp, 1, ret.texture + i);
		}
#endif
		return ret;	
	}

	void RenderSystem::releaseTextTexture(TextTextureInfo& info)
	{
		glDeleteLists(info.texture, info.num);
		info.texture = INVALID_TEXTURE_ID;
		info.num = 0;
	}

	void RenderSystem::drawText(const TextTextureInfo& info, const Rect& drawArea)
	{
#if 1
		glColor4f(COLOR_GET_4F(COLOR_RED));
		ScreenPoint startPos = { drawArea.left, drawArea.top };
		Vector<float> startPosOrtho = APP_SERVICE()->pos2ortho(startPos);
#if 0
		glRasterPos2f(startPosOrtho.x, startPosOrtho.y);
#else
		glRasterPos2f(0.0f, 0.0f);
#endif
		for (size_t i = 0; i < info.num; ++i)
		{
			glCallList(info.texture + i);
		}
		glFlush();
#else
		GLint width = NEXT_AI_APP_SERVICE()->getWindowsWidth();
		GLint height = NEXT_AI_APP_SERVICE()->getWindowsHeight();

		//gluPerspective(45.0f * 2, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
		//glTranslatef(0.0f, 0.0f, -480);         //当前局部坐标为(0,0,-480)
		glRasterPos2f(0.0f, 0.0f);//在视口的左下角显示字体
		//glColor4f(COLOR_GET_RED(COLOR_WHITE), COLOR_GET_GREEN(COLOR_WHITE), COLOR_GET_BLUE(COLOR_WHITE), COLOR_GET_ALPHA(COLOR_WHITE));
		//glRasterPos2f(drawArea.left, drawArea.top);
		for (size_t i = 0; i < info.num; ++i)
		{
			glCallList(info.texture + i);
		}
		glFlush();
#endif
	}


	RenderSystem::RenderSystem()
	{

	}

	RenderSystem::~RenderSystem()
	{

	}
}
