﻿#ifndef _MAPBAR_BASIC_DEFINE_H_
#define _MAPBAR_BASIC_DEFINE_H_

typedef int int32;
typedef int32 BOOL;
typedef unsigned int uint32;
typedef unsigned long uint64;

// Max length of file's path
#define FILE_PATH_MAX_LENGTH 1024

// Max length of text
#define TEXT_MAX_LENGTH 512

// Disable class' copy constructor.
#define DISABLE_CLASS_COPY(typeName) \
	typeName(const typeName&); typeName& operator=(const typeName&)

// ############ POINT ############
// Compare point.
#define POINT_equals(p,q) \
	(p.x == q.x && p.y == q.y)

// ############ RECT ############
// Return whether the point p is in rect r

// ############ ARRAY ############
#define element_of(x) \
	(sizeof(x) / sizeof(x[0]))

// ############ TOUCH ############
#define TOUCH_POINT_MAX_COUNT 10

// ############ COLOR ############
#define COLOR_GET_RED(color)	(((color >> 24) & 0x000000FF) / 256.0f)
#define COLOR_GET_GREEN(color)	(((color >> 16) & 0x000000FF) / 256.0f)
#define COLOR_GET_BLUE(color)	(((color >> 8) & 0x000000FF) / 256.0f)
#define COLOR_GET_ALPHA(color)	((color & 0x000000FF) / 256.0f)

// ############ MEMORY ###########

#if defined(MAPBAR_USE_MEMORY_DEBUGGER)
#define MbNew(T, ...) ((T*)_MemoryDebugger_addRecord(new T(__VA_ARGS__), sizeof(T), __FILE__, __LINE__, __FUNCTION__))
#define MbNewArray(T, n) (T*)_MemoryDebugger_addRecord(new T[n], sizeof(T) * n, __FILE__, __LINE__, __FUNCTION__);
#define MbDelete(o) {_MemoryDebugger_removeRecord(o); delete o; }
#define MbDeleteArray(o) {_MemoryDebugger_removeRecord(o); delete[] o; }
#else
#define MbNew(T, ...) (new T(__VA_ARGS__))
#define MbDelete(o) delete o
#define MbNewArray(T, n) new T[n]
#define MbDeleteArray(o) delete[] o
#endif

#define MIN(l,r) (l > r ? r : l)
#define MAX(l,r) (l < r ? r : l)

#define MbAssert(expr) assert(expr)

#define FLOOR(x) (static_cast<int32>(x))

#define PI 3.1415926f

#ifndef INT_MIN
#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#endif

#ifndef INT_MAX
#define INT_MAX       2147483647    /* maximum (signed) int value */
#endif

#ifdef SYSTEM_LINUX
#define WCHAR wchar_t
#define CHAR char
#define MB_LEN_MAX    5             /* max. # bytes in multibyte char */
#define SHRT_MIN    (-32768)        /* minimum (signed) short value */
#define SHRT_MAX      32767         /* maximum (signed) short value */
#define USHRT_MAX     0xffff        /* maximum unsigned short value */
#define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#define LONG_MAX      2147483647L   /* maximum (signed) long value */
#define ULONG_MAX     0xffffffffUL  /* maximum unsigned long value */
#define LLONG_MAX     9223372036854775807i64       /* maximum signed long long int value */
#define LLONG_MIN   (-9223372036854775807i64 - 1)  /* minimum signed long long int value */
#define ULLONG_MAX    0xffffffffffffffffui64       /* maximum unsigned long long int value */
#endif

#define D_USE_STD_STRING

#endif // !_MAPBAR_BASIC_DEFINE_H_