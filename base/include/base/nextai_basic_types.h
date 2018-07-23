#ifndef _NEXTAI_BASIC_TYPES_H_
#define _NEXTAI_BASIC_TYPES_H_

#ifdef SYSTEM_WINDOWS
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <string>
#include <math.h>
#include <sys/types.h>
#include <vector>

#include "base/nextai_basic_define.h"

namespace NextAI
{
	void mb_assert(BOOL value, const CHAR* message);

// 半径
typedef float Radian;

// 点信息
class Point
{
public:
	int32 x;
	int32 y;

	BOOL operator==(const Point& p){ return this->x == p.x && this->y == p.y; }
	BOOL operator!=(const Point& p){ return !(*this == p); }
	void invalidate() { x = y = INT_MAX; }
	BOOL isValid() { return !(x == INT_MAX || y == INT_MAX); }
};

typedef Point ScreenPoint;	/* 屏幕坐标 */
typedef Point MapPoint;		/* 经纬度坐标 */
typedef Point NdsPoint;		/* Nds坐标 */

/* 中心轴 */
class Pivot
{
public:
	float x;
	float y;
};

template<typename T>
class Vector
{
public:
	T x;
	T y;
};

// 矩形框
class Rect
{
public:
	int32 left;
	int32 top;
	int32 right;
	int32 bottom;

	BOOL operator==(const Rect& r) { 
		return (left == r.left) 
			&& (top == r.top) 
			&& (right == r.right) 
			&& (bottom == r.bottom);
	}

	BOOL operator!=(const Rect& r) {
		return !(*this == r);
	}

	void invalidate() { left = top = right = bottom = 0; }
	BOOL isValid() { return (left == 0) && (top == 0) && (right == 0) && (bottom == 0); }
	size_t width() { return right - left; }
	size_t height() { return bottom - top; }

	BOOL testPoint(const Point& p) { return (left <= p.x) && (right >= p.x) && (top <= p.y) && (bottom >= p.y); }

	void combine(const Rect& r)	{
		left = MIN(left, r.left);
		top = MIN(top, r.top);
		right = MAX(right, r.right);
		bottom = MAX(bottom, r.bottom);
	}

	void combine(const Point& p) {
		left = MIN(left, p.x);
		top = MIN(top, p.y);
		right = MAX(right, p.x);
		bottom = MAX(bottom, p.y);
	}

	void expand(const Pivot& pivot, Vector<int32> v) {
		left = FLOOR(left - width() * pivot.x * v.x);
		top = FLOOR(top - height() * pivot.y * v.y);
		right = FLOOR(right + width() * (1 - pivot.x) * v.x);
		bottom = FLOOR(bottom + height() * (1 - pivot.y) * v.y);
	}

	void setOffset(Vector<int32> offset){
		left += offset.x;
		top += offset.y;
		right += offset.x;
		bottom += offset.y;
	}
};

typedef Rect ScreenRect;			/* 屏幕矩形框 */
typedef Rect CordinatesRect;		/* 经纬度矩形框 */
typedef Rect NdsRect;				/* Nds矩形框 */

class Segment
{
public:
	Point start;
	Point end;

	Segment(){}
	Segment(const Point& s, const Point& e){
		start = s;
		end = e;
	}

	BOOL slope(float& k){ 
		if (start.x == end.x) return FALSE; 
		k = ((float)end.y - (float)start.y) / ((float)end.x - (float)start.x);
		return TRUE;
	}

	BOOL radian(Radian& r){
		float k;
		if (slope(k))
		{
			r = atan(k);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	float angel()
	{
		float r = 0;
		float ret = 0;
		if (radian(r))
		{
			if (r > 0)
			{
				if (start.x < end.x) 
					ret = 180 / PI * r;
				else 
					ret = 180 / PI * r + 180;
			}
			else
			{
				if (start.x > end.x)
					ret = 180 / PI * r + 180;
				else
					ret = 180 / PI * r + 360;
			}
		}
		else
		{
			if (start.x > end.x)
				ret = 270;
			else
				ret = 90;
		}

		return ret;
	}

	Rect bounding() {
		Rect ret = { 0, 0, 0, 0 };
		ret.left = MIN(start.x, end.x);
		ret.top = MIN(start.y, end.y);
		ret.right = MAX(start.x, end.x);
		ret.bottom = MAX(start.y, end.y);
		return ret;
	}

	void expand_start(float length){
		assert(0);
	}

	void expand_end(float length){
		assert(0);
		// TODO
	}
};

class Line
{
public:
	Point point;
	float angel;

	Line() {}
	Line(Point p, float a){
		point = p;
		angel = a;
	}
	Line(Segment s)
	{
		point = s.start;
		angel = s.angel();
	}
};

// Color
typedef uint64 ColorCode;

}

#endif // !_NEXTAI_BASIC_TYPES_H_