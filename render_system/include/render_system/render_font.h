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
		Font();
		virtual ~Font();

		virtual void drawText(const ScreenPoint& pos, PixelColor color, const CHAR* text) const = 0;
		virtual void drawText(const ScreenPoint& pos, PixelColor color, const WCHAR* text) const = 0;

	protected:
		/* Disable copy constructor and operator= */
		Font(const Font&);
		Font& operator=(const Font&);
	};

	/* Alloc font object with CreateFontA */
	class WindowsFont : public Font
	{
	public:
		/* Alloc and release windows font object */
		static Font* allocFont();
		static Font* allocFont(int32 height, const CHAR* pszFaceName);
		static Font* allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
			FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
			FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
			FontQuality quality, FontPitchAndFamily pitchAndFamily, const CHAR* pszFaceName);
		static void release(Font* font);

		/* Constructor */
		WindowsFont(int32 height, int32 width, int32 escapement, int32 orientation, 
			FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut, 
			FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision, 
			FontQuality quality, FontPitchAndFamily pitchAndFamily, const CHAR* pszFaceName);
		
		virtual ~WindowsFont();

		void drawText(const ScreenPoint& pos, PixelColor color, const CHAR* text) const;
		void drawText(const ScreenPoint& pos, PixelColor color, const WCHAR* text) const;

	private:
		void init();
		void cleanup();

		/* Disable copy constructor and operator= */
		WindowsFont(WindowsFont&);
		WindowsFont& operator=(WindowsFont&);

#ifdef SYSTEM_WINDOWS
		HFONT m_handle;
#endif
		TEXT_TEXTURE_ID m_texture;
		int32 m_height;
	};

	class FreeTypeFont : public Font
	{
	public:
		/* Alloc and release freetype font object */
		static Font* allocFont();
		static Font* allocFont(int32 height, const CHAR* pszFaceName);
		static Font* allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
			FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
			FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
			FontQuality quality, FontPitchAndFamily pitchAndFamily, const CHAR* pszFaceName);

		FreeTypeFont();
		virtual ~FreeTypeFont();

		void drawText(const ScreenPoint& pos, PixelColor color, const CHAR* text) const;
		void drawText(const ScreenPoint& pos, PixelColor color, const WCHAR* text) const;

	private:
		/* Disable copy constructor and operator= */
		FreeTypeFont(FreeTypeFont&);
		FreeTypeFont& operator=(FreeTypeFont&);
	};
}

#endif // !_NEXTAI_RENDER_FONT_H_