#ifndef _TRINITY_GL_BITMAP_H_
#define _TRINITY_GL_BITMAP_H_

#include "base/mapbar_basic_define.h"
#include "base/mapbar_basic_types.h"

namespace MapBarDL {

class GL_Bitmap
{
public:
	GL_Bitmap(const char* fileName);
	virtual ~GL_Bitmap();

	// Set the path of the bitmap file.
	BOOL setPath(const char* fileName);

	// Set control's area
	virtual void setArea(const Rect& area);
	virtual const Rect& getArea();

	// Draw function
	void draw();

private:
	uint32 getTexture();

private:
	void generateTexture();

	size_t m_width;
	size_t m_height;

	CHAR* m_data;
	Rect m_area;

	uint32 m_texture;
};

}

#endif // !_TRINITY_GL_BITMAP_H_