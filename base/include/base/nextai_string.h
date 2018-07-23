#ifndef _NEXTAI_STRING_H_
#define _NEXTAI_STRING_H_

#if 0

#include "base/nextai_basic_types.h"

namespace NextAI
{
	class MbString
	{
	public:
		/* 构造函数 */
		MbString();
		MbString(const WCHAR* str);

		/* 拷贝构造函数 */
		MbString(const MbString& str);

		/* 析构函数 */
		virtual ~MbString();

		/* 赋值 */
		virtual MbString operator=(const MbString& str);
		
		/* 比较字符串 */
		virtual BOOL operator==(const MbString& str)const;
		virtual BOOL operator==(const WCHAR* str)const;
		virtual BOOL operator!=(const MbString& str)const { return !((*this) == str); }
		virtual BOOL operator!=(const WCHAR* str)const { return !((*this) == str); }

		/* 取独立的字符 */
		virtual WCHAR operator[](int32 index)const;
		
		/* 截取字符串 */
		virtual MbString sub(int32 startPos, int32 endPos);
		virtual MbString operator()(int32 startPos, int32 endPos);

		/* 替换字符串 */
		virtual MbString replace(const MbString& oldStr, const MbString& newStr);

		/* 查找字符串 */
		virtual int32 find(const MbString& str)const;
		virtual int32 find(const WCHAR* str)const;
		virtual BOOL startsWith(const MbString& str)const;
		virtual BOOL startsWith(const WCHAR* str)const;
		virtual BOOL endsWith(const MbString& str)const;
		virtual BOOL endsWith(const WCHAR* str)const;

		/* 清空字符串，默认清除空格，制表符 */
		virtual void trim(const MbString& characters);
		virtual void trim(const WCHAR* characters = NULL);
		virtual void trimStart(const MbString& characters);
		virtual void trimStart(const WCHAR* characters = NULL);
		virtual void trimEnd(const MbString& characters);
		virtual void trimEnd(const WCHAR* characters = NULL);

		/* 切分字符串 */
		virtual void split(const MbString& characters);
		virtual void split(const WCHAR* characters);

		/* 字符串长度 */
		virtual size_t length()const;

		/* 字符串拼接 */
		virtual MbString cat(const MbString& str)const;
		virtual MbString operator+(const MbString& str)const;
		virtual MbString operator+=(const MbString& str);
		virtual MbString operator*(size_t times)const;		/* 字符串重复times次 */

		virtual const WCHAR* cStr()const;

	private:
		// wstring好像不支持
#ifdef D_USE_STD_STRING
		std::wstring m_buffer;
#else
#define D_NEXTAI_STRING_BUFFER_DEFAULT_SIZE TEXT_MAX_LENGTH
		WCHAR* m_buffer;
		size_t m_bufferSize;
#endif
	};
}

#endif // 0

#endif // !_NEXTAI_STRING_H_
