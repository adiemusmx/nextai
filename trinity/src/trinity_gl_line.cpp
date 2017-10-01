#include "trinity_gl_line.h"
#include "trinity_util_log.h"
#include <cstdlib>
#include <cstring>

namespace Trinity
{

GL_Line::GL_Line()
{
	m_width = 1.0f;
}

GL_Line::~GL_Line()
{
	m_points.clear();
}

void GL_Line::draw()
{
	size_t loopIdx;
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0xAAAA);
	glLineWidth(m_width);

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	for (loopIdx = 0; loopIdx < m_points.size(); ++loopIdx)
	{
		glVertex3f(m_points[loopIdx].x, m_points[loopIdx].y, 0);
	}
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

void GL_Line::setPoints(const Point* points, size_t count)
{
	size_t loopIdx;
	TRI_INFO_LOG("points[%p] count[%lu]", points, count);
	m_points.clear();

	for (loopIdx = 0; loopIdx < count; ++loopIdx)
	{
		m_points.push_back(points[loopIdx]);
	}
}

void GL_Line::appendPoint(const Point& point)
{
	m_points.push_back(point);
}

void GL_Line::clearPoints()
{
	TRI_INFO_LOG("clear point");
	m_points.clear();
}

void GL_Line::setWidth(float width)
{
	TRI_INFO_LOG("width[%f]", width);
	m_width = width;
}

}