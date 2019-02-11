#ifndef _NEXTAI_RENDER_IMAGE_H_
#define _NEXTAI_RENDER_IMAGE_H_

#include "render_system/render_system_types.h"

struct FIBITMAP;

namespace NextAI
{
	class GLBITMAP;
	
	class Image
	{
	public:
		static void init();
		static void cleanup();
		
		static bool loadTexture(const std::wstring& filePath, PICTURE_TEXTURE_ID& texture);
		static bool loadTextures(const std::wstring& filePath, int32 count, std::vector<PICTURE_TEXTURE_ID>& textures);
	};
}

#endif // !_NEXTAI_RENDER_IMAGE_H_
