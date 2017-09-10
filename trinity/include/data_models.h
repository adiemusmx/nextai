#pragma once

#include "common_types.h"
#include "common_define.h"
#include "vector"

namespace Trinity {
	class DataModel;

	// 监听者
	class DataModelListener {
	public:
		virtual void onChanged(DataModel* dataModel) {}
	};

	class DataModel {
	public:
		void addListener(DataModelListener* listener);
		void removeListener(DataModelListener* listener);

		void notify();

	private:
		std::vector<DataModelListener*> m_listeners;
	};

	template <class T>
	class PointDataModel : public DataModel {
	public:
		// 构造函数
		PointDataModel();
		PointDataModel(const T& x, const T& y);
		PointDataModel(const PointDataModel& point);
		~PointDataModel();

		// 重载操作符
		BOOL operator==(const PointDataModel &point);
		const PointDataModel& operator=(const PointDataModel& point);

		// 设定/取得
		void setValue(const T& x, const T& y);	// 触发onChanged消息
		const PointDataModel& getValue();

	private:
		// 基本数据
		T m_x;
		T m_y;
	};

	// 矩形
	class RectDataModel : public DataModel {
	public:
		// 构造函数
		RectDataModel();
		RectDataModel(POINT leftTop, POINT rightBottom);
		RectDataModel(LONG left, LONG top, LONG width, LONG height);
		RectDataModel(const RectDataModel &rect);

		// 重载操作符
		BOOL operator==(const RectDataModel& rect);
		RectDataModel& operator=(const RectDataModel& rect);

		// POINT是否在RECT里面
		BOOL testPoint(const POINT& point);

		// 设定/取得
		void setValue(POINT leftTop, POINT rightBottom);
		void setValue(LONG left, LONG top, LONG width, LONG height);
		const RectDataModel& getValue();

	private:
		// 基本数据
		POINT m_leftTop;
		POINT m_rightBottom;
	};
}