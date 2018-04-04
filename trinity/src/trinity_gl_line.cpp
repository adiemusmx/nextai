#include "trinity/trinity_gl_line.h"
#include "trinity/trinity_util_log.h"
#include <cstdlib>
#include <cstring>

namespace Trinity {

GL_Line::GL_Line()
{
	m_width = 1.0f;
	m_styleFacor = 1;
	m_style = 0xFFFF;
	m_color = 0xFF000000;
}

GL_Line::~GL_Line()
{
	m_points.clear();
}

void GL_Line::draw()
{
	size_t loopIdx;
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(m_styleFacor, m_style);
	glLineWidth(m_width);

	glBegin(GL_LINE_STRIP);
	glColor4f(COLOR_GET_RED(m_color), COLOR_GET_GREEN(m_color), COLOR_GET_BLUE(m_color), COLOR_GET_ALPHA(m_color));

	for (loopIdx = 0; loopIdx < m_points.size(); ++loopIdx)
		glVertex3f(m_points[loopIdx].x, m_points[loopIdx].y, 0);

	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void GL_Line::setPoints(const Point* points, size_t count)
{
	size_t loopIdx;
	TRI_VERBOSE_LOG("points[%p] count[%zu]", points, count);
	m_points.clear();

	for (loopIdx = 0; loopIdx < count; ++loopIdx)
	{
		m_points.push_back(points[loopIdx]);
	}
}

void GL_Line::appendPoint(const Point& point)
{
	TRI_VERBOSE_LOG("point[%d,%d]", point.x, point.y);
	m_points.push_back(point);
}

void GL_Line::clearPoints()
{
	TRI_VERBOSE_LOG("clear point");
	m_points.clear();
}

void GL_Line::setWidth(float width)
{
	TRI_VERBOSE_LOG("width[%f]", width);
	m_width = width;
}

void GL_Line::setStyleFactor(int32 factor)
{
	TRI_VERBOSE_LOG("factor[%x]", factor);
	m_styleFacor = factor;
}

void GL_Line::setStyle(int32 style)
{
	TRI_VERBOSE_LOG("style[%x]", style);
	m_style = style;
}

void GL_Line::setColor(ColorCode color)
{
	TRI_VERBOSE_LOG("color[%x]", color);
	printf("Color [%f %f %f %f]\n", COLOR_GET_RED(color), COLOR_GET_GREEN(color), COLOR_GET_BLUE(color), COLOR_GET_ALPHA(color));
	m_color = color;
}

}