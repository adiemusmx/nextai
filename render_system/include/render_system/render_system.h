#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#define RENDER_SYSTEM() MapBarDL::RenderSystem::instance()

namespace MapBarDL {

	// Line Style
#define LINE_STYLE_1 0xFFFF			// 1111111111111111 --> ——————————————
#define LINE_STYLE_2 0xAAAA			// 1010101010101010 --> --------------
#define LINE_STYLE_3 0xCCCC			// 1100110011001100 --> ——  ——  ——  ——

#define INVALID_TEXTURE_ID (-1)
typedef uint32 TEXTURE_ID;

	// Polygon Mode
	enum POLYGON_MODE
	{
		POLYGON_MODE_POINT,		// 表示只显示顶点，多边形用点显示
		POLYGON_MODE_LINE,		// 表示显示线段，多边形用轮廓显示
		POLYGON_MODE_FILL		// 表示显示面，多边形采用填充形式
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

		// Texture (allocTexture函数的oldTextureId会被release，无需外部调用releaseTexture)
		TEXTURE_ID allocTexture(const CHAR* fileName, TEXTURE_ID oldTextureId = INVALID_TEXTURE_ID);
		void releaseTexture(TEXTURE_ID textureId);

		// Line
		void drawPolyLine(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor);

		// Polygon
		void drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, ColorCode lineColor, POLYGON_MODE polygonMode);

		// Picture
		void drawPicture(TEXTURE_ID textureId, const Rect& drawArea);

	private:
		// Constructor
		RenderSystem();
		virtual ~RenderSystem();

		// Disable copy constructor
		DISABLE_CLASS_COPY(RenderSystem);

		// Load bmp file
		BOOL loadBmpFile(const CHAR* bmpFile, size_t& width, size_t& height, CHAR** data);
	};
}

#endif // !_RENDER_SYSTEM_H_