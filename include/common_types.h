#pragma once

#ifdef SYSTEM_WINDOWS
#include <windows.h>
#endif // SYSTEM_WINDOWS

typedef int int32;
typedef int BOOL;

// �������
enum E_HIT_TYPE {
	E_HIT_TYPE_DONW,		// ѹ��
	E_HIT_TYPE_UP,			// ̧��
	E_HIT_TYPE_SHORT,		// ��ѹ
	E_HIT_TYPE_LONG,		// ��Ѻ
	E_HIT_TYPE_LONG_UP,		// ��Ѻ̧��
	E_HIT_TYPE_REPEAT
};