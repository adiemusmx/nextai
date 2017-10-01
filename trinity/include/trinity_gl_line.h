#ifndef _TRINITY_GL_LINE_H_
#define _TRINITY_GL_LINE_H_

#include "trinity_common_define.h"
#include "trinity_common_types.h"

#include <GL/glut.h>
#include <GL/glu.h>

namespace Trinity
{

class GL_Line
{
public:
	GL_Line();
	virtual ~GL_Line();

	// Draw
	virtual void drawImpl();

	// Points
	virtual void setPoints(const Point* points, size_t count);
	virtual void appendPoint(const Point& point);
	virtual void clearPoints();

	// Line width
	virtual void setWidth(float width);

private:
	std::vector<Point> m_points;
	float m_width;
};

}
#endif // !_TRINITY_GL_LINE_H_