#ifndef _TRINITY_COMMON_TYPES_H_
#define _TRINITY_COMMON_TYPES_H_

#ifdef SYSTEM_WINDOWS

#include <windows.h>

typedef int int32;
typedef int32 BOOL;

#else

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int int32;
typedef int32 BOOL;

struct POINT
{
	int32 x;
	int32 y;
};

struct RECT
{
	int32 left;
	int32 top;
	int32 right;
	int32 bottom;
};

typedef wchar_t WCHAR;
typedef char CHAR;
typedef long LONG;

#endif // SYSTEM_WINDOWS

#include <vector>

#endif // !_TRINITY_COMMON_TYPES_H_