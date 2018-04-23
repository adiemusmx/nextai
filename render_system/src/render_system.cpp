#include "stdafx.h"
#include "render_system/render_system.h"
#include "render_system/free_image.h"

#define COLOR_WHITE 0x00000000
#define COLOR_BLACK 0xFFFFFF00

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

	TEXTURE_ID RenderSystem::allocTexture(const MbString& fileName, TEXTURE_ID oldTextureId)
	{
		// 删除旧的纹理
		releaseTexture(oldTextureId);

		TEXTURE_ID textureId = INVALID_TEXTURE_ID;

		//textureId = allocBmpTexture(fileName);
		textureId = FreeImage::loadTexture(fileName);

		return textureId;
	}

	TEXTURE_ID RenderSystem::allocBmpTexture(const MbString& fileName)
	{
		size_t width, height;
		CHAR* fileBuffer;
		TEXTURE_ID textureId = INVALID_TEXTURE_ID;
		if (fileName == L"" || loadBmpFile(fileName, width, height, &fileBuffer) == FALSE)
		{
			// 非法文件，或载入失败
			MAPBAR_ERROR_LOG("File[%s] load failed.", fileName);
			return textureId;
		}

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)width, (GLsizei)height, 0, GL_RGB, GL_UNSIGNED_BYTE, fileBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		return textureId;
	}

	void RenderSystem::releaseTexture(TEXTURE_ID textureId)
	{
		if (textureId != INVALID_TEXTURE_ID && glIsTexture(textureId))
		{
			glDeleteTextures(1, &textureId);
		}
	}

	void RenderSystem::drawTexture(TEXTURE_ID textureId, const Rect& drawArea)
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

	BOOL RenderSystem::loadBmpFile(const MbString& bmpFile, size_t& width, size_t& height, CHAR** data)
	{
		FILE* fp;
		size_t size;
		size_t i;
		unsigned short int planes;
		unsigned short int bpp;
		char temp;

		fp = _wfopen(bmpFile.cStr(), L"rb");

		if (fp == NULL)
		{
			MAPBAR_ERROR_LOG("Image[%s] do not exist.", bmpFile);
			return FALSE;
		}
		fseek(fp, 18, SEEK_CUR);

		if ((i = fread(&width, 4, 1, fp)) != 1)
		{
			MAPBAR_ERROR_LOG("Image[%s] read width failed.", bmpFile);
			return FALSE;
		}

		if ((i = fread(&height, 4, 1, fp)) != 1)
		{
			MAPBAR_ERROR_LOG("Image[%s] read height failed.", bmpFile);
			return FALSE;
		}

		MAPBAR_INFO_LOG("width[%u] height[%u]", width, height)
			size = width * height * 3;
		if ((fread(&planes, 2, 1, fp)) != 1)
		{
			MAPBAR_ERROR_LOG("Image[%s] read planes' flag failed.", bmpFile);
			return FALSE;
		}
		if (planes != 1)
		{
			MAPBAR_ERROR_LOG("Image[%s] is not bmp file.", bmpFile);
			return FALSE;
		}

		if ((i = fread(&bpp, 2, 1, fp)) != 1)
		{
			MAPBAR_ERROR_LOG("Can NOT read Image[%s] bpp.", bmpFile);
			return FALSE;
		}
		if (bpp != 24)
		{
			MAPBAR_ERROR_LOG("Image[%s] is not 24bpp.", bmpFile);
			return FALSE;
		}

		fseek(fp, 24, SEEK_CUR);
		*data = (CHAR*)malloc(size);
		if (*data == NULL)
		{
			MAPBAR_ERROR_LOG("Image[%s]'s malloc failed. size[%zu]", bmpFile, size);
			return FALSE;
		}
		if ((i = fread(*data, size, 1, fp)) != 1)
		{
			MAPBAR_ERROR_LOG("Can NOT read image[%s] data.", bmpFile);
			return FALSE;
		}

		// 配色颠倒处理（RGB修改为BGR）
		for (i = 0; i < size; i += 3)
		{
			temp = (*data)[i];
			(*data)[i] = (*data)[i + 2];
			(*data)[i + 2] = temp;
		}
		return TRUE;
	}

	RenderSystem::RenderSystem()
	{

	}

	RenderSystem::~RenderSystem()
	{

	}
}
