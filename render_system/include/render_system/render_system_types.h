#ifndef _MAPBAR_RENDER_SYSTEM_TYPES_H_
#define _MAPBAR_RENDER_SYSTEM_TYPES_H_

#include "base/mapbar_basic_types.h"
#include "base/mapbar_string.h"

namespace MapBarDL
{
	// Line Style
#define LINE_STYLE_1 0xFFFF			// 1111111111111111 --> ——————————————
#define LINE_STYLE_2 0xAAAA			// 1010101010101010 --> --------------
#define LINE_STYLE_3 0xCCCC			// 1100110011001100 --> ——  ——  ——  ——

#define INVALID_TEXTURE_ID (-1)
	typedef uint32 PICTURE_TEXTURE_ID;
	typedef uint32 TEXT_TEXTURE_ID;

	// Polygon Mode
	enum POLYGON_MODE
	{
		POLYGON_MODE_POINT,		// 表示只显示顶点，多边形用点显示
		POLYGON_MODE_LINE,		// 表示显示线段，多边形用轮廓显示
		POLYGON_MODE_FILL		// 表示显示面，多边形采用填充形式
	};
}

#endif // !_MAPBAR_RENDER_SYSTEM_TYPES_H_