#ifndef _NEXTAI_RENDER_IMAGE_H_
#define _NEXTAI_RENDER_IMAGE_H_

#include "render_system/render_system_types.h"

struct FIBITMAP;

namespace NextAI
{
	class GLBITMAP;

	class FreeImage
	{
	public:
		static void init();
		static void cleanup();

		static PICTURE_TEXTURE_ID loadTexture(const WCHAR* filePath);

	private:
		static GLBITMAP * convFIBitmap2GLBitmap(FIBITMAP* fibmp);
		static void freeGLBitmap(GLBITMAP *glbmp);
	};
}

#endif // !_NEXTAI_RENDER_IMAGE_H_
