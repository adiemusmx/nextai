#pragma once

typedef int32 ObjectId;

class WidgetObject
{
public:
	WidgetObject();
	~WidgetObject();
	WidgetObject(const WidgetObject& obj);
	WidgetObject& operator=(const WidgetObject& obj);


private:
	ObjectId m_id;  // Object's id.
}