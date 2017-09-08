#pragma once

// Max length of file's path
#define FILE_PATH_MAX_LENGTH 1024

// Max length of text
#define TEXT_MAX_LENGTH 512

// Disable class' copy constructor.
#define DISABLE_CLASS_COPY(typeName) \
	typeName(const typeName&); typeName& operator=(const typeName&)

// Compare point.
#define POINT_equals(p,q) \
	(p.x == q.x && p.y == q.y)

// Return whether the point p is in rect r
#define RECT_testPOINT(r, p) \
	(r.left <= p.x && r.right >= p.x && r.top <= p.y && r.bottom >= p.y)

#define element_of(x) \
	(sizeof(x) / sizeof(x[0]))

#define WINDOWS_POSITION_LEFT 100
#define WINDOWS_POSITION_TOP 100

#define WINDOWS_WIDTH 1024
#define WINDOWS_HEIGHT 768