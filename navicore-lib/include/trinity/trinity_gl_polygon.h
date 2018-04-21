#ifndef _TRINITY_GL_POLYGON_H_
#define _TRINITY_GL_POLYGON_H_

#include "base/mapbar_basic_define.h"
#include "base/mapbar_basic_types.h"

namespace MapBarDL {



	enum GL_Face
	{
		GL_Face_front,				// 表示显示模式将适用于物体的前向面（也就是物体能看到的面）
		GL_Face_back,				// 表示显示模式将适用于物体的后向面（也就是物体上不能看到的面）
		GL_Face_all					// 表示显示模式将适用于物体的所有面
	};

	enum GL_Mode
	{
		GL_Mode_point,		// 表示只显示顶点，多边形用点显示
		GL_Mode_line,		// 表示显示线段，多边形用轮廓显示
		GL_Mode_fill		// 表示显示面，多边形采用填充形式
	};

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
		virtual void setColor(ColorCode color);
		virtual ColorCode getColor() { return m_color; }

	private:
		std::vector<Point> m_points;

		// width
		float m_width;			// Default: 1.0f

		// style
		int32 m_styleFacor;		// Default: 1
		int32 m_style;			// Default: 0xFFFF

		// color --> RGBA
		ColorCode m_color;		// Default: 0xFF000000
	};

}
#endif // !_TRINITY_GL_POLYGON_H_