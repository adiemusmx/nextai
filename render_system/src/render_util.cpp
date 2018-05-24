#include "stdafx.h"
#include "render_system/render_util.h"

namespace NextAI
{
	size_t RenderUtil::getArrowOutline(
		const Point* points,
		size_t points_size,
		Point* outline,
		size_t outline_size,
		float trunk_width,
		float arrow_width,
		float arrow_height)
	{
		for (size_t loopIdx = 0; loopIdx < points_size - 1; ++loopIdx)
		{
			Segment s(points[loopIdx], points[loopIdx + 1]);
			
		}
		return 0;
	}

	size_t RenderUtil::getArrowBorderOutline(
		const Point* points,
		size_t points_size,
		Point* outline,
		size_t outline_size,
		float trunk_width,
		float arrow_width,
		float arrow_height,
		float border_width)
	{
		return 0;
	}
}