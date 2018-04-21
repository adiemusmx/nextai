#ifndef _TRINITY_GL_POLYGON_H_
#define _TRINITY_GL_POLYGON_H_

#include "base/mapbar_basic_define.h"
#include "base/mapbar_basic_types.h"

namespace MapBarDL {



	enum GL_Face
	{
		GL_Face_front,				// ��ʾ��ʾģʽ�������������ǰ���棨Ҳ���������ܿ������棩
		GL_Face_back,				// ��ʾ��ʾģʽ������������ĺ����棨Ҳ���������ϲ��ܿ������棩
		GL_Face_all					// ��ʾ��ʾģʽ�������������������
	};

	enum GL_Mode
	{
		GL_Mode_point,		// ��ʾֻ��ʾ���㣬������õ���ʾ
		GL_Mode_line,		// ��ʾ��ʾ�߶Σ��������������ʾ
		GL_Mode_fill		// ��ʾ��ʾ�棬����β��������ʽ
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