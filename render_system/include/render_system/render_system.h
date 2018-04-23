#ifndef _MAPBAR_RENDER_SYSTEM_H_
#define _MAPBAR_RENDER_SYSTEM_H_

#include "base/mapbar_string.h"
#include "render_system/render_system_types.h"

#define RENDER_SYSTEM() MapBarDL::RenderSystem::instance()

namespace MapBarDL {

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

		// Texture (allocTexture函数的oldTextureId会被release，无需外部调用releaseTexture)
		TEXTURE_ID allocTexture(const MbString& fileName, TEXTURE_ID oldTextureId = INVALID_TEXTURE_ID);
		void releaseTexture(TEXTURE_ID textureId);
		void drawTexture(TEXTURE_ID textureId, const Rect& drawArea);

	private:
		// Constructor
		RenderSystem();
		virtual ~RenderSystem();

		// Disable copy constructor
		DISABLE_CLASS_COPY(RenderSystem);

		// Load bmp file
		BOOL loadBmpFile(const MbString& bmpFile, size_t& width, size_t& height, CHAR** data);

		TEXTURE_ID allocBmpTexture(const MbString& fileName);
	};
}

#endif // !_MAPBAR_RENDER_SYSTEM_H_