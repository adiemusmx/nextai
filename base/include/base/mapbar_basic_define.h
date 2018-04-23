#ifndef _MAPBAR_BASIC_DEFINE_H_
#define _MAPBAR_BASIC_DEFINE_H_

#include "base/mapbar_basic_types.h"

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
#define RECT_testPOINT(r, p) \
	(r.left <= p.x && r.right >= p.x && r.top <= p.y && r.bottom >= p.y)

#define RECT_getHeight(r) \
	(r.bottom - r.top)

#define RECT_getWidth(r) \
	(r.right - r.left)

#define RECT_invalidate(r) \
	r.left = r.top = r.right = r.bottom = 0

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

#define MbAssert(expr) assert(expr)

#endif // !_MAPBAR_BASIC_DEFINE_H_