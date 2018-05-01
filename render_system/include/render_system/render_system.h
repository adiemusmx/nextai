#ifndef _MAPBAR_RENDER_SYSTEM_H_
#define _MAPBAR_RENDER_SYSTEM_H_

#include "base/mapbar_string.h"
#include "render_system/render_system_types.h"

#define RENDER_SYSTEM() MapBarDL::RenderSystem::instance()

namespace MapBarDL {

	class TextTextureInfo
	{
	public:
		TextTextureInfo()
		{
			texture = INVALID_TEXTURE_ID;
			num = 0;
		}

		TEXT_TEXTURE_ID texture;
		size_t num;
	};

	// Render System
	class RenderSystem
	{

	public:
		// Get the instance of the app service.
		static RenderSystem* instance();

		// Initialize
		void init();
		void cleanup();

		// Point
		void drawPoint(const Point& point, float pointSize, ColorCode pointColor);

		// Line
		void drawPolyLine(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor);

		// Polygon
		void drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor, POLYGON_MODE polygonMode);

		// Picture (allocTexture函数的oldTextureId会被release，无需外部调用releaseTexture)
		PICTURE_TEXTURE_ID allocPictureTexture(const MbString& fileName, PICTURE_TEXTURE_ID oldTextureId = INVALID_TEXTURE_ID);
		void releasePictureTexture(PICTURE_TEXTURE_ID textureId);
		void drawPicture(PICTURE_TEXTURE_ID& textureId, const Rect& drawArea);

		// Text (allocTexture函数的oldTextureId会被release，无需外部调用releaseTexture)
		TextTextureInfo allocTextTexture(const MbString& str);
		void releaseTextTexture(TextTextureInfo& info);
		void drawText(const TextTextureInfo& info, const Rect& drawArea);

	private:
		// Constructor
		RenderSystem();
		virtual ~RenderSystem();

		// Disable copy constructor
		DISABLE_CLASS_COPY(RenderSystem);

		
	};
}

#endif // !_MAPBAR_RENDER_SYSTEM_H_