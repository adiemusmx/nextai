#include "stdafx.h"
#include "render_system/render_font.h"
#include "base/nextai_basic_define.h"
#include "render_system/render_system.h"

#ifdef SYSTEM_LINUX
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#endif

namespace NextAI
{
	Font* Font::allocFont()
	{
		Font* ret = NULL;
#ifdef SYSTEM_WINDOWS
		ret = new WindowsFont(13, 0, 0, 0, FontWeight_medium, 0, 0, 0,
			FontCharset_gb2312, FontOutPrecision_default, FontClipPrecision_default,
			FontQuality_default, FontPitch_default | FontFamily_SWISS, "楷体_GB2312");
#endif
		return ret;
	}

	Font* Font::allocFont(int32 height, const CHAR* pszFaceName)
	{
		Font* ret = NULL;
#ifdef SYSTEM_WINDOWS
		ret = new WindowsFont(height, 0, 0, 0, FontWeight_medium, 0, 0, 0,
			FontCharset_gb2312, FontOutPrecision_default, FontClipPrecision_default,
			FontQuality_default, FontPitch_default | FontFamily_SWISS, pszFaceName);
#endif
		return ret;
	}

	Font* Font::allocFont(int32 height, int32 width, int32 escapement, int32 orientation,
		FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
		FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
		FontQuality quality, FontPitchAndFamily pitchAndFamily, const CHAR* pszFaceName)
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

	void Font::release(Font* font)
	{
		if (font != NULL)
		{
			delete font;
		}
	}

	Font::Font()
	{
		m_handle = NULL;
		m_texture = INVALID_TEXTURE_ID;
		m_height = 0;
	}

	Font::~Font()
	{

	}

	WindowsFont::WindowsFont(int32 height, int32 width, int32 escapement, int32 orientation,
		FontWeight weight, BOOL italic, BOOL underline, BOOL strikeOut,
		FontCharset charSet, FontOutPrecision outPrecision, FontClipPrecision clipPrecision,
		FontQuality quality, FontPitchAndFamily pitchAndFamily, const CHAR* pszFaceName)
	{
		m_height = height;
		m_handle = CreateFontA(
			height, width, escapement, orientation,
			weight,	italic, underline, strikeOut, charSet,
			outPrecision, clipPrecision, quality,
			pitchAndFamily, pszFaceName);

		init();
	}

	WindowsFont::~WindowsFont()
	{
		
	}

	void WindowsFont::drawText(const ScreenPoint& pos, PixelColor color, const CHAR* text) const
	{
		HDC hDC = wglGetCurrentDC();
		size_t length = strlen(text);
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
	}

	void WindowsFont::drawText(const ScreenPoint& pos, PixelColor color, const WCHAR* text) const
	{
		HDC hDC = wglGetCurrentDC();
		size_t length = wcslen(text);
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
}