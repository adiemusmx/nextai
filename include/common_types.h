#pragma once

#ifdef SYSTEM_WINDOWS
#include <windows.h>
#endif // SYSTEM_WINDOWS

typedef int int32;
typedef int BOOL;

// 点击类型
enum E_HIT_TYPE {
	E_HIT_TYPE_DONW,		// 压下
	E_HIT_TYPE_UP,			// 抬起
	E_HIT_TYPE_SHORT,		// 短压
	E_HIT_TYPE_LONG,		// 长押
	E_HIT_TYPE_LONG_UP,		// 长押抬起
	E_HIT_TYPE_REPEAT
};