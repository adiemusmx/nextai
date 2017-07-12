#pragma once

#include "gl_bitmap.h"

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
	D_CLASS_DISABLE_COPY(WidgetPicture);

private:
	GL_Bitmap* m_bmp;
};
}