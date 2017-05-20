#pragma once

// 文件路径最大长度
#define D_FILE_PATH_MAX_LENGTH 1024

// 文本最大长度
#define D_TEXT_MAX_LENGTH 512

// 拷贝构造函数
#define CLASS_disableCopy(typeName)	\
    typeName(const typeName &);		\
    typeName &operator=(const typeName &);

// POINT比较
#define POINT_equals(p,q)			\
	(p.x == q.x && p.y == q.y)

// RECT是否包含POINT
#define RECT_testPOINT(r, p)		\
	(r.left <= p.x && r.right >= p.x	\
	&& r.top <= p.y && r.bottom >= p.y)

// 初始化结构体
#define STRUCT_invalid(x)			\
	memset(x, 0x00, sizeof(x))

#define ARRAY_LENGTH(x)				\
	(sizeof(x) / sizeof(x[0]))


#define SCREEN_AREA_LEFT 100
#define SCREEN_AREA_TOP 100

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480