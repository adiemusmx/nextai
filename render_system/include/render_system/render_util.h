#include "base/mapbar_basic_types.h"

namespace MapBarDL
{
	class RenderUtil
	{
	public:
		/* �����ͷ������ */
		static size_t getArrowOutline(
			const Point* points,	/* �������Ϣ */
			size_t points_size,	/* ��������� */
			Point* outline,		/* �������Ϣ */
			size_t outline_size,	/* ��������� */
			float trunk_width,		/* �����߿� */
			float arrow_width,		/* ��ͷ�߿� */
			float arrow_height	/* ��ͷ�߶� */
			);

		/* �����ͷ����߿� */
		static size_t getArrowBorderOutline(
			const Point* points,	/* �������Ϣ */
			size_t points_size,	/* ��������� */
			Point* outline,		/* �������Ϣ */
			size_t outline_size,	/* ��������� */
			float trunk_width,		/* �����߿� */
			float arrow_width,		/* ��ͷ�߿� */
			float arrow_height,	/* ��ͷ�߶� */
			float border_width	/* �߿�Ŀ�� */
			);
	};
}