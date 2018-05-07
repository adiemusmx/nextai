#include "stdafx.h"
#include "render_system/render_system.h"
#include "render_system/free_image.h"

#define COLOR_WHITE 0x000000FF
#define COLOR_BLACK 0xFFFFFFFF


namespace MapBarDL
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

		glColor4f(COLOR_GET_RED(pointColor), COLOR_GET_GREEN(pointColor), COLOR_GET_BLUE(pointColor), COLOR_GET_ALPHA(pointColor));
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
		glColor4f(COLOR_GET_RED(lineColor), COLOR_GET_GREEN(lineColor), COLOR_GET_BLUE(lineColor), COLOR_GET_ALPHA(lineColor));

		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
			glVertex3i(points[loopIdx].x, points[loopIdx].y, 0);

		glEnd();
		glDisable(GL_LINE_STIPPLE);

		glFlush();
	}

	void RenderSystem::drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor, POLYGON_MODE polygonMode)
	{
		glBegin(GL_POLYGON);
		glColor4f(COLOR_GET_RED(lineColor), COLOR_GET_GREEN(lineColor), COLOR_GET_BLUE(lineColor), COLOR_GET_ALPHA(lineColor));

		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
			glVertex3i(points[loopIdx].x, points[loopIdx].y, 0);

		glEnd();

		glFlush();
	}

	PICTURE_TEXTURE_ID RenderSystem::allocPictureTexture(const MbString& fileName, PICTURE_TEXTURE_ID oldTextureId)
	{
		// 删除旧的纹理
		releasePictureTexture(oldTextureId);

		PICTURE_TEXTURE_ID textureId = INVALID_TEXTURE_ID;

		//textureId = allocBmpTexture(fileName);
		textureId = FreeImage::loadTexture(fileName);

		return textureId;
	}

	void RenderSystem::releasePictureTexture(PICTURE_TEXTURE_ID textureId)
	{
		if (textureId != INVALID_TEXTURE_ID && glIsTexture(textureId))
		{
			glDeleteTextures(1, &textureId);
		}
	}

	void RenderSystem::drawPicture(PICTURE_TEXTURE_ID& textureId, const Rect& drawArea)
	{
		glColor4f(COLOR_GET_RED(COLOR_BLACK), COLOR_GET_GREEN(COLOR_BLACK), COLOR_GET_BLUE(COLOR_BLACK), COLOR_GET_ALPHA(COLOR_BLACK));

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

	TextTextureInfo RenderSystem::allocTextTexture(const MbString& str)
	{
		HDC hDC = wglGetCurrentDC();

		HFONT hFont = CreateFontA(13, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
			GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "楷体_GB2312");
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		DeleteObject(hOldFont);

		TextTextureInfo ret;

		ret.num = str.length();
		ret.texture = glGenLists(ret.num);

		MbAssert(ret.texture != 0);

		//glColor4f(COLOR_GET_RED(COLOR_WHITE), COLOR_GET_GREEN(COLOR_WHITE), COLOR_GET_BLUE(COLOR_WHITE), COLOR_GET_ALPHA(COLOR_WHITE));

		glRasterPos2f(0.8f, 0.8f);

		// 逐个输出字符
		for (size_t i = 0; i < ret.num; ++i)
		{
			WCHAR temp = str[i];
			wglUseFontBitmapsW(hDC, temp, 1, ret.texture + i);
		}

		for (size_t i = 0; i < ret.num; ++i)
		{
			glCallList(ret.texture + i);
		}
		glFlush();

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
		HDC hDC = wglGetCurrentDC();

#if 0
		glRasterPos2f(0.0f, 0.0f);
		ColorCode color = 0x00FF0088;
		glColor4f(COLOR_GET_RED(color), COLOR_GET_GREEN(color), COLOR_GET_BLUE(color), COLOR_GET_ALPHA(color));
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
