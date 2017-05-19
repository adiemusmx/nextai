#include "ComType.h"

bool IntPointDataModel::operator==(const Point& point)
{
	if (m_x == point.m_x && m_y == point.m_y)
		return true;
	else
		return false;
}

IntPointDataModel& IntPointDataModel::operator=(const Point& point)
{
	m_x = point.m_x;
	m_y = point.m_y;
	return *this;
}

IntPointDataModel::IntPointDataModel(INT32 x, INT32 y)
{
	m_x = x;
	m_y = y;
}

IntPointDataModel::IntPointDataModel(const Point& rect)
{
	m_x = rect.m_x;
	m_y = rect.m_y;
}

bool Rect::operator==(const Rect& rect)
{
	if (m_leftTop == rect.m_leftTop && m_rightBottom == rect.m_rightBottom)
		return true;
	else
		return false;
}

Rect& Rect::operator=(const Rect& point)
{
	m_leftTop = point.m_leftTop;
	m_rightBottom = point.m_rightBottom;
	return *this;
}

bool Rect::isInArea(const IntPointDataModel point)
{
	if (m_leftTop.m_x <= point.m_x && m_rightBottom.m_x >= point.m_x &&
		m_leftTop.m_y <= point.m_y && m_rightBottom.m_y >= point.m_y)
		return true;
	else
		return false;
}

Rect::Rect(IntPointDataModel leftTop, IntPointDataModel rightBottom)
{
	m_leftTop = leftTop;
	m_rightBottom = rightBottom;
}

Rect::Rect(INT32 left, INT32 top, INT32 width, INT32 height)
{
	m_leftTop.m_x = left;
	m_leftTop.m_y = top;
	m_rightBottom.m_x = left + width;
	m_rightBottom.m_y = top + height;
}

Rect::Rect(const Rect& rect)
{
	m_leftTop = rect.m_leftTop;
	m_rightBottom = rect.m_rightBottom;
}
