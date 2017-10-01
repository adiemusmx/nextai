#ifndef _TRINITY_DATA_MODELS_H_
#define _TRINITY_DATA_MODELS_H_

#include "trinity_common_types.h"
#include "trinity_common_define.h"
#include "vector"

namespace Trinity
{
class DataModel;

// Listener
class DataModelListener
{
public:
	virtual void onChanged(DataModel* dataModel) {}
};

class DataModel
{
public:
	void addListener(DataModelListener* listener);
	void removeListener(DataModelListener* listener);

	void notify();

private:
	std::vector<DataModelListener*> m_listeners;
};

template <class T>
class PointDataModel : public DataModel
{
public:
	// Constructor
	PointDataModel();
	PointDataModel(const T& x, const T& y);
	PointDataModel(const PointDataModel& point);
	~PointDataModel();

	// operator
	BOOL operator==(const PointDataModel& point);
	const PointDataModel& operator=(const PointDataModel& point);

	// setter/getter
	void setValue(const T& x, const T& y);	// 触发onChanged消息
	const PointDataModel& getValue();

private:
	// basic data
	T m_x;
	T m_y;
};

// Rect
class RectDataModel : public DataModel
{
public:
	// construtor
	RectDataModel();
	RectDataModel(POINT leftTop, POINT rightBottom);
	RectDataModel(LONG left, LONG top, LONG width, LONG height);
	RectDataModel(const RectDataModel& rect);

	// operator
	BOOL operator==(const RectDataModel& rect);
	RectDataModel& operator=(const RectDataModel& rect);

	// test point
	BOOL testPoint(const POINT& point);

	// setter/getter
	void setValue(POINT leftTop, POINT rightBottom);
	void setValue(LONG left, LONG top, LONG width, LONG height);
	const RectDataModel& getValue();

private:
	// basic data
	POINT m_leftTop;
	POINT m_rightBottom;
};
}

#endif // !_TRINITY_DATA_MODELS_H_