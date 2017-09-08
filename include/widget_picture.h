#pragma once

#include "common_define.h"
#include "gl_bitmap.h"
#include "widget_object.h"

namespace Trinity {

class WidgetPicture : public WidgetObject
{
public:
	WidgetPicture(ObjectId id);
	virtual ~WidgetPicture();

	// �趨/ȡ������
	virtual void setArea(const RECT& area);

	// �����軭����
	virtual void drawImpl();

private:
	DISABLE_CLASS_COPY(WidgetPicture);

private:
	GL_Bitmap* m_bmp;
};
}