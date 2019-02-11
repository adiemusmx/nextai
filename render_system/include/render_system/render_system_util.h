#include "base/nextai_basic_types.h"

namespace NextAI
{
	class RenderSystemUtil
	{
	public:
		/* 计算箭头的主干 */
		static size_t getArrowOutline(
			const Point* points,	/* 输入点信息 */
			size_t points_size,	/* 输入点数量 */
			Point* outline,		/* 输出点信息 */
			size_t outline_size,	/* 输出点数量 */
			float trunk_width,		/* 主干线宽 */
			float arrow_width,		/* 箭头线宽 */
			float arrow_height	/* 箭头高度 */
		);
		
		/* 计算箭头的外边框 */
		static size_t getArrowBorderOutline(
			const Point* points,	/* 输入点信息 */
			size_t points_size,	/* 输入点数量 */
			Point* outline,		/* 输出点信息 */
			size_t outline_size,	/* 输出点数量 */
			float trunk_width,		/* 主干线宽 */
			float arrow_width,		/* 箭头线宽 */
			float arrow_height,	/* 箭头高度 */
			float border_width	/* 边框的宽度 */
		);
	};
}