#ifndef _TRINITY_WIDGET_PICTURE_H_
#define _TRINITY_WIDGET_PICTURE_H_


#include "trinity_gl_bitmap.h"
#include "trinity_widget_object.h"

namespace NextAI
{

class WidgetPicture : public WidgetObject
{
public:
	WidgetPicture(ObjectId id);
	virtual ~WidgetPicture();

	// Draw function
	virtual void drawImpl();

	// Set/get drawable area.
	virtual void setDrawableArea(const Rect& area);

	// Set path of the bmp file.
	virtual void setPath(const CHAR* path);

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetPicture);

private:
	GL_Bitmap* m_bmp;
};
}

#endif // !_TRINITY_WIDGET_PICTURE_H_