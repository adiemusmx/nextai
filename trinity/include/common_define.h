#pragma once

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


#define element_of(x) \
	(sizeof(x) / sizeof(x[0]))

#define WINDOWS_POSITION_LEFT 100
#define WINDOWS_POSITION_TOP 100

#define WINDOWS_WIDTH 1024
#define WINDOWS_HEIGHT 768