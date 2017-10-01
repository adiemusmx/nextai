#ifndef _TRINITY_COMMON_TYPES_H_
#define _TRINITY_COMMON_TYPES_H_

typedef int int32;
typedef int32 BOOL;

#ifdef SYSTEM_WINDOWS
#include <windows.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

typedef int int32;
typedef int32 BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef WCHAR
#define WCHAR wchar_t
#endif

#ifndef CHAR
#define CHAR char
#endif

#ifndef LONG
#define LONG long
#endif

#include <vector>

namespace Trinity
{

// Int Point
struct Point
{
	int32 x;
	int32 y;
};

// Double Point
struct DoublePoint
{
	double x;
	double y;
};

// Rect
struct Rect
{
	int32 left;
	int32 top;
	int32 right;
	int32 bottom;
};

// Double Rect
struct DoubleRect
{
	double left;
	double top;
	double right;
	double bottom;
};

}

#endif // !_TRINITY_COMMON_TYPES_H_