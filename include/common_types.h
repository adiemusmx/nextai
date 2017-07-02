#pragma once

typedef int int32;
typedef int32 BOOL;

#ifdef SYSTEM_WINDOWS

#include <windows.h>

#else

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
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

// Hit event type
enum E_HIT_TYPE {
	E_HIT_TYPE_DONW,
	E_HIT_TYPE_UP,
	E_HIT_TYPE_SHORT,
	E_HIT_TYPE_LONG,
	E_HIT_TYPE_LONG_UP,
	E_HIT_TYPE_REPEAT
};