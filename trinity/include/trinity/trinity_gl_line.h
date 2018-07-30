#ifndef _TRINITY_GL_LINE_H_
#define _TRINITY_GL_LINE_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

namespace NextAI {

// 1111111111111111 --> ！！！！！！！！！！！！！！
#define GL_LINE_STYLE_1 0xFFFF

// 1010101010101010 --> --------------
#define GL_LINE_STYLE_2 0xAAAA

// 1100110011001100 --> ！！  ！！  ！！  ！！
#define GL_LINE_STYLE_3 0xCCCC

class GL_Line
{
public:
	GL_Line();
	virtual ~GL_Line();

	// Draw
	virtual void draw();

	// Points
	virtual void setPoints(const Point* points, size_t count);
	virtual void appendPoint(const Point& point);
	virtual void clearPoints();

	// Line width
	virtual void setWidth(float width);
	virtual float getWidth() { return m_width; }

	// Line style
	virtual void setStyleFactor(int32 factor);
	virtual int32 getStyleFactor() { return m_styleFacor; }
	virtual void setStyle(int32 style);
	virtual int32 getStyle() { return m_style; }

	// Color
	virtual void setColor(PixelColor color);
	virtual PixelColor getColor() { return m_color; }

private:
	std::vector<Point> m_points;

	// width
	float m_width;			// Default: 1.0f

	// style
	int32 m_styleFacor;		// Default: 1
	int32 m_style;			// Default: 0xFFFF

	// color --> RGBA
	PixelColor m_color;		// Default: 0xFF000000
};

}
#endif // !_TRINITY_GL_LINE_H_