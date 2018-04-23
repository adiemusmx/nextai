#ifndef _MAPBAR_STRING_H_
#define _MAPBAR_STRING_H_

#include "base/mapbar_basic_types.h"

namespace MapBarDL
{
	class MbString
	{
	public:
		/* ¹¹Ôìº¯Êý */
		MbString();
		MbString(const WCHAR* str);

		/* ¿½±´¹¹Ôìº¯Êý */
		MbString(const MbString& str);

		/* Îö¹¹º¯Êý */
		virtual ~MbString();

		/* ¸³Öµ */
		virtual MbString operator=(const MbString& str);
		
		/* ±È½Ï×Ö·û´® */
		virtual BOOL operator==(const MbString& str)const;
		virtual BOOL operator==(const WCHAR* str)const;
		virtual BOOL operator!=(const MbString& str)const { return !((*this) == str); }
		virtual BOOL operator!=(const WCHAR* str)const { return !((*this) == str); }
		virtual BOOL operator>(const MbString& str)const;
		virtual BOOL operator>(const WCHAR* str)const;
		virtual BOOL operator<(const MbString& str)const { return !((*this) > str); }
		virtual BOOL operator<(const WCHAR* str)const { return !((*this) > str); }

		/* È¡¶ÀÁ¢µÄ×Ö·û */
		virtual WCHAR operator[](int32 index)const;
		
		/* ½ØÈ¡×Ö·û´® */
		virtual MbString sub(int32 startPos, int32 endPos);
		virtual MbString operator()(int32 startPos, int32 endPos);

		/* Ìæ»»×Ö·û´® */
		virtual MbString replace(const MbString& oldStr, const MbString& newStr);

		/* ²éÕÒ×Ö·û´® */
		virtual int32 find(const MbString& str)const;
		virtual int32 find(const WCHAR* str)const;
		virtual BOOL startsWith(const MbString& str)const;
		virtual BOOL startsWith(const WCHAR* str)const;
		virtual BOOL endsWith(const MbString& str)const;
		virtual BOOL endsWith(const WCHAR* str)const;

		/* Çå¿Õ×Ö·û´®£¬Ä¬ÈÏÇå³ý¿Õ¸ñ£¬ÖÆ±í·û */
		virtual void trim(const MbString& characters);
		virtual void trim(const WCHAR* characters = NULL);
		virtual void trimStart(const MbString& characters);
		virtual void trimStart(const WCHAR* characters = NULL);
		virtual void trimEnd(const MbString& characters);
		virtual void trimEnd(const WCHAR* characters = NULL);

		/* ÇÐ·Ö×Ö·û´® */
		virtual void split(const MbString& characters);
		virtual void split(const WCHAR* characters);

		/* ×Ö·û´®³¤¶È */
		virtual size_t length()const;

		/* ×Ö·û´®Æ´½Ó */
		virtual MbString cat(const MbString& str)const;
		virtual MbString operator+(const MbString& str)const;
		virtual MbString operator+=(const MbString& str);
		virtual MbString operator*(size_t times)const;		/* ×Ö·û´®ÖØ¸´times´Î */

		virtual const WCHAR* cStr()const;

	private:
		std::wstring m_buffer;
	};
}

#endif // !_MAPBAR_STRING_H_