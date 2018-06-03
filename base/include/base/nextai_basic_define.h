#ifndef _nextai_BASIC_DEFINE_H_
#define _nextai_BASIC_DEFINE_H_

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
#define COLOR_GET_4F(color)		COLOR_GET_RED(color), COLOR_GET_GREEN(color), COLOR_GET_BLUE(color), COLOR_GET_ALPHA(color)
#define COLOR_GET_3F(color)		COLOR_GET_RED(color), COLOR_GET_GREEN(color), COLOR_GET_BLUE(color)

// ############ MEMORY ###########

#if defined(nextai_USE_MEMORY_DEBUGGER)
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

#ifdef SYSTEM_LINUX
#define WCHAR wchar_t
#define CHAR char

#define TRUE 1
#define FALSE 0

#define LONG long

#define INT_MAX       2147483647    /* maximum (signed) int value */

#endif

#if 0
#if !MB_LEN_MAX
#define MB_LEN_MAX    5             /* max. # bytes in multibyte char */
#endif

#if ! SHRT_MIN
#define SHRT_MIN    (-32768)        /* minimum (signed) short value */
#endif

#if !SHRT_MAX
#define SHRT_MAX      32767         /* maximum (signed) short value */
#endif

#if !USHRT_MAX
#define USHRT_MAX     0xffff        /* maximum unsigned short value */
#endif

#if !INT_MIN
#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#endif

#if !INT_MAX

#endif

#if !UINT_MAX
#define UINT_MAX      0xffffffff    /* maximum unsigned int value */
#endif

#if !LONG_MIN
#define LONG_MIN    (-2147483647L - 1) /* minimum (signed) long value */
#endif

#if !LONG_MAX
#define LONG_MAX      2147483647L   /* maximum (signed) long value */
#endif

#if !ULONG_MAX
#define ULONG_MAX     0xffffffffUL  /* maximum unsigned long value */
#endif

#if !LLONG_MAX
#define LLONG_MAX     9223372036854775807i64       /* maximum signed long long int value */
#endif

#if !LLONG_MIN
#define LLONG_MIN   (-9223372036854775807i64 - 1)  /* minimum signed long long int value */
#endif

#if !ULLONG_MAX
#define ULLONG_MAX    0xffffffffffffffffui64       /* maximum unsigned long long int value */
#endif
#endif

#define D_USE_STD_STRING

#endif // !_nextai_BASIC_DEFINE_H_
