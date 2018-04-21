#ifndef _MAPBAR_BASIC_TYPES_H_
#define _MAPBAR_BASIC_TYPES_H_

typedef int int32;
typedef int32 BOOL;
typedef unsigned int uint32;
typedef unsigned long uint64;

#ifdef SYSTEM_WINDOWS
#include <windows.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

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

#include <vector>

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

// Color
typedef uint64 ColorCode;

#endif // !_MAPBAR_BASIC_TYPES_H_