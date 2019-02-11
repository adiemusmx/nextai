#include "stdafx.h"
#include "render_system/render_system.h"
#include "render_system/render_system_image.h"
#include "base/nextai_app.h"
#include "base/nextai_file_system.h"

namespace NextAI
{
	RenderSystem* RenderSystem::instance()
	{
		static RenderSystem ins;
		return &ins;
	}
	
	void RenderSystem::init()
	{
		Image::init();
	}
	
	void RenderSystem::cleanup()
	{
		Image::cleanup();
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
		beginDrawPolyLine(lineWidth, lineStyleFactor, lineStyle, lineColor);
		
		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
		{ glVertex3i(points[loopIdx].x, points[loopIdx].y, 0); }
		
		endDrawPolyLine();
	}
	
	void RenderSystem::drawPolyLine(const std::vector<Point>& points, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor)
	{
		beginDrawPolyLine(lineWidth, lineStyleFactor, lineStyle, lineColor);
		std::vector<Point>::const_iterator iter = points.begin();
		
		while (iter != points.end())
		{
			glVertex3i(iter->x, iter->y, 0);
			++iter;
		}
		
		endDrawPolyLine();
	}
	
	void RenderSystem::drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode)
	{
		beginDrawPolygon(lineWidth, lineStyleFactor, lineStyle, lineColor, polygonMode);
		
		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
		{ glVertex3i(points[loopIdx].x, points[loopIdx].y, 0); }
		
		endDrawPolygon();
	}
	
	void RenderSystem::drawPolygon(const std::vector<Point>& points, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode)
	{
		beginDrawPolygon(lineWidth, lineStyleFactor, lineStyle, lineColor, polygonMode);
		std::vector<Point>::const_iterator iter = points.begin();
		
		while (iter != points.end())
		{
			glVertex3i(iter->x, iter->y, 0);
			++iter;
		}
		
		endDrawPolygon();
	}
	
	void RenderSystem::allocPictureTexture(const std::wstring& fileName, PICTURE_TEXTURE_ID& texture)
	{
		texture = INVALID_TEXTURE_ID;
		
		if (FileSystem::isExist(fileName))
		{
			Image::loadTexture(fileName, texture);
		}
		else
		{
			NEXTAI_WARN_LOG(L"Can NOT find file[{}]", fileName);
		}
	}
	
	void RenderSystem::releasePictureTexture(PICTURE_TEXTURE_ID textureId)
	{
		if (textureId != INVALID_TEXTURE_ID && glIsTexture(textureId))
		{
			glDeleteTextures(1, &textureId);
		}
	}
	
	void RenderSystem::allocPictureTextureArray(const std::wstring& fileName, int32 size, std::vector<PICTURE_TEXTURE_ID>& textures)
	{
		textures.clear();
		
		if (FileSystem::isExist(fileName))
		{
			Image::loadTextures(fileName, size, textures);
		}
		else
		{
			NEXTAI_WARN_LOG(L"Can NOT find file[{}]", fileName);
		}
	}
	
	void RenderSystem::releasePictureTextureArray(PICTURE_TEXTURE_ID* textures, int32 size)
	{
		for (int32 loopIdx = 0; loopIdx < size; ++loopIdx)
		{
			releasePictureTexture(textures[loopIdx]);
		}
	}
	
	void RenderSystem::drawTexture(PICTURE_TEXTURE_ID textureId, const Rect& drawArea)
	{
		NEXTAI_TRACE_LOG(L"texture[{}] drawArea[{},{},{},{}]", textureId, drawArea.left, drawArea.top, drawArea.right, drawArea.bottom);
		glColor4f(COLOR_GET_4F(PIXEL_COLOR_WHITE));
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
	
	void RenderSystem::drawText(const Font* font, const Point& pos, PixelColor color, const std::string& text)
	{
		font->drawText(pos, color, text);
	}
	
	void RenderSystem::drawText(const Font* font, const Point& pos, PixelColor color, const std::wstring& text)
	{
		font->drawText(pos, color, text);
	}
	
	RenderSystem::RenderSystem()
	{
	}
	
	RenderSystem::~RenderSystem()
	{
	}
	
	void RenderSystem::beginDrawPolyLine(float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(lineStyleFactor, lineStyle);
		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		glColor4f(COLOR_GET_4F(lineColor));
	}
	
	void RenderSystem::endDrawPolyLine()
	{
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glFlush();
	}
	
	void RenderSystem::beginDrawPolygon(float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode)
	{
		glBegin(GL_POLYGON);
		glColor4f(COLOR_GET_4F(lineColor));
	}
	
	void RenderSystem::endDrawPolygon()
	{
		glEnd();
		glFlush();
	}
}
