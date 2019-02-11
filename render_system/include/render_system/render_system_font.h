#ifndef _NEXTAI_RENDER_FONT_H_
#define _NEXTAI_RENDER_FONT_H_

#include "base/nextai_basic_types.h"
#include "render_system/render_system_types.h"

namespace NextAI
{
	enum FontWeight
	{
		FontWeight_dontCare		= 0,
		FontWeight_thin			= 100,
		FontWeight_extraLight	= 200,
		FontWeight_light		= 300,
		FontWeight_normal		= 400,
		FontWeight_medium		= 500,
		FontWeight_semiBold		= 600,
		FontWeight_bold			= 700,
		FontWeight_extraBold	= 800,
		FontWeight_heavy		= 900,
	};
	
	enum FontCharset
	{
		FontCharset_ansi		= 0,
		FontCharset_default		= 1,
		FontCharset_symbol		= 2,
		FontCharset_shiftJIS	= 128,
		FontCharset_hangEUL		= 129,
		FontCharset_hangUL		= 129,
		FontCharset_gb2312		= 134,
		FontCharset_chineseBig5	= 136,
		FontCharset_oem			= 255,
		FontCharset_johab		= 130,
		FontCharset_hebrew		= 177,
		FontCharset_arabic		= 178,
		FontCharset_greek		= 161,
		FontCharset_turkish		= 162,
		FontCharset_vietnamese	= 163,
		FontCharset_thai		= 222,
		FontCharset_eastEurope	= 238,
		FontCharset_russian		= 204,
		FontCharset_mac			= 77,
		FontCharset_baltic		= 186,
	};
	
#define FontPitchAndFamily		int32
	
#define FontPitch_default		0
#define FontPitch_fixed			1
#define FontPitch_variable		(1 << 1)
#define FontPitch_mono			(1 << 3)
#define FontFamily_DONTCARE		(0 << 4)  /* Don't care or don't know. */
#define FontFamily_ROMAN		(1 << 4)  /* Variable stroke width, serifed. */
	/* Times Roman, Century Schoolbook, etc. */
#define FontFamily_SWISS		(2 << 4)  /* Variable stroke width, sans-serifed. */
	/* Helvetica, Swiss, etc. */
#define FontFamily_MODERN		(3 << 4)  /* Constant stroke width, serifed or sans-serifed. */
	/* Pica, Elite, Courier, etc. */
#define FontFamily_SCRIPT		(4 << 4)  /* Cursive, etc. */
#define FontFamily_DECORATIVE	(5 << 4)  /* Old English, etc. */
	
	enum FontOutPrecision
	{
		FontOutPrecision_default			= 0,
		FontOutPrecision_string				= 1,
		FontOutPrecision_character			= 2,
		FontOutPrecision_stroke				= 3,
		FontOutPrecision_tt					= 4,
		FontOutPrecision_device				= 5,
		FontOutPrecision_raster				= 6,
		FontOutPrecision_tt_only			= 7,
		FontOutPrecision_outline			= 8,
		FontOutPrecision_screen_outline		= 9,
		FontOutPrecision_ps_only			= 10,
	};
	
#define FontClipPrecision					int32
#define FontClipPrecision_character			1
#define FontClipPrecision_default			0
#define FontClipPrecision_stroke			2
#define FontClipPrecision_mask				0xf
#define FontClipPrecision_LH_angel			(1 << 4)
#define FontClipPrecision_TT_always			(2 << 4)
#define FontClipPrecision_dfa_disable		(4 << 4)
#define FontClipPrecision_embedded			(8 << 4)
	
	enum FontQuality
	{
		FontQuality_default			= 0,
		FontQuality_draft			= 1,
		FontQuality_proof			= 2,
		FontQuality_nonAntialiased	= 3,
		FontQuality_Antialiased		= 4,
	};
	
#define FONT_TEXTURE_MAX_SIZE 512
	
	class Font
	{
	public:
	
		/* 构造和析构函数 */
		Font();
		virtual ~Font();
		
		/* 名称 */
		virtual std::string getName() = 0;
		
		/* 高度 */
		virtual int32 getHeight() = 0;
		
		/* 描画 */
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const std::string& text) const = 0;
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const std::wstring& text) const = 0;
		
	protected:
	
		/* 禁用拷贝 */
		DISABLE_CLASS_COPY(Font);
	};
	
	/* Alloc font object with CreateFontA */
	class WindowsFont : public Font
	{
	public:
	
		/* 创建字体 */
		static Font* allocFont();
		static Font* allocFont(int32 height, const std::string& pszFaceName);
		static Font* allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
							   FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
							   FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
							   FontQuality quality, FontPitchAndFamily pitchAndFamily, const std::string& pszFaceName);
		static void release(Font* font);
		
		/* 构造和析构函数 */
		WindowsFont(int32 height, int32 width, int32 escapement, int32 orientation,
					FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
					FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
					FontQuality quality, FontPitchAndFamily pitchAndFamily, const std::string& pszFaceName);
					
		virtual ~WindowsFont();
		
		/* 名称 */
		virtual std::string getName() { return m_name; }
		
		/* 高度 */
		virtual int32 getHeight() { return m_height; }
		
		/* 描画 */
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const std::string& text) const;
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const std::wstring& text) const;
		
	private:
	
		/* 初始化和销毁 */
		void init();
		void cleanup();
		
		/* 禁用拷贝 */
		DISABLE_CLASS_COPY(WindowsFont);
		
#ifdef SYSTEM_WINDOWS
		HFONT m_handle;					/* 句柄 */
#endif
		TEXT_TEXTURE_ID m_texture;		/* 纹理 */
		
		std::string m_name;				/* 名称 */
		int32 m_height;					/* 高度 */
	};
	
	class FreeTypeFont : public Font
	{
	public:
	
		/* 创建字体 */
		static Font* allocFont();
		static Font* allocFont(int32 height, const std::string& pszFaceName);
		static Font* allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
							   FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
							   FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
							   FontQuality quality, FontPitchAndFamily pitchAndFamily, const std::string& pszFaceName);
							   
		/* 构造和析构函数 */
		FreeTypeFont();
		virtual ~FreeTypeFont();
		
		/* 名称 */
		virtual std::string getName() { return m_name; }
		
		/* 高度 */
		virtual int32 getHeight() { return m_height; }
		
		/* 描画 */
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const std::string& text) const;
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const std::wstring& text) const;
		
	private:
	
		/* 禁用拷贝 */
		DISABLE_CLASS_COPY(FreeTypeFont);
		
		std::string m_name;					/* 名称 */
		int32 m_height;						/* 高度 */
		
	};
}

#endif // !_NEXTAI_RENDER_FONT_H_