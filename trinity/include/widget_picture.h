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

	// Draw function
	virtual void drawImpl();

	// Set/get drawable area.
	virtual void setDrawableArea(const RECT& area);

	// Set path of the bmp file.
	virtual void WidgetPicture::setPath(const CHAR* path);

private:
	DISABLE_CLASS_COPY(WidgetPicture);

private:
	GL_Bitmap* m_bmp;
};
}