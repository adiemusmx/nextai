#ifndef _NEXTAI_RENDER_SYSTEM_H_
#define _NEXTAI_RENDER_SYSTEM_H_

#include "render_system/render_font.h"
#include "render_system/render_system_types.h"

#define RENDER_SYSTEM() NextAI::RenderSystem::instance()

namespace NextAI {

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

	/* Render System */
	class RenderSystem
	{

	public:
		/* 单例模式 */
		static RenderSystem* instance();

		/* 初始化和析构 */
		void init();
		void cleanup();

		/* Point描画 */
		void drawPoint(const Point& point, float pointSize, PixelColor pointColor);

		/* Line描画 */
		void drawPolyLine(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor);
		void drawPolyLine(const std::vector<Point>& points, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor);

		/* Polygon描画 */
		void drawPolygon(const Point* points, size_t pointsCount, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode);
		void drawPolygon(const std::vector<Point>& points, float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode);

		/* 
		 * Picture描画
		 * allocTexture函数的oldTextureId会被release，无需外部调用releaseTexture 
		 */
		PICTURE_TEXTURE_ID allocPictureTexture(const WCHAR* fileName, PICTURE_TEXTURE_ID oldTextureId = INVALID_TEXTURE_ID);
		void releasePictureTexture(PICTURE_TEXTURE_ID textureId);
		void drawPicture(PICTURE_TEXTURE_ID textureId, const Rect& drawArea);

		/* 
		 * Text描画
		 * allocTexture函数的oldTextureId会被release，无需外部调用releaseTexture 
		 */
		void drawText(const Font* font, const Point& pos, PixelColor color, const CHAR* text);
		void drawText(const Font* font, const Point& pos, PixelColor color, const WCHAR* text);

	private:
		/* 构造函数和析构函数 */
		RenderSystem();
		virtual ~RenderSystem();

		/* 禁止拷贝函数 */
		DISABLE_CLASS_COPY(RenderSystem);

		/* 内部准备环境 */
		void beginDrawPolyLine(float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor);
		void endDrawPolyLine();

		void beginDrawPolygon(float lineWidth, int32 lineStyleFactor, int32 lineStyle, PixelColor lineColor, POLYGON_MODE polygonMode);
		void endDrawPolygon();
	};
}

#endif // !_NEXTAI_RENDER_SYSTEM_H_
