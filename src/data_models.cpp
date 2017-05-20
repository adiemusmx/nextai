#include "data_models.h"

namespace Trinity {

	void DataModel::addListener(DataModelListener* listener) {
		m_listeners.push_back(listener);
	}

	void DataModel::removeListener(DataModelListener* listener) {
		for (std::vector<DataModelListener*>::iterator i = m_listeners.begin(); i != m_listeners.end(); ++i) {
			if ((DataModelListener*)*i == listener) {
				m_listeners.erase(i);
				return;
			}
		}
	}

	void DataModel::notify() {
		for (std::vector<DataModelListener*>::iterator i = m_listeners.begin(); i != m_listeners.end(); ++i) {
			((DataModelListener*)*i)->onChanged(this);
		}
	}

	template <class T>
	PointDataModel<T>::PointDataModel() {
	}

	template <class T>
	PointDataModel<T>::PointDataModel(const T& x, const T& y) {
		m_x = x;
		m_y = y;
	}

	template <class T>
	PointDataModel<T>::PointDataModel(const PointDataModel& point) {
		m_x = point.m_x;
		m_y = point.m_y;
	}

	template <class T>
	PointDataModel<T>::~PointDataModel() {
	}

	template <class T>
	BOOL PointDataModel<T>::operator==(const PointDataModel<T> &point) {
		return (point.m_x == m_x && point.m_y == m_y);
	}

	template <class T>
	const PointDataModel<T>& PointDataModel<T>::operator=(const PointDataModel<T>& point) {
		m_x = point.m_x;
		m_y = point.m_y;
		return *this;
	}

	template <class T>
	void PointDataModel<T>::setValue(const T& x, const T& y) {
		m_x = x;
		m_y = y;
		notify();
	}

	template <class T>
	const PointDataModel<T>& PointDataModel<T>::getValue() {
		return *this;
	}

	RectDataModel::RectDataModel() {
	}

	RectDataModel::RectDataModel(POINT leftTop, POINT rightBottom) {
		m_leftTop = leftTop; m_rightBottom = rightBottom;
	}

	RectDataModel::RectDataModel(LONG left, LONG top, LONG width, LONG height) {
		m_leftTop.x = left;
		m_leftTop.y = top;
		m_rightBottom.x = left + width;
		m_rightBottom.y = top + height;
	}

	RectDataModel::RectDataModel(const RectDataModel &rect) {
		m_leftTop = rect.m_leftTop;
		m_rightBottom = rect.m_rightBottom;
	}

	BOOL RectDataModel::operator==(const RectDataModel& rect) {
		return (POINT_equals(m_leftTop, rect.m_leftTop) && POINT_equals(m_rightBottom, rect.m_rightBottom));
	}

	RectDataModel& RectDataModel::operator=(const RectDataModel& rect) {
		m_leftTop = rect.m_leftTop;
		m_rightBottom = rect.m_rightBottom;
		return *this;
	}

	BOOL RectDataModel::testPoint(const POINT& point) {
		return (m_leftTop.x < point.x && m_rightBottom.x > point.x && m_leftTop.y < point.y && m_rightBottom.y > point.y);
	}

	void RectDataModel::setValue(POINT leftTop, POINT rightBottom) {
		m_leftTop = leftTop;
		m_rightBottom = rightBottom;
		notify();
	}

	void RectDataModel::setValue(LONG left, LONG top, LONG width, LONG height) {
		m_leftTop.x = left;
		m_leftTop.y = top;
		m_rightBottom.x = left + width;
		m_rightBottom.y = top + height;
		notify();
	}

	const RectDataModel& RectDataModel::getValue() {
		return *this;
	}

}