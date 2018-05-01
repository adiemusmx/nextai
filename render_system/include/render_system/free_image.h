#ifndef _MAPBAR_FREE_IMAGE_H_
#define _MAPBAR_FREE_IMAGE_H_

#include "render_system/render_system_types.h"

struct FIBITMAP;

namespace MapBarDL
{
	class GLBITMAP;

	class FreeImage
	{
	public:
		static PICTURE_TEXTURE_ID loadTexture(const MbString& filePath);

	private:
		static GLBITMAP * convFIBitmap2GLBitmap(FIBITMAP* fibmp);
		static void freeGLBitmap(GLBITMAP *glbmp);
	};
}

#endif // !_MAPBAR_FREE_IMAGE_H_