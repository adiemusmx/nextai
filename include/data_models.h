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
		void addListener(DataModelListener* listener) { m_listeners.push_back(listener); }
		void removeListener(DataModelListener* listener) {
			for (std::iterator i = m_listeners.begin(); i != m_listeners.end(); ++i) {
				if ((DataModelListener*)*i == listener) {
					m_listeners.erase(i);
					return;
				}
			}
		}

	private:
		void notify() {
			for (std::iterator i = m_listeners.begin(); i != m_listeners.end(); ++i) {
				((DataModelListener*)*i).onChanged(this);
			}
		}

		std::vector<DataModelListener*> m_listeners;
	};

	template <typename>
	class PointDataModel : public DataModel {
	public:
		// 构造函数
		PointDataModel() {}
		PointDataModel(typename x, typename y) { m_x = x; m_y = y; }
		PointDataModel(const PointDataModel& point) { m_x = point.m_x; m_y = point.m_y; }
		~PointDataModel() {}

		// 重载操作符
		BOOL operator==(const PointDataModel &point) { return (point.m_x == m_x && point.m_y == m_y); }
		const PointDataModel& operator=(const PointDataModel& point) { m_x = point.m_x; m_y = point.m_y; return *this; }

		// 设定/取得
		void setValue(typename x, typename y) { m_x = x; m_y = y; notify(); }	// 触发onChanged消息
		const PointDataModel& getValue() { return *this; }

	private:
		// 基本数据
		typename m_x;
		typename m_y;
	};

	// 矩形
	class RectDataModel : public DataModel {
	public:
		// 构造函数
		RectDataModel() {}
		RectDataModel(POINT leftTop, POINT rightBottom) { m_leftTop = leftTop; m_rightBottom = rightBottom; }
		RectDataModel(LONG left, LONG top, LONG width, LONG height) {
			m_leftTop.x = left; m_leftTop.y = top; m_rightBottom.x = left + width; m_rightBottom.y = top + height;
		}
		RectDataModel(const RectDataModel &rect) {
			m_leftTop = rect.m_leftTop; m_rightBottom = rect.m_rightBottom;
		}

		// 重载操作符
		BOOL operator==(const RectDataModel& rect) {
			return (m_leftTop.x == rect.x && m_leftTop.y == rect.y && m_rightBottom.x == rect.x && m_rightBottom.y == rect.y);
		}
		RectDataModel& operator=(const RectDataModel& rect) {
			m_leftTop = rect.m_leftTop; m_rightBottom = rect.m_rightBottom;
		}

		// POINT是否在RECT里面
		BOOL testPoint(const POINT& point) {
			return (m_leftTop.x < point.x && m_rightBottom.x > point.x && m_leftTop.y < point.y && m_rightBottom.y > point.y);
		}

		// 设定/取得
		void setValue(POINT leftTop, POINT rightBottom) {
			m_leftTop = leftTop; m_rightBottom = rightBottom;
			notify();
		}
		void setValue(LONG left, LONG top, LONG width, LONG height) {
			m_leftTop.x = left; m_leftTop.y = top;
			m_rightBottom.x = left + width; m_rightBottom.y = top + height;
			notify();
		}
		const RectDataModel& getValue() { return *this; }

	private:
		// 基本数据
		POINT m_leftTop;
		POINT m_rightBottom;
	};
}