#pragma once

// max length of file path
#define D_FILE_PATH_MAX_LENGTH 1024

// max length of text
#define D_TEXT_MAX_LENGTH 512

// Disable class' copy constructor.
#define CLASS_disableCopy(typeName)	\
    typeName(const typeName &);		\
    typeName &operator=(const typeName &);

// Compare point.
#define POINT_equals(p,q)			\
	(p.x == q.x && p.y == q.y)

// Return whether the point p is in rect r
#define RECT_testPOINT(r, p)		\
	(r.left <= p.x && r.right >= p.x	\
	&& r.top <= p.y && r.bottom >= p.y)

#define element_of(x)				\
	(sizeof(x) / sizeof(x[0]))

#define SCREEN_AREA_LEFT 100
#define SCREEN_AREA_TOP 100

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480