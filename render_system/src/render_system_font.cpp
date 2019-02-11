#include "stdafx.h"
#include "render_system/render_system_font.h"

#include "base/nextai_basic_types.h"
#include "base/nextai_file_system.h"

#include "render_system/render_system.h"
#include "freetype/freetype.h"

namespace NextAI
{
	Font::Font()
	{
	}
	
	Font::~Font()
	{
	}
	
	Font* WindowsFont::allocFont()
	{
		Font* ret = NULL;
#ifdef SYSTEM_WINDOWS
		ret = new WindowsFont(13, 0, 0, 0, FontWeight_medium, 0, 0, 0,
							  FontCharset_gb2312, FontOutPrecision_default, FontClipPrecision_default,
							  FontQuality_default, FontPitch_default | FontFamily_SWISS, "楷体_GB2312");
#endif
		return ret;
	}
	
	Font* WindowsFont::allocFont(int32 height, const std::string& pszFaceName)
	{
		Font* ret = NULL;
#ifdef SYSTEM_WINDOWS
		ret = new WindowsFont(height, 0, 0, 0, FontWeight_medium, 0, 0, 0,
							  FontCharset_gb2312, FontOutPrecision_default, FontClipPrecision_default,
							  FontQuality_default, FontPitch_default | FontFamily_SWISS, pszFaceName);
#endif
		return ret;
	}
	
	Font* WindowsFont::allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
								 FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
								 FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
								 FontQuality quality, FontPitchAndFamily pitchAndFamily, const std::string& pszFaceName)
	{
		Font* ret = NULL;
#ifdef SYSTEM_WINDOWS
		ret = new WindowsFont(height, width, escapement, orientation,
							  weight, italic, underline, strikeOut,
							  charSet, outPrecision, clipPrecision,
							  quality, pitchAndFamily, pszFaceName);
#endif
		return ret;
	}
	
	void WindowsFont::release(Font* font)
	{
		if (font != NULL)
		{
			delete font;
		}
	}
	
	WindowsFont::WindowsFont(int32 height, int32 width, int32 escapement, int32 orientation,
							 FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
							 FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
							 FontQuality quality, FontPitchAndFamily pitchAndFamily, const std::string& pszFaceName)
	{
		m_texture = INVALID_TEXTURE_ID;
		m_name = pszFaceName;
		m_height = height;
#ifdef SYSTEM_WINDOWS
		m_handle = CreateFontA(
					   height, width, escapement, orientation,
					   weight,	italic, underline, strikeOut, charSet,
					   outPrecision, clipPrecision, quality,
					   pitchAndFamily, pszFaceName.c_str());
#endif
		init();
	}
	
	WindowsFont::~WindowsFont()
	{
	}
	
	void WindowsFont::drawText(const ScreenPoint& pos, PixelColor color, const std::string& text) const
	{
#ifdef SYSTEM_WINDOWS
		HDC hDC = wglGetCurrentDC();
		size_t length = text.size();
		length = (length > FONT_TEXTURE_MAX_SIZE ? FONT_TEXTURE_MAX_SIZE : length);
		HFONT oldFont = (HFONT)SelectObject(hDC, m_handle);
		glColor4f(COLOR_GET_4F(color));
		glRasterPos2i(pos.x, pos.y + m_height);
		
		for (size_t loopIdx = 0; loopIdx < length; ++loopIdx)
		{
			wglUseFontBitmapsA(hDC, text[loopIdx], 1, m_texture + loopIdx);
			glCallList(m_texture + loopIdx);
		}
		
		glFlush();
		SelectObject(hDC, oldFont);
#endif
	}
	
	void WindowsFont::drawText(const ScreenPoint& pos, PixelColor color, const std::wstring& text) const
	{
#ifdef SYSTEM_WINDOWS
		HDC hDC = wglGetCurrentDC();
		size_t length = text.length();
		length = (length > FONT_TEXTURE_MAX_SIZE ? FONT_TEXTURE_MAX_SIZE : length);
		HFONT oldFont = (HFONT)SelectObject(hDC, m_handle);
		glColor4f(COLOR_GET_4F(color));
		glRasterPos2i(pos.x, pos.y + m_height);
		
		for (size_t loopIdx = 0; loopIdx <= length; ++loopIdx)
		{
			wglUseFontBitmapsW(hDC, text[loopIdx], 1, m_texture + loopIdx);
			glCallList(m_texture + loopIdx);
		}
		
		glFlush();
		SelectObject(hDC, oldFont);
#endif
	}
	
	void WindowsFont::init()
	{
		m_texture = glGenLists(FONT_TEXTURE_MAX_SIZE);
	}
	
	void WindowsFont::cleanup()
	{
		if (m_texture != INVALID_TEXTURE_ID)
		{
			glDeleteLists(m_texture, FONT_TEXTURE_MAX_SIZE);
			m_texture = INVALID_TEXTURE_ID;
		}
	}
	
	Font* FreeTypeFont::allocFont() { return NULL; }
	Font* FreeTypeFont::allocFont(int32 height, const std::string& pszFaceName) { return NULL; }
	Font* FreeTypeFont::allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
								  FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
								  FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
								  FontQuality quality, FontPitchAndFamily pitchAndFamily, const std::string& pszFaceName)
	{
		return NULL;
	}
	
	FreeTypeFont::FreeTypeFont()
	{
		m_name = "";
		m_height = 0;
	}
	
	FreeTypeFont::~FreeTypeFont() {}
	
	void FreeTypeFont::drawText(const ScreenPoint& pos, PixelColor color, const std::string& text) const
	{
		/* TODO */
	}
	
	void FreeTypeFont::drawText(const ScreenPoint& pos, PixelColor color, const std::wstring& text) const
	{
		/* TODO */
	}
}
