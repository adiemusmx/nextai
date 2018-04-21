#include "stdafx.h"
#include "render_system/render_system.h"

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

	void RenderSystem::drawPolyLine(Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor)
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
	}

	void RenderSystem::drawPolygon(Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor, POLYGON_MODE polygonMode)
	{
		glBegin(GL_POLYGON);
		glColor4f(COLOR_GET_RED(lineColor), COLOR_GET_GREEN(lineColor), COLOR_GET_BLUE(lineColor), COLOR_GET_ALPHA(lineColor));

		for (size_t loopIdx = 0; loopIdx < pointsCount; ++loopIdx)
			glVertex3i(points[loopIdx].x, points[loopIdx].y, 0);

		glEnd();
	}

	RenderSystem::RenderSystem()
	{

	}

	RenderSystem::~RenderSystem()
	{

	}
}
