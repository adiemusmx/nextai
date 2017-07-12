#pragma once
#include "common_types.h"
#include <vector>

namespace Trinity {

// ����ID
typedef int32 ObjectId;

class WidgetObject
{
public:
	WidgetObject(ObjectId id);
	virtual ~WidgetObject();

	BOOL operator==(const WidgetObject& obj) { return (m_id == obj.m_id); }

	// ��ȡID
	void setId(ObjectId id) { m_id = id; }
	ObjectId getId() { return m_id; }

	// �趨/ȡ������
	virtual void setArea(const RECT& area);
	virtual const RECT& getArea();

	// �軭���
	virtual void draw();
	virtual void drawImpl();

	// ������
	virtual BOOL hit();
	virtual BOOL hitImpl();

	// �Ƿ���ʾ
	virtual void setVisible(BOOL visible);
	virtual BOOL getVisible();

	// �Ƿ�֧�ֵ��
	virtual void setHitEnable(BOOL hitEnable);
	virtual BOOL getHitEnable();

	// �Ƿ�֧�ֵ����͸
	virtual void setHitTransEnable(BOOL hitTransEnable);
	virtual BOOL getHitTransEnable();

	// �Ӷ�����ز���
	void addChild(WidgetObject* child);
	void removeChild(WidgetObject* child);
	BOOL isChild(WidgetObject* child);

	// ��ID���������������ݹ��ӿؼ���
	WidgetObject* getObjectById(ObjectId id);

private:
	// ��ֹ����
	WidgetObject(const WidgetObject& obj);
	WidgetObject& operator=(const WidgetObject& obj);

	// ���ؼ���Ҫ����ˢ��
	void invalidate();
	BOOL isNeedsRefresh();

private:
	// ����ΨһID�����ڼ���
	ObjectId m_id;

	// �趨�ؼ�����
	RECT m_area;

	// �Ӷ���
	std::vector<WidgetObject*> m_children;

	// �Ƿ���hit��Ϣ
	BOOL m_isHitEnable;

	// �Ƿ񴫵�hit��Ϣ
	BOOL m_isHitTrans;

	// �Ƿ��ܹ������軭
	BOOL m_visible;

	// �Ƿ���Ҫˢ��
	BOOL m_needsRefresh;
};

}