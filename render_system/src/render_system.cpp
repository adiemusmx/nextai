#include "stdafx.h"
#include "render_system/render_system.h"
#include "render_system/render_image.h"
#include "base/nextai_app.h"

namespace NextAI
{
	RenderSystem* RenderSystem::instance()
	{
		static RenderSystem ins;
		return &ins;
	}

	void RenderSystem::init()
	{
		FreeImage::init();
	}

	void RenderSystem::cleanup()
	{
		FreeImage::cleanup();
	}

	void RenderSystem::drawPoint(const Point& point, float pointSize, PixelColor pointColor)
	{
		glBegin(GL_POINT);

		glColor4f(COLOR_GET_4F(pointColor));
		glPointSize(pointSize);
		glVertex3i(point.x, point.y, 0);

		glEnd();
	}

	void RenderSystem::drawPolyLine(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor)
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

	void RenderSystem::drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode)
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
		glColor4f(COLOR_GET_4F(COLOR_WHITE));

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

	void RenderSystem::drawText(const Font* font, const Point& pos, PixelColor color, const CHAR* text)
	{
		font->drawText(pos, color, text);
	}

	void RenderSystem::drawText(const Font* font, const Point& pos, PixelColor color, const WCHAR* text)
	{
		font->drawText(pos, color, text);
	}

	RenderSystem::RenderSystem()
	{

	}

	RenderSystem::~RenderSystem()
	{

	}
}
